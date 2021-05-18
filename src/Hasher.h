/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef _SHORTLINK_SRC_HASHER_H_
#define _SHORTLINK_SRC_HASHER_H_

#include <string>

namespace shortlink {

// Encapsulate the hasher of standard library.
// let user can only call the HashRawURL function to get the hash number.
// Example:
//		string url = "https:://www.google.com"
//		shortlink::Hasher hasher;
//		size_t hash_code = hasher.HashRawUrl(url);
class Hasher {
public:
  Hasher() = default;

  // Delete the copy constructor
  Hasher(const Hasher &) = delete;

  // Delete copy operator
  Hasher &operator=(const Hasher &hasher) = delete;

  // Hash the raw url to a hash code Using standard library hash.
  static size_t HashRawUrl(const std::string &raw_url);

private:
  // standard hasher for the string.
  static std::hash<std::string> str_hasher;
};
} // namespace shortlink
#endif // !_SHORTLINK_SRC_HASHER_H_
