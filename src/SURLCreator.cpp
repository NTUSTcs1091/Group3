/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include "SURLCreator.h"

namespace shortlink {
// static variable
const std::string SURLCreator::base64_table =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
const std::unordered_map<char, std::string> SURLCreator::hex2bits = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
    {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"},
};

std::string SURLCreator::CreateSURL(const std::string &raw_url, int length) {
  // make sure length is in the range of 6 ~ 10
  length = std::max(std::min(length, 10), 6);

  // get hash Code in length of 20
  size_t hashCode = Hasher::HashRawUrl(raw_url);

  // transfer hash Code to Hex
  std::stringstream stream;
  stream << std::hex << hashCode;
  std::string result(stream.str());

  // transfer to binary
  std::string binary = "";
  for (int i = 0; i < result.size(); i++) {
    binary += hex2bits.at(result[i]);
  }

  // transfer each six bit to base64 char
  std::string surl_key = "";
  for (int i = 0; binary.size() - i >= 6; i += 6) {
    std::string subChar = binary.substr(i, 6);
    int ids = std::stoi(subChar, 0, 2);
    surl_key += base64_table[ids];
  }

  // extract a string with a length of 6 ~ 10, depending on the parameter.
  surl_key = surl_key.substr(0, length);

  return surl_key;
}

} // namespace shortlink
