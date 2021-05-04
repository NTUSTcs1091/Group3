/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#ifndef SHORTLINK_SRC_CREATEHANDLER_H_
#define SHORTLINK_SRC_CREATEHANDLER_H_
#include <string>

#include "Hasher.h"
#include "RequestHandler.h"

namespace shortlink {

// This class represents a operation of creating SURL from RawURL and storing
// them to a database. Example:
//    CreateHandler handler = CreateHandler();
//    handler.CreateSURL();
//    std::string surl = handler.GetSURL();
class CreateHandler : RequestHandler {
 public:
  CreateHandler();
  ~CreateHandler();

  // Creates a SURL in database that is paired with original URL.
  void CreateSURL();
  // Returns the SURL that created in database. If it isn't created, returns
  // empty string.
  std::string GetSURL();

 private:
  Hasher hasher;

  // Hashes the URL to SURL, returns SURL.
  std::string EncodeURL();
};

}  // namespace shortlink

#endif  // SHORTLINK_SRC_CREATEHANDLER_H_
