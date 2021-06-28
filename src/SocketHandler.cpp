/*
Copyright (c) 2021 Chiu Yen-Chen, Swen Sun-Yen, Wen Yong-Wei, Yuan Wei-Chen.
All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file. See the AUTHORS file for names of contributors.
 */
#include "SocketHandler.h"

namespace shortlink {

	SocketHandler::pointer SocketHandler::Create()
	{
		return pointer(new SocketHandler());
	}

	void SocketHandler::StartWorkingThread()
	{
		if (threadRunning) return;
		workingThread = std::thread(&SocketHandler::LoopingWork, this);
		threadRunning = true;
	}

	void SocketHandler::AssignSocket(const SocketPointer& newSocket)
	{
		socket = newSocket;
	}

	void SocketHandler::LoopingWork()
	{
		//  infinite loop for a thread
		while (true)
		{
			if (socket == NULL)
			{
				socketWorking = false;
			}
			else if (socket->is_open())
			{
				try
				{
					socketWorking = true;

					//	read socket
					std::string recievedMessage = ReadSocket();
					std::cout << "Message recieved:\n";
					std::cout << recievedMessage << "\n";

					//	handle message
					std::string responseMessage = HandleMessage(recievedMessage);
					
					///	fake delay...
					std::this_thread::sleep_for(std::chrono::seconds(5));

					//	write socket
					WriteSocket(responseMessage);
					std::cout << "Write message:\n";
					std::cout << responseMessage << "\n";

					//	disconnect socket
					CloseSocket();
				}
				catch (boost::system::error_code e)
				{
					//  TODO: handle exception...
					CloseSocket();
				}
			}
			else
			{
				CloseSocket();
			}
		}
	}

	void SocketHandler::WriteSocket(std::string message)
	{
		boost::asio::write(*socket, boost::asio::buffer(message));
	}

	std::string SocketHandler::ReadSocket()
	{
		std::string recievedMessage = "";
		boost::array<char, 128> recievedBuffer;
		boost::system::error_code errorCode;
		std::size_t bytesTransferred;

		std::cout << "Start reading message...\n";

		while (true)
		{
			//  socket.read_some() waits for the incomming message from the client
			bytesTransferred = socket->read_some(boost::asio::buffer(recievedBuffer), errorCode);

			if (bytesTransferred == 0)
			{
				return recievedMessage;
			}
			else if (!errorCode)
			{
				//  Append message
				recievedMessage = recievedMessage.append(recievedBuffer.data(), bytesTransferred);
				//  Stop reading if met a double CRLF.
				if (recievedMessage.find("\r\n\r\n") != std::string::npos)
					return recievedMessage;
			}
			else if (errorCode == boost::asio::error::eof)
			{
				//  socket disconnected
				return "eof";
			}
			else
			{
				std::cout << "error\n";
				return recievedMessage;
				//throw errorCode;
			}
		}
	}

	std::string SocketHandler::HandleMessage(std::string message)
	{
		Worker worker;
		worker.Run(message);
		return worker.SendResponse();
	}

	void SocketHandler::CloseSocket()
	{
		std::cout << "Socket closed.\t\t(" << socket->remote_endpoint().address().to_string() << ":" << socket->remote_endpoint().port() << ")\n";
		socket->close();
		socket = NULL;
		socketWorking = false;
	}

}