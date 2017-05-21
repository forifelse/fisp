#pragma once
//#include "../utility/include/useutility.h"
#include "../share/include/useshare.h"
using namespace fisp;

class WebLgc : public IMsgHandler
{
public:
	enum MsgType
	{
		LoginCommunication,
		EchoCommunication,
		Routedcommunication,
		GroupCommunication,
		StreamedCommunication,
	};

public:
	WebLgc();
	virtual ~WebLgc();
	bool onEcho(const MsgPackage& msgReceived, MsgPackage& msgReply);

	const WebLgc::MsgType& type() const;
	const TArray<String>& cmd() const;
	const TArray<String>& msg() const;
	const TArray<String>& user() const;
	const TArray<String>& rawString() const;
	DBPath* dbPath();
	const DBPath* dbPath() const;

public:
	void writeLog(const String& strLog) const;
	bool hasScene(const String& strScene) const;
	void dataPath(const String& strPath);
	const String& dataPath() const;

protected:
	bool proceMsg(const MsgPackage& msgReceived, MsgPackage& msgReply);
	void parseMsg(const MsgPackage& msgReceived);
	bool isFor(const String& strCmd) const;

private:
	//void procStream(LogicalConnection* pClient,String &strMsgReply,TArray<String>* vReply = NULL);
	// @uRecIdx: [input/output]
	// input: perhaps is the record, find it firstly. output: really find record index or not set if not found.
	bool findRecord(const String& strPathFile,const String& strApp, const String& strKey,uint uKeyIdx = 0,uint* uRecIdx = nullptr) const;
	void buildFolder(const String& strUser);
	bool newScene(const String& strUser, const String& strScene, String* strSceneList = nullptr);
	bool delScene(const String& strUser, const String& strScene, String* strSceneList = nullptr);

private:
	MsgType			meType;
	TArray<String>	mvCmd;
	TArray<String>	mvMsg;
	TArray<String>	mvUser;
	TArray<String>	mvExtra;
	TArray<String>	mvRaw;
	//
	DBPath			mdbPath;
	JSRap*			mpJson;
	//
	String			mstrStreamFile;
	String			mstrStream;
	FileIO*			mpFileIO;
};