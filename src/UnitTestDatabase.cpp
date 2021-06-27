/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include <thread>

#include <gtest/gtest.h>

#include "Database.h"

shortlink::Database database;

void TestDatabaseCreate(const std::string &raw_url) {
  // create a hundred datas
  for (int i = 0; i < 100; i++) {
    const std::string insert_url = raw_url + std::to_string(i);
    shortlink::Database::CreateSURL(insert_url);
  }
}
void TestDatabaseRead(const std::string &raw_url) {
  // read a hundred datas
  for (int i = 0; i < 100; i++) {
    const std::string insert_url = raw_url + std::to_string(i);
    shortlink::Database::ReadSURL(insert_url);
  }
}

TEST(Database_Test, TestingDatabaseMultiThread) {
  // test Create the duplicate url and multithread create
  std::vector<std::string> result1;
  std::string url("https://www.youtube.com/");
  std::thread test1_1((TestDatabaseCreate), url);
  std::thread test1_2((TestDatabaseCreate), url);

  // set the answer data
  for (int i = 0; i < 100; i++) {
    std::string insert_url = url + std::to_string(i);
    result1.push_back(shortlink::SURLCreator::CreateSURL(insert_url));
  }

  test1_1.join();
  test1_2.join();

  // verify if the result and insert data is the same
  for (int i = 0; i < 100; i++) {
    std::string insert_url = url + std::to_string(i);
    std::string result = shortlink::Database::ReadSURL(result1[i]);
    ASSERT_EQ(result1[i], insert_url);
  }

  // verify if user try to reading the data which does not exist
  ASSERT_EQ("", shortlink::Database::ReadSURL("testing"));

  // check that program will not crash when update the data and read the data at
  // the same time
  std::thread test2_1((TestDatabaseCreate), url);
  std::thread test2_2((TestDatabaseRead), url);

  test2_1.join();
  test2_2.join();
}
