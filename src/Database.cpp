/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#include "Database.h"

namespace shortlink {

// static variable initial
std::unordered_map<std::string, std::unique_ptr<SURL>> Database::lut;
Date Database::last_expiration = boost::gregorian::day_clock::local_day();
std::mutex Database::write_lock;

std::string Database::CreateSURL(const std::string &raw_url) {
  // Create the short url
  std::string short_url = SURLCreator::CreateSURL(raw_url);

  // Check if short url exists
  std::string read_url = ReadSURL(short_url);
  if (read_url != "") {
    // if short url exists
    if (read_url == raw_url) {
      // the short url and its corresponding raw_url in lut is the same as the
      // input raw_url. Update the surl expire time.
      Date now = boost::gregorian::day_clock::local_day();
      UpdateSURL(std::move(lut.at(short_url)), now);
      return read_url;
    } else {
      // the short url in lut is the same as the input short url,
      // but the corresponding raw_url is not the same.
      // Add the offset to Encode the url
      int offset = 1;
      while (read_url != raw_url) {
        short_url = SURLCreator::CreateSURL(raw_url, offset);
        read_url = ReadSURL(short_url);
      }
      std::unique_ptr<SURL> surl(new SURL(raw_url, short_url));
      InsertSURL(short_url, std::move(surl));
      return short_url;
    }
  } else {
    // if short url does not in the lut, insert it to the lut
    std::unique_ptr<SURL> surl(new SURL(raw_url, short_url));
    InsertSURL(short_url, std::move(surl));
    return short_url;
  }
}
std::string Database::ReadSURL(const std::string &surl) {
  // if the surl is not in the lut, return "", else return the raw url.
  write_lock.lock();
  bool found_flag = (lut.find(surl) != lut.end());
  write_lock.unlock();
  if (!found_flag) {
    return "";
  }

  return lut.at(surl)->GetUrl();
}
bool Database::InsertSURL(const std::string &short_url,
                          std::unique_ptr<SURL> surl) {
  // lock the insert lock, make sure there is only one thread can change lut.
  write_lock.lock();
  lut[short_url] = std::move(surl);
  write_lock.unlock();
  return true;
}
bool Database::UpdateSURL(std::unique_ptr<SURL> surl, const Date &expire) {
  write_lock.lock();
  surl.get()->SetExpireTime(expire);
  lut.at(surl.get()->GetSURL()) = std::move(surl);
  write_lock.unlock();
  return true;
}

bool Database::CheckSURLExpiration() {
  Date now = boost::gregorian::day_clock::local_day();

  boost::gregorian::date_duration dur = now - last_expiration;
  if (dur.days() > 1) {
    return DeleteSURL();
  }

  return false;
}

bool Database::DeleteSURL() {
  Date now = boost::gregorian::day_clock::local_day();
  bool delete_flag = false;

  std::unordered_map<std::string, std::unique_ptr<SURL>>::iterator it;
  it = lut.begin();
  while (it != lut.end()) {
    const boost::gregorian::date_duration kExpireTime =
        now - it->second.get()->GetExpireTime();
    const int kExpireTimeInDays = kExpireTime.days();
    if (kExpireTimeInDays >= 30) {
      write_lock.lock();
      it = lut.erase(it);
      delete_flag = true;
      write_lock.unlock();
    }
  }

  return delete_flag;
}

} // namespace shortlink
