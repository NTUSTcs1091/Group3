/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef _SHORTLINK_SRC_SURLCreator_H_
#define _SHORTLINK_SRC_SURLCreator_H_

#include "Hasher.h"
#include "SURL.h"

namespace shortlink {
// The controller of the SURL Encoding method
// Example:
//	std::string raw_url = "https://www.google.com";
//	std::string surl = my_creator.CreateSURL(raw_url);
class SURLCreator {
public:
  SURLCreator() = default;

  // Input the original URL and encoding it to a new SURL.
  static std::string CreateSURL(const std::string &rawURL);

private:
  // transfer hex to bits
  static std::string hex2bits(char hex);

  // the base64 table for mapping id to character
  static const std::string base64_table;
};

} // namespace shortlink

#endif // !_SHORTLINK_SRC_SURLCreator_H_