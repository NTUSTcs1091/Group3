/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */

#ifndef SHORTLINK_SRC_WORKER_H_
#define SHORTLINK_SRC_WORKER_H_
#include <string>

namespace shortlink
{
    enum WorkerStatus
    {
        kBusy,
        kFree,
        kDone
    };
    //ThreadPool will create this class 
    //Example:
    // Worker worker = Worker();
    // worker.Run("raw_request_data");
    class Worker
    {
    private:
        //private copy constructor
        Worker(const Worker &other);
        //worker status
        WorkerStatus worker_status;
        //parsed data 
        std::string resp_data;
        //Raw data Request
        std::string raw_request_data;

    public:
        Worker();        
        ~Worker();
        //start parse data
        void Run(const std::string& raw_request_data);
        //return parsed data to HTTP server class 
        const std::string GetResponse();      
    };
}// namespace shortlink

#endif SHORTLINK_SRC_WORKER_H_
