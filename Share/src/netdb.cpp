/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/netdbif.h"
namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class MsgPackage
		------------------------------------------------------------*/
		MsgPackage::MsgPackage()
			: muMsgType(0)
			, mstrPayload("")
			, mwOpcode(0)
			//, mpMsgFrom(nullptr)
		{
		}

		MsgPackage::MsgPackage(const MsgPackage& o)
			: muMsgType(0)
			, mstrPayload("")
			, mwOpcode(0)
			//, mpMsgFrom(nullptr)
		{
			copyFrom(o);
		}

		MsgPackage::~MsgPackage()
		{
			clear();
		}

		MsgPackage& MsgPackage::operator = (const MsgPackage& o)
		{
			copyFrom(o);
			return *this;
		}

		void MsgPackage::copyFrom(const MsgPackage& o)
		{
			muMsgType = o.muMsgType;
			mstrPayload = o.mstrPayload;
			mwOpcode = o.mwOpcode;
			mpMsgFrom = o.mpMsgFrom;
		}

		void MsgPackage::makePkg(const String& strPayload, uint uMsgType /* = 0 */, word wOpcode /* = 0 */)
		{
			mstrPayload = strPayload;
			muMsgType = uMsgType;
			mwOpcode = wOpcode;
		}

		void MsgPackage::clear()
		{
			muMsgType = 0;
			mstrPayload = "";
			mwOpcode = 0;
			//mpMsgFrom = nullptr;
		}

		void MsgPackage::msgType(uint uMsgType)
		{
			muMsgType = uMsgType;
		}

		uint MsgPackage::msgType() const
		{
			return muMsgType;
		}

		void MsgPackage::payload(const String& strPayload)
		{
			mstrPayload = strPayload;
		}

		const String& MsgPackage::payload() const
		{
			return mstrPayload;
		}

		void MsgPackage::opcode(word wOpcode)
		{
			mwOpcode = wOpcode;
		}

		word MsgPackage::opcode() const
		{
			return mwOpcode;
		}

		void MsgPackage::msgFrom(std::weak_ptr<void> pSend)
		{
			mpMsgFrom = pSend;
		}

		std::weak_ptr<void> MsgPackage::msgFrom() const
		{
			return mpMsgFrom;
		}
		
		







	}
}