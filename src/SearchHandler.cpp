/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include "SearchHandler.h"

std::string SearchHandler::SearchURL() {
  respData = Database.ReadSURL(reqData.target);
  return respData;
}

std::string SearchHandler::RunRequest() { return SearchURL(); }
