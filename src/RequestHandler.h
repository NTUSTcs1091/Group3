/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#ifndef SHORTLINK_SRC_REQUESTHANDLER_H_
#define SHORTLINK_SRC_REQUESTHANDLER_H_
#include <string>

#include "RequestData.h"
#include "SURL.h"

namespace shortlink {

// This class represents a operation of handling different types of requests and
// executing them. Example:
//    RequestHander handler = RequestHandler(requestData);
//    handler.RunRequest();
class RequestHandler {
 public:
  // Constructor with request as parameter.
  RequestHandler(RequestData request);
  ~RequestHandler();

  // Run the request from the user. Returns the requested data.
  std::string RunRequest();

 private:
  std::string respData;
  RequestData reqData;
};

}  // namespace shortlink

#endif  // SHORTLINK_SRC_REQUESTHANDLER_H_
