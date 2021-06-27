/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef _SHORTLINK_SRC_SURLCreator_H_
#define _SHORTLINK_SRC_SURLCreator_H_

#include <unordered_map>

#include "Hasher.h"
#include "SURL.h"

namespace shortlink {
// The controller of the SURL Encoding method
// Example:
//	std::string raw_url = "https://www.google.com";
//  std::string surlKey = shortlink::SURLCreator::CreateSURL(raw_url);
class SURLCreator {
public:
  SURLCreator() = default;

  // Input the original URL and encoding it to a new SURL key.
  // default length of surl key is 8, can deal range 6 ~ 10.
  static std::string CreateSURL(const std::string &raw_url, int offset = 0,
                                int length = 8);

private:
  // transfer hex to bits
  static const std::unordered_map<char, std::string> hex2bits;

  // the base64 table for mapping id to character
  static const std::string base64_table;

  // The max length of the short url
  static const int kMaxLengthOfSurl;

  // The min length of the short url
  static const int kMinLengthOfSurl;
};

} // namespace shortlink

#endif // !_SHORTLINK_SRC_SURLCreator_H_
