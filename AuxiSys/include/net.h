/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "../../Share/include/useShare.h"
#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_INTERNAL_
#include "websocketpp\config\asio_no_tls.hpp"
#include "websocketpp\server.hpp"
#include <functional>

namespace fisp
{
	namespace auxisys
	{
		/*-----------------------------------------------------------
		class Server
		------------------------------------------------------------*/
		class Server : public ICSServer
		{
		public:
		};

		/*-----------------------------------------------------------
		class Client
		------------------------------------------------------------*/
		class Client : public ICSClient
		{
		public:
		};

		/*-----------------------------------------------------------
		class WebSocket
		------------------------------------------------------------*/
		class WebSocket : public ISocket
		{
		public:
			WebSocket();
			WebSocket(std::weak_ptr<void> socket);
			WebSocket(std::weak_ptr<void> socket, const String& strID);
			WebSocket(const WebSocket& o);
			virtual ~WebSocket();
			WebSocket& operator = (const WebSocket& o);
			bool operator == (const WebSocket& o) const;
			bool operator != (const WebSocket& o) const;
			void send(const MsgPackage& msg) override;
			void* socket();
			void userID(ulong uID);
			ulong userID() const;
			void userName(const String& strName);
			String userName() const;

		protected:
			void copyFrom(const WebSocket& o);

		private:
			ulong	muID;
			String	mstrName;
			String	mstrID;	// timestamp;
			std::weak_ptr<void>	mSocket;
		};

		/*-----------------------------------------------------------
		class WebServer
		------------------------------------------------------------*/
		typedef websocketpp::server<websocketpp::config::asio> TypeServer;
		class WebServer : public IWebServer
		{
		public:

		public:
			WebServer();
			virtual ~WebServer();
			WebServer(IMsgHandler* pMsgHandler);
			void run(uint uPort) override;
			void msgHandler(IMsgHandler* pMsgHandler) override;

		protected:
			bool doCreate(void* pInitParam = nullptr) override;
			void doDestroy() override;
			void threadWorker(void* pParam);
			void onOpen(websocketpp::connection_hdl hdl);
			void onClose(websocketpp::connection_hdl hdl);
			void onMsg(websocketpp::connection_hdl hdl, TypeServer::message_ptr msg);
			void procMsgpool(void* pParam);
			void useIDLogin(unsigned long long *uID = nullptr);

		private:
			ISocket*	mpSocket;
			websocketpp::server<websocketpp::config::asio> mServerEP; // end-point
			MsgPackage	mMsgReceived;
			MsgPackage	mMsgReply;
			IMsgHandler*	mpMsgHandler;
			//
			TList<WebSocket>	mSocketList;
			TList<MsgPackage>	mMsgpkgList;
			std::mutex			mlockSocket;
			std::mutex			mlockMsgpkg;
			std::condition_variable	mCondVal;
			//
			Timer				mTimer;
		};

		/*-----------------------------------------------------------
		class WebClient
		------------------------------------------------------------*/
		class WebClient : public IWebClient
		{
		public:
		};





	}
}