/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include "HttpServer.h"

namespace shortlink {

	HttpServer::HttpServer(int threadPoolSize, boost::asio::io_context& context, int port)
		: ioContext(context),
		acceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	{
		//	initialize all SocketHandlers
		InitializeSocketHandlerPool(threadPoolSize);
	}

	HttpServer::~HttpServer()
	{
		Shutdown();
	}

	void HttpServer::InitializeSocketHandlerPool(int size)
	{
        if (socket_handler_pool != nullptr)
            return;
		socket_handler_pool = std::unique_ptr<ThreadPool>(new ThreadPool());
        socket_handler_pool->SetMaxPoolSize(size);
	}

	void HttpServer::Start()
	{
		if (serverStatus == ServerStatus::kRunning)
		{
			std::cout << "Server is alreadly running.\n";
			return;
		}
		serverStatus = ServerStatus::kRunning;
		std::cout << "Server starts on " << acceptor.local_endpoint().address().to_string() << ":" << acceptor.local_endpoint().port() << ".\n";
		StartAccept();
	}

	void HttpServer::StartAccept()
	{
		//	create a new socket
		socket = SocketPointer(new boost::asio::ip::tcp::socket(ioContext));
		//  wait for client connection (async)
		acceptor.async_accept(*socket,
			boost::bind(&HttpServer::HandleAccept, this, boost::asio::placeholders::error));
	}

	void HttpServer::HandleAccept(const boost::system::error_code& error)
	{
		std::cout << "\nSocket connected.\t(" << socket->remote_endpoint().address().to_string() << ":" << socket->remote_endpoint().port() << ")\n";

		if (!error)
		{
            std::thread freeThread = socket_handler_pool->GetThread();

			if (freeThread != nullptr)
			{
				std::cout << "The socket is taken by a thread.\n";
				//	TODO: assign the connected socket to a thread 
                //  ...
			}
			else
			{
				std::cout << "No available thread for this connection...\n";
				//	TODO: maybe send a "server busy response"?
				std::cout << "Socket closed.\t\t(" << socket->remote_endpoint().address().to_string() << ":" << socket->remote_endpoint().port() << ")\n";
				//	abandond this socket
				socket->WriteSocket("HTTP/1.1 500 OK\r\n\r\n");
				socket->close();
			}
		}
		//	keep accept for another client connection
		StartAccept();
	}

	void HttpServer::Shutdown()
	{
		// TODO: Close all the threads and async-works
		serverStatus = ServerStatus::kStopped;
	}

	int HttpServer::GetClientCount()
	{
        return socket_handler_pool->GetcurPoolSize();
	}


}
