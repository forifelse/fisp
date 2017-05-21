#include "stdafx.h"
#include "mainlgc.h"
//#include "src\WebsocketClient.h"
//#include "..\WebsocketProtocol\src\WebsocketDataMessage.h"
#include <io.h>

WebLgc::WebLgc()
	:mpFileIO(nullptr)
	,mpJson(nullptr)
{
	mpJson = JSRap::createMem<JSRap>();
}

WebLgc::~WebLgc()
{
	if(nullptr != mpFileIO)
	{
		mpFileIO->close();
		delete mpFileIO;
		mpFileIO = nullptr;
	}
	JSRap::destroyMem<JSRap>(mpJson);
}

void WebLgc::writeLog(const String& strLog) const
{
	String strMsg = String::sGetSystemTime() + strLog;
	cout << strMsg.getChar() << endl;
}

bool WebLgc::onEcho(const MsgPackage& msgReceived, MsgPackage& msgReply)
{
	bool bReply = proceMsg(msgReceived, msgReply);
	return bReply;
}

void WebLgc::parseMsg(const MsgPackage& msgReceived)
{
	//received msg format:
	// cmd:msg:user:extra
	mvCmd.clear();
	mvMsg.clear();
	mvUser.clear();
	mvExtra.clear();
	//
	mvRaw = msgReceived.payload().split(":", false);
	if (mvRaw.size() > 0)
	{
		mvCmd = mvRaw[0].split(",");
	}
	if (mvRaw.size() > 1)
	{
		mvMsg = mvRaw[1].split(",");
	}
	if (mvRaw.size() > 2)
	{
		mvUser = mvRaw[2].split(",");
	}
	if (mvRaw.size() > 3)
	{
		mvExtra = mvRaw[3].split(",");
	}
}

