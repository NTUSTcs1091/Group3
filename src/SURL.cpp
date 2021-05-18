/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include "SURL.h"

namespace shortlink {

SURL::SURL(const std::string &raw_url, const std::string &surl) {
  this->raw_url = raw_url;
  this->surl = surl;
  this->expire = boost::gregorian::day_clock::local_day();
}

SURL::SURL(const std::string &raw_url, const std::string &surl,
           const std::string &url, const Date &expire) {
  this->raw_url = raw_url;
  this->surl = surl;
  this->expire = expire;
}

} // namespace shortlink
