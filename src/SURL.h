/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef _SHORTLINK_SRC_SURL_H_
#define _SHORTLINK_SRC_SURL_H_

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace shortlink {
// shorten the using of the class name
typedef boost::gregorian::date Date;

// A data Type to store a short URL and its expire time
// url name wont be change after the time you created.
// Example:
//		std::string ds("2021/04/19");
//		SURL surl("https:://www.google.com", Date(from_string(ds)));
//		// Update the expire time after it is re-created
//		Date now = boost::gregorian::day_clock::local_day();
//		surl.SetExpireTime(now);
class SURL {
public:
  // default constructor
  SURL() = default;

  // default constructor with target url and now date
  SURL(const std::string &raw_url, const std::string &surl);

  // default contructor with target url and specific expire date
  SURL(const std::string &raw_url, const std::string &surl,
       const std::string &url, const Date &expire);

  // get the name of the SURL
  std::string GetSURL() const { return surl; }

  // get the name of the url
  std::string GetUrl() const { return raw_url; }

  // get the expire time of the SURL
  Date GetExpireTime() const { return expire; }

  // update the expire time of the SURL
  void SetExpireTime(const Date &date) { expire = date; }

private:
  // the original url of the SURL
  std::string raw_url;

  // the short url of the SURL
  std::string surl;

  // the expire date of the SURL, data type using boost library
  Date expire;
};
} // namespace shortlink

#endif // !_SHORTLINK_SRC_SURL_H_
