/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/net.h"

namespace fisp
{
	namespace auxisys
	{
		/*-----------------------------------------------------------
		class WebSocket
		------------------------------------------------------------*/
		WebSocket::WebSocket()
			: mstrName("")
			, mstrID("")
		{
		}

		WebSocket::WebSocket(std::weak_ptr<void> socket)
			: mstrName("")
			, mstrID("")
			, mSocket(socket)
		{
		}

		WebSocket::WebSocket(std::weak_ptr<void> socket, const String& strID)
			: mstrName("")
			, mstrID(strID)
			, mSocket(socket)
		{
		}

		WebSocket::WebSocket(const WebSocket& o)
			: mstrName("")
			, mstrID("")
		{
			copyFrom(o);
		}

		WebSocket::~WebSocket()
		{
			mstrName = "";
			mstrID = "";
		}

		WebSocket& WebSocket::operator = (const WebSocket& o)
		{
			copyFrom(o);
			return *this;
		}

		bool WebSocket::operator == (const WebSocket& o) const
		{
			return (mSocket._Get() == o.mSocket._Get());
		}

		bool WebSocket::operator != (const WebSocket& o) const
		{
			return !(this->operator==(o));
		}

		void WebSocket::copyFrom(const WebSocket& o)
		{
			mstrName = o.mstrName;
			mstrID = o.mstrID;
			mSocket = o.mSocket;
		}

		void WebSocket::send(const MsgPackage& msg)
		{
		}

		void* WebSocket::socket()
		{
			return &mSocket;
		}

		void WebSocket::userID(ulong uID)
		{
			muID = uID;
		}

		ulong WebSocket::userID() const
		{
			return muID;
		}

		void WebSocket::userName(const String& strName)
		{
			mstrName = strName;
		}

		String WebSocket::userName() const
		{
			return mstrName;
		}

		/*-----------------------------------------------------------
		class WebServer
		------------------------------------------------------------*/
		WebServer::WebServer()
			: mpSocket(nullptr)
			, mpMsgHandler(nullptr)
		{
		}

		WebServer::WebServer(IMsgHandler* pMsgHandler)
			: mpSocket(nullptr)
			, mpMsgHandler(pMsgHandler)
		{
		}

		WebServer::~WebServer()
		{
			mpSocket = nullptr;
			mpMsgHandler = nullptr;
		}

		bool WebServer::doCreate(void* pInitParam /* = nullptr */)
		{
			// Set logging settings
			mServerEP.set_error_channels(websocketpp::log::elevel::none); //(websocketpp::log::elevel::all);
			mServerEP.set_access_channels(websocketpp::log::elevel::none);// (websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

			// Initialize Asio
			mServerEP.init_asio();

			// Set the handler to the echo handler
			mServerEP.set_open_handler(std::bind(&WebServer::onOpen, this, std::placeholders::_1));
			mServerEP.set_close_handler(std::bind(&WebServer::onClose, this, std::placeholders::_1));
			mServerEP.set_message_handler(std::bind(&WebServer::onMsg, this, std::placeholders::_1, std::placeholders::_2));
			//
			return true;
		}

		void WebServer::doDestroy()
		{

		}

		void WebServer::onOpen(websocketpp::connection_hdl hdl)
		{
			const String& strTimestamp = Timer::timestamp();
			{
				std::lock_guard<std::mutex> guard(mlockSocket);
				mSocketList.push(WebSocket(hdl, strTimestamp));
			}
			mMsgReply.makePkg(String("onopen:") + strTimestamp, 0, 1);
			websocketpp::frame::opcode::value opcode = (websocketpp::frame::opcode::value)mMsgReply.opcode();
			mServerEP.send(hdl, mMsgReply.payload().getString(), opcode);
			//
			cout << Timer::systemTime().getString() + " add socket! count: " << mSocketList.size() << endl;
		}

		void WebServer::onClose(websocketpp::connection_hdl hdl)
		{
			std::lock_guard<std::mutex> guard(mlockSocket);
			mSocketList.remove(WebSocket(hdl));
			//
			cout << Timer::systemTime().getString() + " del socket! count: " << mSocketList.size() << endl;
		}

		void WebServer::onMsg(websocketpp::connection_hdl hdl, TypeServer::message_ptr msg)
		{
			mMsgReceived.makePkg(msg->get_payload(), 0, msg->get_opcode());
			mMsgReceived.msgFrom(hdl);
			{
				std::lock_guard<std::mutex> guard(mlockMsgpkg);
				mMsgpkgList.push(mMsgReceived);
			}
			mCondVal.notify_one();
		}

		void WebServer::run(uint uPort)
		{
			// Listen
			mServerEP.listen(uPort);

			// Queues a connection accept operation
			mServerEP.start_accept();

			// create msg process thread
			std::thread thMsg(&WebServer::procMsgpool, this, nullptr);
			thMsg.detach();

			// Start the Asio io_service run loop
			thread thMain =	std::thread(&WebServer::threadWorker, this, nullptr);
			cout << "WebServer start ..." << endl << "Listen on port: " << uPort << endl;
			thMain.join();
		}

		void WebServer::threadWorker(void* pParam)
		{
			mServerEP.run();
		}

		void WebServer::msgHandler(IMsgHandler* pMsgHandler)
		{
			mpMsgHandler = pMsgHandler;
		}

		void WebServer::procMsgpool(void* pParam)
		{
			while (true)
			{
				MsgPackage msg;
				{
					std::unique_lock<mutex> lock(mlockMsgpkg);
					while (mMsgpkgList.size() <= 0)
						mCondVal.wait(lock);
					msg = mMsgpkgList.pop();
					lock.unlock();
				}
				bool bReply = mpMsgHandler->onEcho(msg, mMsgReply);
				//
				if (bReply)
				{
					mMsgReply.opcode(msg.opcode());
					std::lock_guard<std::mutex> guard(mlockSocket);
					if (0 == mMsgReply.msgType())
					{
						websocketpp::connection_hdl hdl = (websocketpp::connection_hdl)msg.msgFrom();
						websocketpp::frame::opcode::value opcode = (websocketpp::frame::opcode::value)mMsgReply.opcode();
						mServerEP.send(hdl, mMsgReply.payload().getString(), opcode);
					}
					else if (1 == mMsgReply.msgType())
					{
						WebSocket wstemp;
						for (mSocketList.begin(); !mSocketList.isEnd(); mSocketList.next())
						{
							wstemp = mSocketList.itVal();
							websocketpp::connection_hdl* hdl = (websocketpp::connection_hdl*)wstemp.socket();
							websocketpp::frame::opcode::value opcode = (websocketpp::frame::opcode::value)mMsgReply.opcode();
							mServerEP.send(*hdl, mMsgReply.payload().getString(), opcode);
						}
					}
				}
			}
		}

		void WebServer::useIDLogin(unsigned long long *uID /* = nullptr */)
		{
			static unsigned long long id = 0;
			static const unsigned long long idMax = 18446744073709551615;//2^64-1
			char sz[64] = { 0 };
			if (NULL != uID)
			{
				::itoa(*uID, sz, 10);
			}
			else
			{
				::itoa(id, sz, 10);
				id++;
				if (id >= idMax)
				{
					id = 0;
				}
			}
			//arg1 = sz;
			//raw = "0" + arg1;
			//if (!arg2.empty())
			//{
			//	raw += "|" + arg2;
			//}
		}



	}
}