bool WebLgc::proceMsg(const MsgPackage& msgReceived, MsgPackage& msgReply)
{
	parseMsg(msgReceived);
	msgReply.clear();
	//
	bool bReply = false;
	if (isFor("check"))
	{
		msgReply.makePkg("check");
	}
	else if (isFor("signup"))
	{
		msgReply.makePkg("error:failed. account exsit!");
		bool bOk = mpJson->open(mdbPath.users() + "user.json");
		if (mvMsg.size() >= 3 && !mpJson->find(mvMsg[0]))
		{
			mpJson->put<uint>(mvMsg[0], "id", mpJson->size());
			mpJson->put<const char*>(mvMsg[0], "pw", mvMsg[1].getChar());
			mpJson->put<const char*>(mvMsg[0], "email", mvMsg[2].getChar());
			mpJson->put<const char*>(mvMsg[0], "scene", "");
			buildFolder(mvMsg[0]);
			msgReply.makePkg("signup:create account ok!");
		}
		mpJson->save();
		mpJson->close();
	}
	else if (isFor("signin"))
	{
		msgReply.makePkg("error:name or password mismatch!");
		if(mvMsg.size() >= 2)
		{
			bool bOk = mpJson->open(mdbPath.users() + "user.json");
			const String strPW = mpJson->findVal<const char*>(mvMsg[0] + ".pw", "");
			if (strPW == mvMsg[1])
			{
				msgReply.makePkg(String("signin:") + mvMsg[0]);
				//if (nullptr != pClient)
				//{
				//	WebsocketClient* pClt = (WebsocketClient*)pClient;
				//	pClt->loginName(mvMsg[0].getString());
				//}
			}
			mpJson->close();
		}
	}
	else if (isFor("signout"))
	{
		//if (nullptr != pClient)
		//{
		//	WebsocketClient* pClt = (WebsocketClient*)pClient;
		//	pClt->loginName("");
		//}
	}
	else if (isFor("chat"))
	{
		msgReply.makePkg(msgReceived.payload(), 1);

		//
		//if (isFor("chat") || (isFor("stream") && mvCmd.size() == 1))
		//{
		//	mvMsg.resize(1);
		//	String strLeft;
		//	msgReceived.payload().split(":", strLeft, mvMsg[0], true);
		//	mvMsg[0].trimRight(":");
		//}
	}
	else if (isFor("newscene"))
	{
		String strSceneList;
		bool bOk = newScene(mvUser[0], mvMsg[0], &strSceneList);
		if (bOk)
		{
			msgReply.makePkg(String("newscene:") + strSceneList);
		}
		else
		{
			msgReply.makePkg(String("error:failed. scene - ") + mvMsg[0] + String(" already exsit!"));
		}
	}
	else if (isFor("delscene"))
	{
		String strSceneList;
		bool bOk = delScene(mvUser[0], mvMsg[0], &strSceneList);
		if (bOk)
		{
			msgReply.makePkg(String("delscene:") + strSceneList);
		}
		else
		{
			msgReply.makePkg(String("error:failed. can not delete scene - ") + mvMsg[0] + String(" or scene not exsit!"));
		}
	}
	//	else if(isFor("kindlist"))
	//	{
	//		const String strPathFile = mstrExePath + "data\\scenelist.ini";
	//		//msgReply.makePkg(WinFun::sReadProfile("kindofscene","kind",strPathFile);
	//	}
	//	else if(isFor("scenelist"))
	//	{
	//		msgReply.makePkg("scenelist:";
	//		const bool bPublic = (mvUser.size() <= 0 || mvUser[0].isEmpty());
	//		if (bPublic) {
	//		}
	//		else {
	//			bool bOk = mpJsonCpp->open(mstrSvrDataPath + "user.json");
	//			JsonCpp::Node* pRoot = (JsonCpp::Node*)mpJsonCpp->root();
	//			String strCurScene = pRoot->getString(mvUser[0] + ".scene");
	//			strMsgReply += strCurScene;
	//		}
	//	}
	//	else if(isFor("geolist"))
	//	{
	//		msgReply.makePkg(mvRaw[0];
	//		strMsgReply += ":";
	//		if(mvCmd[1] == "3")
	//		{
	//			strMsgReply += FileSys::fileList(mstrDataPath + "\\source\\models\\mesh","js",nullptr,true);
	//		}
	//		else if(mvCmd[1] == "4")
	//		{
	//			strMsgReply += FileSys::fileList(mstrDataPath + "\\source\\models\\morph","js",nullptr,true);
	//		}
	//		else if(mvCmd[1] == "5")
	//		{
	//			strMsgReply += FileSys::fileList(mstrDataPath + "\\source\\models\\skin","js",nullptr,true);
	//		}
	//	}
	//	else if(isFor("clearscene") || isFor("clearobject") || isFor("clearlight"))
	//	{
	//		if(mvUser.size() <= 0 || mvUser[0].isEmpty())
	//		{
	//			return false;
	//		}
	//		//
	//		//msgReply.makePkg("";
	//		const String strDir = mstrExePath + "data\\" + mvUser[0];
	//		const String strPathFile = strDir + "\\" + mvMsg[0] + ".ini";//"\\scene.ini";
	//		//
	//		uint uCnt = 0;
	//		if(isFor("clearscene") || isFor("clearobject"))
	//		{
	//			//WinFun::sReadProfile("scene","size",strPathFile,&uCnt);
	//			//for(uint i=0; i<uCnt; i++)
	//			//{
	//			//	WinFun::sWriteProfile("scene",String(i),nullptr,strPathFile);
	//			//}
	//			//WinFun::sWriteProfile("scene","size",0,strPathFile);
	//		}
	//		if(isFor("clearscene") || isFor("clearlight"))
	//		{
	//			//WinFun::sReadProfile("light","size",strPathFile,&uCnt);
	//			//for(uint i=0; i<uCnt; i++)
	//			//{
	//			//	WinFun::sWriteProfile("light",String(i),nullptr,strPathFile);
	//			//}
	//			//WinFun::sWriteProfile("light","size",0,strPathFile);
	//		}
	//	}
	//	else if(isFor("saveobject") || isFor("savelight"))
	//	{
	//		if(mvUser.size() <= 0 || mvUser[0].isEmpty() || mvCmd.size() < 2)
	//		{
	//			return false;
	//		}
	//		//
	//		msgReply.makePkg(mvCmd[0] + String(":");
	//		const String strDir = mstrExePath + "data\\" + mvUser[0];
	//		const String strPathFile = strDir + "\\" + mvCmd[1] + ".ini";//"\\scene.ini";
	//		//
	//		if(_access(strDir.getChar(),0) != 0)
	//		{
	//			FileSys::createDir(strDir);
	//			//WinFun::sWriteProfile("scene","user",mvUser[0],strPathFile);
	//		}
	//		//
	//		String strRecord = mvRaw[1];
	//		String strApp;
	//		if(isFor("saveobject"))
	//		{
	//			strApp = "scene";
	//		}
	//		else if(isFor("savelight"))
	//		{
	//			strApp = "light";
	//		}
	//		//WinFun::sWriteProfile(strApp,mvCmd[2],strRecord,strPathFile);
	//		if(mvCmd.size() > 3)
	//		{
	//			//WinFun::sWriteProfile(strApp,"size",String(mvCmd[3]),strPathFile);
	//		}
	//	}
	//	else if(isFor("addobj") || isFor("addlit"))
	//	{
	//		if(mvUser.size() <= 0 || mvUser[0].isEmpty() || mvCmd.size() < 2)
	//		{
	//			return false;
	//		}
	//		//
	//		msgReply.makePkg(mvCmd[0] + String(":");
	//		const String strDir = mstrExePath + "data\\" + mvUser[0];
	//		const String strPathFile = strDir + "\\" + mvCmd[1] + ".ini";//"\\scene.ini";
	//		//
	//		if(::_access(strDir.getChar(),0) != 0)
	//		{
	//			FileSys::createDir(strDir);
	//			//WinFun::sWriteProfile("scene","user",mvUser[0],strPathFile);
	//		}
	//		//
	//		String strRecord = mvRaw[1];
	//		uint uCnt = 0;
	//		bool bFind = false;
	//		uint uKeyIdx = 1, uRecIdx = mvCmd[2].toUInt();
	//		String strApp;
	//		if(isFor("addobj"))
	//		{
	//			strApp = "scene";
	//		}
	//		else if(isFor("addlit"))
	//		{
	//			strApp = "light";
	//		}
	//		bFind = findRecord(strPathFile,strApp,mvMsg[uKeyIdx],uKeyIdx,&uRecIdx);
	//		if(!bFind)
	//		{
	//			//WinFun::sReadProfile(strApp,"size",strPathFile,&uCnt);
	//			uRecIdx = uCnt ++;
	//			//WinFun::sWriteProfile(strApp,"size",String(uCnt),strPathFile);
	//		}
	//		//WinFun::sWriteProfile(strApp,uRecIdx,strRecord,strPathFile);
	//	}
	//	else if(isFor("remobj") || isFor("remlit"))
	//	{
	//		if(mvUser.size() <= 0 || mvUser[0].isEmpty() || mvCmd.size() < 2)
	//		{
	//			return false;
	//		}
	//		//
	//		msgReply.makePkg(mvCmd[0] + String(":");
	//		const String strDir = mstrExePath + "data\\" + mvUser[0];
	//		const String strPathFile = strDir + "\\" + mvCmd[1] + ".ini";//"\\scene.ini";
	//		//
	//		if(::_access(strDir.getChar(),0) != 0 || ::_access(strPathFile.getChar(),0) != 0)
	//		{
	//			msgReply.makePkg("";
	//			return false;
	//		}
	//		//
	//		String strRecord;
	//		uint uCnt = 0;
	//		bool bFind = false;
	//		uint uKeyIdx = 1, uRecIdx = mvCmd[2].toUInt();
	//		String strApp;
	//		if(isFor("remobj"))
	//		{
	//			strApp = "scene";
	//		}
	//		else if(isFor("remlit"))
	//		{
	//			strApp = "light";
	//		}
	//		bFind = findRecord(strPathFile,strApp,mvMsg[uKeyIdx],uKeyIdx,&uRecIdx);
	//		//WinFun::sReadProfile(strApp,"size",strPathFile,&uCnt);
	//		if(bFind && uCnt > 0 && uRecIdx < uCnt)
	//		{
	//			uCnt --;
	//			if(uRecIdx < uCnt)
	//			{
	//				//strRecord = WinFun::sReadProfile(strApp,String(uCnt),strPathFile);
	//				//WinFun::sWriteProfile(strApp,uRecIdx,strRecord,strPathFile);
	//			}
	//			//WinFun::sWriteProfile(strApp,String(uCnt),nullptr,strPathFile);
	//			//WinFun::sWriteProfile(strApp,"size",String(uCnt),strPathFile);
	//		}
	//	}
	//	else if(isFor("loadlight") || isFor("loadobject"))
	//	{
	//		String strUser;
	//		String strRecord;
	//		uint uCnt = 0;
	//		if(mvUser.size() <= 0 || mvUser[0].isEmpty())
	//		{
	//			TArray<String> vstr;
	//			const String strScenelist = mstrExePath +  "data\\scenelist.ini";
	//			//WinFun::sReadProfile("scene","size",strScenelist,&uCnt);
	//			for(uint i=0; i<uCnt; i++)
	//			{
	//				//strRecord = WinFun::sReadProfile("scene",i,strScenelist);
	//				vstr = strRecord.split(",");
	//				if(vstr.size() > 1 && vstr[0] == mvMsg[0])
	//				{
	//					strUser = vstr[1];
	//				}
	//			}
	//		}
	//		else
	//		{
	//			strUser = mvUser[0];
	//		}
	//		//
	//		const String strDir = mstrExePath + "data\\" + strUser;
	//		const String strPathFile = strDir + "\\" + mvMsg[0] + ".ini";//"\\scene.ini";
	//		//
	//		if(::_access(strDir.getChar(),0) != 0 || ::_access(strPathFile.getChar(),0) != 0)
	//		{
	//			return false;
	//		}
	//		//
	//		if(nullptr != vReply)
	//		{
	//			if(isFor("loadlight"))
	//			{
	//				//WinFun::sReadProfile("light","size",strPathFile,&uCnt);
	//				if(uCnt > 0)
	//				{
	//					vReply->resize(uCnt);
	//					for(uint i=0; i<uCnt; i++)
	//					{
	//						//strRecord = WinFun::sReadProfile("light",i,strPathFile);
	//						(*vReply)[i] = String("loadlight:") + strRecord;
	//					}
	//				}
	//			}
	//			else if(isFor("loadobject"))
	//			{
	//				//WinFun::sReadProfile("scene","size",strPathFile,&uCnt);
	//				if(uCnt > 0)
	//				{
	//					vReply->resize(uCnt);
	//					for(uint i=0; i<uCnt; i++)
	//					{
	//						//strRecord = WinFun::sReadProfile("scene",i,strPathFile);
	//						(*vReply)[i] = String("loadobject:") + strRecord;
	//					}
	//				}
	//			}		
	//		}
	//	}
	//	else if(isFor("stream"))
	//	{
	//		procStream(pClient,strMsgReply,vReply);
	//	}
	bReply = !msgReply.payload().isEmpty();
	return bReply;
}

