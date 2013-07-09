// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/memory/ref_counted.h"
#include "chrome/browser/extensions/api/dial/dial_device_data.h"
#include "chrome/browser/extensions/api/dial/dial_service.h"
#include "net/base/capturing_net_log.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using base::Time;
using ::testing::A;
using ::testing::AtLeast;
using ::testing::Return;

namespace {

const char kValidResponse[] =
  "HTTP/1.1 OK\r\n"
  "LOCATION: http://127.0.0.1/dd.xml\r\n"
  "USN: some_id\r\n"
  "CACHE-CONTROL: max-age=1800\r\n"
  "CONFIGID.UPNP.ORG: 1\r\n\r\n";

}  // namespace

namespace extensions {

class MockObserver : public DialService::Observer {
 public:
  MOCK_METHOD1(OnDiscoveryRequest, void(DialService*));
  MOCK_METHOD2(OnDeviceDiscovered, void(DialService*, const DialDeviceData&));
  MOCK_METHOD1(OnDiscoveryFinished, void(DialService*));
  MOCK_METHOD2(OnError, void(DialService*, const std::string&));
};

class DialServiceTest : public testing::Test {
 public:
  DialServiceTest() {
    dial_service_ = new DialServiceImpl(&capturing_net_log_);
    dial_service_->AddObserver(&mock_observer_);
  }
 protected:
  net::CapturingNetLog capturing_net_log_;
  scoped_refptr<DialServiceImpl> dial_service_;
  MockObserver mock_observer_;
};

TEST_F(DialServiceTest, TestOnDiscoveryRequest) {
  dial_service_->discovery_active_ = true;
  size_t num_bytes = dial_service_->send_buffer_->size();

  EXPECT_CALL(mock_observer_, OnDiscoveryRequest(A<DialService*>())).Times(1);
  dial_service_->OnSocketWrite(num_bytes);
}

TEST_F(DialServiceTest, TestOnDeviceDiscovered) {
  dial_service_->discovery_active_ = true;
  int response_size = arraysize(kValidResponse) - 1;
  dial_service_->recv_buffer_ = new net::IOBufferWithSize(response_size);
  strncpy(dial_service_->recv_buffer_->data(), kValidResponse, response_size);

  DialDeviceData expected_device;
  expected_device.set_device_id("some_id");

  EXPECT_CALL(mock_observer_,
              OnDeviceDiscovered(A<DialService*>(), expected_device))
    .Times(1);
  dial_service_->OnSocketRead(response_size);
};

TEST_F(DialServiceTest, TestOnDiscoveryFinished) {
  dial_service_->discovery_active_ = true;

  EXPECT_CALL(mock_observer_, OnDiscoveryFinished(A<DialService*>())).Times(1);
  dial_service_->FinishDiscovery();
  EXPECT_FALSE(dial_service_->discovery_active_);
}

TEST_F(DialServiceTest, TestResponseParsing) {
  Time now = Time::Now();

  // Successful case
  DialDeviceData parsed;
  EXPECT_TRUE(DialServiceImpl::ParseResponse(kValidResponse,
                                             now, &parsed));
  EXPECT_EQ("some_id", parsed.device_id());
  EXPECT_EQ("http://127.0.0.1/dd.xml", parsed.device_description_url().spec());
  EXPECT_EQ(1, parsed.config_id());
  EXPECT_EQ(now, parsed.response_time());

  // Failure cases
  DialDeviceData not_parsed;

  // Empty, garbage
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "",
    now, &not_parsed));
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "\r\n\r\n",
    now, &not_parsed));
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "xyzzy",
    now, &not_parsed));

  // No headers
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "HTTP/1.1 OK\r\n\r\n",
    now, &not_parsed));

  // Missing LOCATION
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "HTTP/1.1 OK\r\n"
    "USN: some_id\r\n\r\n",
    now, &not_parsed));

  // Empty LOCATION
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "HTTP/1.1 OK\r\n"
    "LOCATION:\r\n"
    "USN: some_id\r\n\r\n",
    now, &not_parsed));

  // Missing USN
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "HTTP/1.1 OK\r\n"
    "LOCATION: http://127.0.0.1/dd.xml\r\n\r\n",
    now, &not_parsed));

  // Empty USN
  EXPECT_FALSE(DialServiceImpl::ParseResponse(
    "HTTP/1.1 OK\r\n"
    "LOCATION: http://127.0.0.1/dd.xml\r\n"
    "USN:\r\n\r\n",
    now, &not_parsed));
}

}  // namespace extensions
