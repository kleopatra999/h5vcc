// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dbus/values_util.h"

#include "base/json/json_writer.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "dbus/message.h"

namespace dbus {

namespace {

// Returns whether |value| is exactly representable by double or not.
template<typename T>
bool IsExactlyRepresentableByDouble(T value) {
  return value == static_cast<T>(static_cast<double>(value));
}

// Pops values from |reader| and appends them to |list_value|.
bool PopListElements(MessageReader* reader, ListValue* list_value) {
  while (reader->HasMoreData()) {
    Value* element_value = PopDataAsValue(reader);
    if (!element_value)
      return false;
    list_value->Append(element_value);
  }
  return true;
}

// Pops dict-entries from |reader| and sets them to |dictionary_value|
bool PopDictionaryEntries(MessageReader* reader,
                          DictionaryValue* dictionary_value) {
  while (reader->HasMoreData()) {
    DCHECK_EQ(Message::DICT_ENTRY, reader->GetDataType());
    MessageReader entry_reader(NULL);
    if (!reader->PopDictEntry(&entry_reader))
      return false;
    // Get key as a string.
    std::string key_string;
    if (entry_reader.GetDataType() == Message::STRING) {
      // If the type of keys is STRING, pop it directly.
      if (!entry_reader.PopString(&key_string))
        return false;
    } else {
      // If the type of keys is not STRING, convert it to string.
      scoped_ptr<Value> key(PopDataAsValue(&entry_reader));
      if (!key.get())
        return false;
      // Use JSONWriter to convert an arbitrary value to a string.
      base::JSONWriter::Write(key.get(), &key_string);
    }
    // Get the value and set the key-value pair.
    Value* value = PopDataAsValue(&entry_reader);
    if (!value)
      return false;
    dictionary_value->SetWithoutPathExpansion(key_string, value);
  }
  return true;
}

// Gets the D-Bus type signature for the value.
std::string GetTypeSignature(const base::Value& value) {
  switch (value.GetType()) {
    case base::Value::TYPE_BOOLEAN:
      return "b";
    case base::Value::TYPE_INTEGER:
      return "i";
    case base::Value::TYPE_DOUBLE:
      return "d";
    case base::Value::TYPE_STRING:
      return "s";
    case base::Value::TYPE_BINARY:
      return "ay";
    case base::Value::TYPE_DICTIONARY:
      return "a{sv}";
    default:
      DLOG(ERROR) << "Unexpected type " << value.GetType();
      return "";
  }
}

}  // namespace

Value* PopDataAsValue(MessageReader* reader) {
  Value* result = NULL;
  switch (reader->GetDataType()) {
    case Message::INVALID_DATA:
      // Do nothing.
      break;
    case Message::BYTE: {
      uint8 value = 0;
      if (reader->PopByte(&value))
        result = Value::CreateIntegerValue(value);
      break;
    }
    case Message::BOOL: {
      bool value = false;
      if (reader->PopBool(&value))
        result = Value::CreateBooleanValue(value);
      break;
    }
    case Message::INT16: {
      int16 value = 0;
      if (reader->PopInt16(&value))
        result = Value::CreateIntegerValue(value);
      break;
    }
    case Message::UINT16: {
      uint16 value = 0;
      if (reader->PopUint16(&value))
        result = Value::CreateIntegerValue(value);
      break;
    }
    case Message::INT32: {
      int32 value = 0;
      if (reader->PopInt32(&value))
        result = Value::CreateIntegerValue(value);
      break;
    }
    case Message::UINT32: {
      uint32 value = 0;
      if (reader->PopUint32(&value))
        result = Value::CreateDoubleValue(value);
      break;
    }
    case Message::INT64: {
      int64 value = 0;
      if (reader->PopInt64(&value)) {
        DLOG_IF(WARNING, !IsExactlyRepresentableByDouble(value)) <<
            value << " is not exactly representable by double";
        result = Value::CreateDoubleValue(value);
      }
      break;
    }
    case Message::UINT64: {
      uint64 value = 0;
      if (reader->PopUint64(&value)) {
        DLOG_IF(WARNING, !IsExactlyRepresentableByDouble(value)) <<
            value << " is not exactly representable by double";
        result = Value::CreateDoubleValue(value);
      }
      break;
    }
    case Message::DOUBLE: {
      double value = 0;
      if (reader->PopDouble(&value))
        result = Value::CreateDoubleValue(value);
      break;
    }
    case Message::STRING: {
      std::string value;
      if (reader->PopString(&value))
        result = Value::CreateStringValue(value);
      break;
    }
    case Message::OBJECT_PATH: {
      ObjectPath value;
      if (reader->PopObjectPath(&value))
        result = Value::CreateStringValue(value.value());
      break;
    }
    case Message::UNIX_FD: {
      // Cannot distinguish a file descriptor from an int
      NOTREACHED();
      break;
    }
    case Message::ARRAY: {
      MessageReader sub_reader(NULL);
      if (reader->PopArray(&sub_reader)) {
        // If the type of the array's element is DICT_ENTRY, create a
        // DictionaryValue, otherwise create a ListValue.
        if (sub_reader.GetDataType() == Message::DICT_ENTRY) {
          scoped_ptr<DictionaryValue> dictionary_value(new DictionaryValue);
          if (PopDictionaryEntries(&sub_reader, dictionary_value.get()))
            result = dictionary_value.release();
        } else {
          scoped_ptr<ListValue> list_value(new ListValue);
          if (PopListElements(&sub_reader, list_value.get()))
            result = list_value.release();
        }
      }
      break;
    }
    case Message::STRUCT: {
      MessageReader sub_reader(NULL);
      if (reader->PopStruct(&sub_reader)) {
        scoped_ptr<ListValue> list_value(new ListValue);
        if (PopListElements(&sub_reader, list_value.get()))
          result = list_value.release();
      }
      break;
    }
    case Message::DICT_ENTRY:
      // DICT_ENTRY must be popped as an element of an array.
      NOTREACHED();
      break;
    case Message::VARIANT: {
      MessageReader sub_reader(NULL);
      if (reader->PopVariant(&sub_reader))
        result = PopDataAsValue(&sub_reader);
      break;
    }
  }
  return result;
}

void AppendBasicTypeValueData(MessageWriter* writer, const base::Value& value) {
  switch (value.GetType()) {
    case base::Value::TYPE_BOOLEAN: {
      bool bool_value = false;
      bool success = value.GetAsBoolean(&bool_value);
      DCHECK(success);
      writer->AppendBool(bool_value);
      break;
    }
    case base::Value::TYPE_INTEGER: {
      int int_value = 0;
      bool success = value.GetAsInteger(&int_value);
      DCHECK(success);
      writer->AppendInt32(int_value);
      break;
    }
    case base::Value::TYPE_DOUBLE: {
      double double_value = 0;
      bool success = value.GetAsDouble(&double_value);
      DCHECK(success);
      writer->AppendDouble(double_value);
      break;
    }
    case base::Value::TYPE_STRING: {
      std::string string_value;
      bool success = value.GetAsString(&string_value);
      DCHECK(success);
      writer->AppendString(string_value);
      break;
    }
    default:
      DLOG(ERROR) << "Unexpected type " << value.GetType();
      break;
  }
}

void AppendBasicTypeValueDataAsVariant(MessageWriter* writer,
                                       const base::Value& value) {
  MessageWriter sub_writer(NULL);
  writer->OpenVariant(GetTypeSignature(value), &sub_writer);
  AppendBasicTypeValueData(&sub_writer, value);
  writer->CloseContainer(&sub_writer);
}

}  // namespace dbus