//bool WebLgc::parseMsg(LogicalConnection* pClient,const WebsocketDataMessage& msgData,const String& strMsgRecPart1,const String& strMsgRecPart2,String &strMsgReply,TArray<String>* vReply /* = nullptr */)
//{
//	parseMsg(msgData,strMsgRecPart1,strMsgRecPart2);
//	//
//	msgReply.makePkg("";
//	if(nullptr != vReply)
//	{
//		vReply->clear();
//	}
//	//

//
//	return true;
//}
//
//void WebLgc::procStream(LogicalConnection* pClient,String &strMsgReply,TArray<String>* vReply /* = nullptr */)
//{
//	if(mvCmd.size() > 1 && mvCmd[1].compareIgnoreCase("start"))
//	{
//		mstrStreamFile = mvMsg[0];
//		mstrStream = "";
//		if(nullptr == mpFileIO)
//		{
//			mpFileIO = new FileIO;
//		}
//		mpFileIO->open(mstrDataPath + "\\temp\\" + mstrStreamFile,EFileMode::File_Mode_Write);
//		mpFileIO->close();
//		mpFileIO->open(mstrDataPath + "\\temp\\" + mstrStreamFile,EFileMode::File_Mode_WriteAppend);
//	}
//	else if(mvCmd.size() > 1 && mvCmd[1].compareIgnoreCase("end"))
//	{
//		msgReply.makePkg("stream";
//		//mpFileIO->write(mstrStream);
//		mpFileIO->close();
//	}
//	else if(mvCmd.size() == 1 && mvMsg.size() > 0 && !mvMsg[0].isEmpty())
//	{
//		//mstrStream += mvMsg[0];
//		mpFileIO->write(mvMsg[0]);
//		mpFileIO->flush();
//	}
//}
//
//bool WebLgc::parseGroupMsg(const WebsocketDataMessage& msgData,const String& strMsgRecPart1,const String& strMsgRecPart2,String &strMsgReply,TArray<String>* vReply /* = nullptr */)
//{
//	parseMsg(msgData,strMsgRecPart1,strMsgRecPart2);
//	//
//	msgReply.makePkg("";
//	if(nullptr != vReply)
//	{
//		vReply->clear();
//	}
//	//
//	if(isFor("chat"))
//	{
//		msgReply.makePkg(String("chat:");
//		strMsgReply += mvRaw[1];
//		strMsgReply += String(":");
//		strMsgReply += mvUser[0];
//	}
//	return true;
//}

