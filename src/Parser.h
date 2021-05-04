/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#ifndef SHORTLINK_SRC_PARSER_H_
#define SHORTLINK_SRC_PARSER_H_
#include <string>

namespace shortlink
{

// forward declare
class RequestData;
class SURL;

// This class represents a operation that can translate raw message to executable information of a request.
// Example:
//    Parser pars = Parser();
//    RequestData reqData = pars.Parse(raw_data);
class Parser
{
public:
	Parser();
	~Parser();

	// Parses the formated request data from the raw string.
	RequestData Parse(const std::string &rawData);
};

} // namespace shortlink

#endif // SHORTLINK_SRC_PARSER_H_
