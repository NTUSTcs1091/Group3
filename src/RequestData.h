 /*
Copyright (c) 2021 Chiu Yen-Chen,
Swen Sun-Yen. 
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */ 
#ifndef SHORTLINK_SRC_REQUESTDATA_H_
#define SHORTLINK_SRC_REQUESTDATA_H_
#include<string>

namespace shortlink
{
	
// RequestData is a class of a data structure that represents a request that a user sends to the server.
// Example:
//    RequestData data = RequestData();
//    data.host = "140.118.88.50";
//    data.port = 80;
//    data.target = "3arUqBH";
//    data.requestMethod = "Search";
class RequestData
{
public:
	// Default constructor, all memeber variables would be 0 or "";
	RequestData();
	// Constructor that sets all the memeber variables with the parameters.
	RequestData(std::string _host, uint16_t _port, std::string _target, std::string _requestMethod);
	// Default destructor
	~RequestData();

	std::string host;
	uint16_t port;
	std::string target;
	std::string requestMethod;
};

}

#endif  // SHORTLINKSERVER_SRC_REQUESTDATA_H_