bool WebLgc::isFor(const String& strCmd) const
{
	bool bRe = false;
	if(!strCmd.isEmpty() && mvCmd.size() > 0)
	{
		bRe = (strCmd == mvCmd[0]);
	}
	return bRe;
}

bool WebLgc::hasScene(const String& strScene) const
{
	if(strScene.isEmpty())
	{
		return false;
	}
	bool bRe = false;
	const String strPathFile = mdbPath.exePath() + "data\\scenelist.ini";
	String strRecord;
	TArray<String> vstr;
	uint uCnt = 0;
	//WinFun::sReadProfile("scene","size",strPathFile,&uCnt);
	for(uint i=0; i<uCnt; i++)
	{
		//strRecord = WinFun::sReadProfile("scene",String(i),strPathFile);
		vstr = strRecord.split(",");
		if(vstr.size() > 0 && vstr[0] == (strScene))
		{
			bRe = true;
			break;
		}
	}
	return bRe;
}

void WebLgc::dataPath(const String& strPath)
{
}

const String& WebLgc::dataPath() const
{
	return "";
}

bool WebLgc::findRecord(const String& strPathFile,const String& strApp, const String& strKey,uint uKeyIdx /* = 0 */,uint* uRecIdx /* = nullptr */) const
{
	bool bFind = false;
	String strRecord;
	TArray<String> vstr;
	if(nullptr != uRecIdx)
	{
		//strRecord = WinFun::sReadProfile(strApp,String(*uRecIdx),strPathFile);
		vstr = strRecord.split(",");
		if(vstr.size() > uKeyIdx && vstr[uKeyIdx] == strKey)
		{
			return true;
		}
	}
	uint uCnt = 0;
	//WinFun::sReadProfile(strApp,"size",strPathFile,&uCnt);
	for(uint i=0; i<uCnt; i++)
	{
		//strRecord = WinFun::sReadProfile(strApp,String(i),strPathFile);
		vstr = strRecord.split(",");
		if(vstr.size() > uKeyIdx && vstr[uKeyIdx] == strKey)
		{
			bFind = true;
			if(nullptr != uRecIdx)
			{
				*uRecIdx = i;
			}
			break;
		}
	}
	return bFind;
}

