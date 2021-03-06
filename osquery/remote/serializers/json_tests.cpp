/*
 *  Copyright (c) 2014, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <gtest/gtest.h>

#include "osquery/remote/serializers/json.h"

namespace osquery {

class JSONTests : public testing::Test {};

TEST_F(JSONTests, testSerialize) {
  auto json = JSONSerializer();
  boost::property_tree::ptree params;
  params.put<std::string>("foo", "bar");

  std::string serialized;
  auto s = json.serialize(params, serialized);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(serialized, "{\"foo\":\"bar\"}\n");
}

TEST_F(JSONTests, testDeserialize) {
  auto json = JSONSerializer();
  boost::property_tree::ptree params;
  std::string serialized = "{\"foo\":\"bar\"}\n";
  auto s = json.deserialize(serialized, params);

  boost::property_tree::ptree expected;
  expected.put<std::string>("foo", "bar");

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(params, expected);
}
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}
