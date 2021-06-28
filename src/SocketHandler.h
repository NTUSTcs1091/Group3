/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include <iostream>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "Worker.h"

#ifndef SHORTLINK_SRC_SOCKETHANDLER_H_
#define SHORTLINK_SRC_SOCKETHANDLER_H_

namespace shortlink {
    
    typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketPointer;

    //  Handler for a socket, this class will create a thread and wait until HttpServer gives this SocketHandler a socket to work with.
    class SocketHandler : public boost::enable_shared_from_this<SocketHandler>
    {
    public:
        //  the shared pointer type of this class
        typedef boost::shared_ptr<SocketHandler> pointer;

        //  make a shared_ptr of this class
        static pointer Create();

        //  starts the working thread
        void StartWorkingThread();

        //  Shows whether this object is ready to handle a new socket.
        bool ReadyToWork() { return (threadRunning && (socket == NULL)); }

        //  Shows whether this object is connected to a client and working.
        bool SocketWorking() { return socketWorking; }

        //  Gives this handler a connected socket to work with (wait for the client message and parse it...)
        void AssignSocket(const SocketPointer& newSocket);

    private:

        //  Looping work of a thread created by this class. 
        void LoopingWork();

        //  Private constructor. Initializes a tcp::socket. Called by static function: create()
        SocketHandler() { };

        //  Send messages to the socket
        void WriteSocket(std::string message);

        //  Read messages from the socket
        std::string ReadSocket();

        //  Handle the message from the client.
        std::string HandleMessage(std::string message);

        //  Close the current socket
        void CloseSocket();

        //  Socket which the thread on this class is dealing with (will be assigned by HttpServer and be released after the task is finished)
        SocketPointer socket = NULL;
        //  Working thread
        std::thread workingThread;
        //  Shows whether the working thread is running
        std::atomic<bool> threadRunning = false;
        //  Shows whether the thread is working with a socket
        std::atomic<bool> socketWorking = false;
    };

}

#endif
