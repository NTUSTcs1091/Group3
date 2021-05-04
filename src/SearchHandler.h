/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#ifndef SHORTLINK_SRC_SEARCHHANDLER_H_
#define SHORTLINK_SRC_SEARCHHANDLER_H_
#include <string>

namespace shortlink {

// This class represents a operation of searching for URL by SURL
// Example:
//    SearchHandler handler = SearchHandler();
//    string rawURL = handler.SearchSURL();
class SearchHandler {
 public:
  SearchHandler();
  ~SearchHandler();

  // Search by the SURL in the database, return the original URL.
  std::string SearchURL();
};

}  // namespace shortlink

#endif  // SHORTLINK_SRC_SEARCHHANDLER_H_