const WebLgc::MsgType& WebLgc::type() const
{
	return meType;
}

const TArray<String>& WebLgc::cmd() const
{
	return mvCmd;
}

const TArray<String>& WebLgc::msg() const
{
	return mvMsg;
}

const TArray<String>& WebLgc::user() const
{
	return mvUser;
}

const TArray<String>& WebLgc::rawString() const
{
	return mvRaw;
}

DBPath* WebLgc::dbPath()
{
	return &mdbPath;
}

const DBPath* WebLgc::dbPath() const
{
	return &mdbPath;
}

void WebLgc::buildFolder(const String& strUser)
{
	FileSys::createDir(mdbPath.users() + strUser);
	//FileSys::createDir(mdbPath.dataPath() + strUser);
}

bool WebLgc::newScene(const String& strUser, const String& strScene, String* strSceneList /* = nullptr */)
{
	bool bOk = mpJson->open(mdbPath.dataPath() + "user.json");
	//JsonRap::Node* pRoot = (JsonRap::Node*)mpJson->root();
	//String strCurScene = pRoot->getString(strUser + ".scene");
	//if (strCurScene.find(strScene))
	//{
	//	return false;
	//}
	//if (!strCurScene.isEmpty())
	//{
	//	strCurScene += String(",");
	//}
	//strCurScene += strScene;
	//pRoot->putString(strUser + ".scene", strCurScene);
	mpJson->save();
	mpJson->close();
	//
	if (nullptr != strSceneList)
	{
		//*strSceneList = strCurScene;

		//bOk = mpJsonCpp->open(mstrSvrDataPath + "user.json");
		//pRoot = (JsonCpp::Node*)mpJsonCpp->root();
		//*strSceneList = pRoot->getString(strUser + ".scene");
		//mpJsonCpp->close();
	}
	//
	//IFileIO::sCreateFile(mstrSvrDataPath + strUser + "\\" + strScene + ".json","{}");
	//SceneSerialize::createScene(mstrSvrDataPath + strUser + "\\" + strScene + ".json");
	return true;
}

bool WebLgc::delScene(const String& strUser, const String& strScene, String* strSceneList /* = nullptr */)
{
	//bool bOk = mpJson->open(mdbPath.dataPath() + "user.json");
	//JsonRap::Node* pRoot = (JsonRap::Node*)mpJson->root();
	//String strCurScene = pRoot->getString(strUser + ".scene");
	//if (!strCurScene.find(strScene))
	//{
	//	return false;
	//}
	//if (!strCurScene.remove(strScene + String(","), true))
	//{
	//	if (!strCurScene.remove(String(",") + strScene, true))
	//	{
	//		strCurScene = "";
	//	}
	//}
	//pRoot->putString(strUser + ".scene", strCurScene);
	//mpJson->save();
	//mpJson->close();
	////
	//if (nullptr != strSceneList)
	//{
	//	*strSceneList = strCurScene;

	//	//bOk = mpJsonCpp->open(mstrSvrDataPath + "user.json");
	//	//pRoot = (JsonCpp::Node*)mpJsonCpp->root();
	//	//*strSceneList = pRoot->getString(strUser + ".scene");
	//	//mpJsonCpp->close();
	//}
	////
	//FileSys::deleteFile(mdbPath.dataPath() + strUser + "\\" + strScene + ".json");
	return true;
}