/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <iostream>
#include <string>

#include "ThreadPool.h"

#ifndef SHORTLINK_SRC_HTTPSERVER_H_
#define SHORTLINK_SRC_HTTPSERVER_H_

namespace shortlink {
// Shows the status of the server.
// kRunning means the server have started the asyncronize work and thread pool.
// kStopped means the server have not been started or have been shutdowned.
enum ServerStatus { kRunning, kStopped };
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketPointer;
// Handles the connection from all the clients.
// HttpServer will establish the ListenerThreadPool during the construction.
// Example:
//    std::unique_ptr<HttpServer> httpServer = std::make_unique<HttpServer>();
//    // start the server
//    httpServer->Start();

class HttpServer {
 public:
  // Constructor
  HttpServer(int thread_pool_size, boost::asio::io_context& context, int port);
  // Delete default constructor
  HttpServer() = delete;
  // Delete copy constructors
  HttpServer(const HttpServer&) = delete;
  HttpServer& operator=(const HttpServer&) = delete;
  // Destructor
  ~HttpServer();
  // Start the server
  void Start();
  // Close all the threads and async-works
  void Shutdown();
  // Get the server status
  ServerStatus GetServerStatus() const { return serverStatus; }
  // Get the number of current serving clients
  int GetClientCount() const;
  // Get the size of the thread pool
  int GetThreadPoolSize() const { return SocketHandlerPool->GetMaxPoolSize(); }

 private:
  // Thread pool initialization. This will be called by the constructor.
  void InitializeSocketHandlerPool(int size);
  // Start to listen to incoming client connections
  void StartAccept();
  // Handle the connected socket. Hand over the socket to a working thread and
  // call StartAccept() to keep waiting for another connection. (This function
  // will be autometically called again after async_accept() finishes)
  void HandleAccept(const boost::system::error_code& error);
  //	io_context for async works
  boost::asio::io_context& io_context;
  //	acceptor for TCP connection
  boost::asio::ip::tcp::acceptor acceptor;
  //	socket for waiting a client connection
  SocketPointer socket;
  //	thread pool for socket handling
  std::unique_ptr<ThreadPool> socket_handler_pool;
  //	the current status of this server
  ServerStatus server_status = ServerStatus::kStopped;
}

}  // namespace shortlink

#endif  // !SHORTLINK_SRC_HTTPSERVER_H_
