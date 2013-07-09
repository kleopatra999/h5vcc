# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import json
import struct_generator

def _JSONToCString16(json_string_literal):
  """Converts a JSON string literal to a C++ UTF-16 string literal. This is
  done by converting \\u#### to \\x####.
  """
  c_string_literal = json_string_literal
  escape_index = c_string_literal.find('\\')
  while escape_index > 0:
    if c_string_literal[escape_index + 1] == 'u':
      # We close the C string literal after the 4 hex digits and reopen it right
      # after, otherwise the Windows compiler will sometimes try to get more
      # than 4 characters in the hex string.
      c_string_literal = (c_string_literal[0:escape_index + 1] + 'x' +
          c_string_literal[escape_index + 2:escape_index + 6] + '" L"' +
          c_string_literal[escape_index + 6:])
    escape_index = c_string_literal.find('\\', escape_index + 6)
  return c_string_literal

def _GenerateString(content, lines):
  """Generates an UTF-8 string to be included in a static structure initializer.
  If content is not specified, uses NULL.
  """
  if content is None:
    lines.append('  NULL,')
  else:
    # json.dumps quotes the string and escape characters as required.
    lines.append('  %s,' % json.dumps(content))

def _GenerateString16(content, lines):
  """Generates an UTF-16 string to be included in a static structure
  initializer. If content is not specified, uses NULL.
  """
  if content is None:
    lines.append('  NULL,')
  else:
    # json.dumps quotes the string and escape characters as required.
    lines.append('  L%s,' % _JSONToCString16(json.dumps(content)))

def _GenerateArray(field_info, content, lines):
  """Generates an array to be included in a static structure initializer. If
  content is not specified, uses NULL. The array is assigned to a temporary
  variable which is initialized before the structure.
  """
  if content is None:
    lines.append('  NULL,')
    lines.append('  0,')  # Size of the array.
    return

  # Create a new array variable and use it in the structure initializer.
  # This prohibits nested arrays. Add a clash detection and renaming mechanism
  # to solve the problem.
  var = 'array_%s' % field_info['field'];
  lines.append('  %s,' % var)
  lines.append('  %s,' % len(content))  # Size of the array.
  # Generate the array content.
  array_lines = []
  field_info['contents']['field'] = var;
  array_lines.append(struct_generator.GenerateField(
                     field_info['contents']) + '[] = {')
  for subcontent in content:
    GenerateFieldContent(field_info['contents'], subcontent, array_lines)
  array_lines.append('};')
  # Prepend the generated array so it is initialized before the structure.
  lines.reverse()
  array_lines.reverse()
  lines.extend(array_lines)
  lines.reverse()

def GenerateFieldContent(field_info, content, lines):
  """Generate the content of a field to be included in the static structure
  initializer. If the field's content is not specified, uses the default value
  if one exists.
  """
  if content is None:
    content = field_info.get('default', None)
  type = field_info['type']
  if type == 'int' or type == 'enum':
    lines.append('  %s,' % content)
  elif type == 'string':
    _GenerateString(content, lines)
  elif type == 'string16':
    _GenerateString16(content, lines)
  elif type == 'array':
    _GenerateArray(field_info, content, lines)
  else:
    raise RuntimeError('Unknown field type "%s"' % type)

def GenerateElement(type_name, schema, element_name, element):
  """Generate the static structure initializer for one element.
  """
  lines = [];
  lines.append('const %s %s = {' % (type_name, element_name));
  for field_info in schema:
    content = element.get(field_info['field'], None)
    if (content == None and not field_info.get('optional', False)):
      raise RuntimeError('Mandatory field "%s" omitted in element "%s".' %
                         (field_info['field'], element_name))
    GenerateFieldContent(field_info, content, lines)
  lines.append('};')
  return '\n'.join(lines)

def GenerateElements(type_name, schema, description):
  """Generate the static structure initializer for all the elements in the
  description['elements'] dictionary, as well as for any variables in
  description['int_variables'].
  """
  result = [];
  for var_name, value in description.get('int_variables', {}).items():
    result.append('const int %s = %s;' % (var_name, value))
  result.append('')

  for element_name, element in description.get('elements', {}).items():
    result.append(GenerateElement(type_name, schema, element_name, element))
    result.append('')
  return '\n'.join(result)
