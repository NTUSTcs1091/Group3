/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include "SURLCreator.h"

namespace shortlink {

const std::string SURLCreator::base64_table =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";

std::string SURLCreator::CreateSURL(const std::string &raw_url) {
  // get hash Code in length of 20
  size_t hashCode = Hasher::HashRawUrl(raw_url);

  // transfer hash Code to Hex
  std::stringstream stream;
  stream << std::hex << hashCode;
  std::string result(stream.str());

  // transfer to binary
  std::string binary = "";
  for (int i = 0; i < result.size(); i++) {
    binary += hex2bits(result[i]);
  }

  // transfer each six bit to base64 char
  std::string surl_key = "";
  for (int i = 0; binary.size() - i >= 6; i += 6) {
    std::string subChar = binary.substr(i, 6);
    int ids = std::stoi(subChar, 0, 2);
    surl_key += base64_table[ids];
  }

  return surl_key;
}
std::string SURLCreator::hex2bits(char hex) {
  switch (hex) {
  case '0':
    return "0000";
  case '1':
    return "0001";
  case '2':
    return "0010";
  case '3':
    return "0011";
  case '4':
    return "0100";
  case '5':
    return "0101";
  case '6':
    return "0110";
  case '7':
    return "0111";
  case '8':
    return "1000";
  case '9':
    return "1001";
  case 'a':
    return "1010";
  case 'b':
    return "1011";
  case 'c':
    return "1100";
  case 'd':
    return "1101";
  case 'e':
    return "1110";
  case 'f':
    return "1111";
  default:
    return "0000";
  }
}
} // namespace shortlink
