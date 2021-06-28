/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include "CreateHandler.h"

void CreateHandler::CreateSURL() {
  // check if it has original URL
  respData = Database.CreateSURL(reqData.target);
}

std::string CreateHandler::GetSURL() {
  respData = Database.ReadSURL();
  return respData;
}

std::string CreateHandler::RunRequest() {
  CreateSURL();
  return GetSURL();
}
