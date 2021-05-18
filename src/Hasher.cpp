/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include "Hasher.h"

namespace shortlink {
std::hash<std::string> Hasher::str_hasher;

size_t Hasher::HashRawUrl(const std::string &raw_url) {
  return str_hasher(raw_url);
}
} // namespace shortlink
