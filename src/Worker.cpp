/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef SHORTLINK_SRC_WORKER_CPP_
#define SHORTLINK_SRC_WORKER_CPP_

#include "Worker.h"
#include "Parser.h"

namespace shortlink
{
	//constructor
	Worker::Worker()
	{
		worker_status = WorkerStatus.kFree;
		resp_data = "";
		raw_request_data = "";
	}
	//start parse data
	void Run(const std::string& raw_request_data)
	{
		this->raw_request_data = raw_request_data;
		worker_status = WorkerStatus.kBusy;
		resp_data = Parser.Parse(this->raw_request_data);
		worker_status = WorkerStatus.kDone;
	}
	//return parsed data to HTTP server class
	const std::string Worker::GetResponse()
	{
		if(worker_status == WorkerStatus.kDone)
		{
			return resp_data;
		}
		else
		{
			return "";
		}
	}
}// namespace shortlink

#endif SHORTLINK_SRC_WORKER_CPP_
