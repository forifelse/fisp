/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "inshare.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class MsgPackage
		------------------------------------------------------------*/
		class MsgPackage : public IRoot
		{
		public:
			MsgPackage();
			MsgPackage(const MsgPackage& o);
			virtual ~MsgPackage();
			MsgPackage& operator = (const MsgPackage& o);
			void makePkg(const String& strPayload, uint uMsgType = 0, word wOpcode = 0);
			void clear();
			void msgType(uint uMsgType);
			uint msgType() const;
			void payload(const String& strPayload);
			const String& payload() const;
			void opcode(word wOpcode);
			word opcode() const;
			void msgFrom(std::weak_ptr<void> pSend);
			std::weak_ptr<void> msgFrom() const;

		protected:
			void copyFrom(const MsgPackage& o);

		private:
			uint	muMsgType;		// 0: subscribe, 1: broadcast, 2: group, 3:stream
			String	mstrPayload;	// cmd:msg:user:extra
			word	mwOpcode;		// 0:text, 1:binary, 2:
			std::weak_ptr<void>	mpMsgFrom;
			//bool	mbReceived;		// T: received, F : send
		};

		/*-----------------------------------------------------------
		class ISocket
		------------------------------------------------------------*/
		class ISocket : public IRoot
		{
		public:
			virtual void send(const MsgPackage& msg) = 0;
		};

		/*-----------------------------------------------------------
		class IMsgHandler
		------------------------------------------------------------*/
		class IMsgHandler : public IRoot
		{
		public:
			virtual bool onEcho(const MsgPackage& msgReceived, MsgPackage& msgReply) = 0;

		public:
			void socket(ISocket* pSocket) { mpSocket = pSocket; }

		private:
			ISocket*	mpSocket;
		};

		///*-----------------------------------------------------------
		//class ISeverHandler
		//------------------------------------------------------------*/
		//class ISeverHandler : public IMsgHandler
		//{
		//public:
		//};

		///*-----------------------------------------------------------
		//class IClientHandler
		//------------------------------------------------------------*/
		//class IClientHandler : public IMsgHandler
		//{
		//public:
		//};

		/*-----------------------------------------------------------
		class IServer
		------------------------------------------------------------*/
		class IServer : public IRoot
		{
		public:
			virtual void run(uint uPort) = 0;
			virtual void msgHandler(IMsgHandler* pMsgHandler) = 0;
		};

		/*-----------------------------------------------------------
		class IClient
		------------------------------------------------------------*/
		class IClient : public IRoot
		{
		public:
		};

		/*-----------------------------------------------------------
		class ICSServer
		------------------------------------------------------------*/
		class ICSServer : public IServer
		{
		public:
		};

		/*-----------------------------------------------------------
		class ICSClient
		------------------------------------------------------------*/
		class ICSClient : public IClient
		{
		public:
		};

		/*-----------------------------------------------------------
		class IWebServer
		------------------------------------------------------------*/
		class IWebServer : public IServer
		{
		public:
		};

		/*-----------------------------------------------------------
		class IWebClient
		------------------------------------------------------------*/
		class IWebClient : public IClient
		{
		public:
		};




	}
}