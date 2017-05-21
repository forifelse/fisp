/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/filefmt.h"
#include <io.h>
// rapidjson
#include "rapidjson/rapidjson.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

namespace fisp
{
	namespace utility
	{
		///*-----------------------------------------------------------
		//class JsonCpp::Node
		//------------------------------------------------------------*/
		//JsonCpp::Node::Node()
		//{

		//}

		//JsonCpp::Node::~Node()
		//{
		//	mValue.clear();
		//}

		//bool JsonCpp::Node::isEmpty() const
		//{
		//	return mValue.empty();
		//}

		//uint JsonCpp::Node::size() const
		//{
		//	return mValue.size();
		//}

		////virtual IDBNode* child(const String& strChild) const = 0;

		//void JsonCpp::Node::putString(const String& strKey, const String& strVal)
		//{
		//	mValue[strKey.getString()] = strVal.getString();
		//}

		//String JsonCpp::Node::getString(const String& strKey) const
		//{
		//	String val = mValue[strKey.getChar()].asString();
		//	return val;
		//}

		//void JsonCpp::Node::putInt(const String& strKey, int val)
		//{
		//	mValue[strKey.getString()] = val;
		//}

		//int JsonCpp::Node::getInt(const String& strKey) const
		//{
		//	int val = mValue[strKey.getChar()].asInt();
		//	return val;
		//}

		////void putFloat(const String& strKey, float val);

		//float JsonCpp::Node::getFloat(const String& strKey) const
		//{
		//	float val = mValue[strKey.getChar()].asFloat();
		//	return val;
		//}

		////void putBool(const String& strKey, bool val);

		//bool JsonCpp::Node::getBool(const String& strKey) const
		//{
		//	bool val = mValue[strKey.getChar()].asBool();
		//	return val;
		//}

		//bool JsonCpp::Node::getChild(IDBNode* node, const String& strChild) const
		//{
		//	Json::Value val = mValue[strChild.getChar()];
		//	((JsonCpp::Node*)node)->mValue = val;
		//	return val.isNull();
		//}

		//bool JsonCpp::Node::arrayEle(IDBNode* node, uint idx, uint* uSubCnt /* = nullptr */) const
		//{
		//	const uint cnt = mValue.size();
		//	if (nullptr == node || idx >= cnt)
		//		return false;
		//	Json::Value val = mValue[idx];
		//	((JsonCpp::Node*)node)->mValue = val;
		//	if (nullptr != uSubCnt)
		//		*uSubCnt = cnt;
		//	return val.isNull();
		//}

		//void JsonCpp::Node::arrayData(float* &pData, uint &uSize) const
		//{
		//	const uint cnt = mValue.size();
		//	if (!(mValue.isArray() && cnt > 0 && mValue[0].isNumeric()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new float[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mValue[i].asFloat();
		//	}
		//	uSize = cnt;
		//}

		//void JsonCpp::Node::arrayData(word* &pData, uint &uSize) const
		//{
		//	const uint cnt = mValue.size();
		//	if (!(mValue.isArray() && cnt > 0 && mValue[0].isNumeric()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new word[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mValue[i].asUInt();
		//	}
		//	uSize = cnt;
		//}

		//bool JsonCpp::Node::find(const String& strKey, IDBNode* node /* = nullptr */) const
		//{
		//	return false;
		//	//mValue.find()
		//}

		//void JsonCpp::Node::addChild(const String& strKey, IDBNode* node)
		//{
		//	if (nullptr == node)
		//		return;
		//	mValue[strKey.getString()] = ((JsonCpp::Node*)node)->mValue;
		//}

		///*-----------------------------------------------------------
		//class JsonCpp
		//------------------------------------------------------------*/
		//JsonCpp::JsonCpp()
		//	: mpRoot(nullptr)
		//{
		//	mpRoot = JsonCpp::Node::createMem<JsonCpp::Node>();
		//}

		//JsonCpp::~JsonCpp()
		//{
		//	JsonCpp::Node::destroyMem<JsonCpp::Node>(mpRoot);
		//}

		//bool JsonCpp::open(const String& strOpen)
		//{
		//	Json::Reader reader;
		//	std::ifstream is;
		//	is.open(strOpen.getString());
		//	reader.parse(is, mpRoot->mValue);
		//	//is.close();
		//	return true;
		//}

		//void JsonCpp::close()
		//{

		//}

		//void JsonCpp::save()
		//{
		//	write(mstrPathFile);
		//}

		//bool JsonCpp::write(const String& strWrite)
		//{
		//	Json::FastWriter writer;
		//	const String strContent = writer.write(mpRoot->mValue);
		//	std::ofstream os;
		//	os.open(strWrite.getString());
		//	os.write(strContent.getChar(), strContent.getSize());
		//	os.flush();
		//	os.close();
		//	return true;
		//}

		//IDBNode* JsonCpp::root()
		//{
		//	return mpRoot;
		//}

		//const IDBNode* JsonCpp::root() const
		//{
		//	return mpRoot;
		//}

		///*-----------------------------------------------------------
		//class JsonRap::Node
		//------------------------------------------------------------*/
		//JsonRap::Node::Node()
		//{

		//}

		//JsonRap::Node::~Node()
		//{
		//	mValue.Clear();
		//}

		//bool JsonRap::Node::isEmpty() const
		//{
		//	return mValue.Empty();
		//}

		//uint JsonRap::Node::size() const
		//{
		//	return mValue.Size();
		//}

		////virtual IDBNode* child(const String& strChild) const = 0;

		//void JsonRap::Node::putString(const String& strKey, const String& strVal)
		//{
		//	rapidjson::Value val;// = strVal.getChar();
		//	//val.SetString(strVal.getString(), strVal.getSize(), );
		//	//mValue.AddMember(strKey.getChar(), val);
		//}

		//String JsonRap::Node::getString(const String& strKey) const
		//{
		//	String val = mValue[strKey.getChar()].GetString();
		//	return val;
		//}

		//void JsonRap::Node::putInt(const String& strKey, int val)
		//{
		//	mValue[strKey.getChar()] = val;
		//}

		//int JsonRap::Node::getInt(const String& strKey) const
		//{
		//	int val = mValue[strKey.getChar()].GetInt();
		//	return val;
		//}

		////void putFloat(const String& strKey, float val);

		//float JsonRap::Node::getFloat(const String& strKey) const
		//{
		//	float val = mValue[strKey.getChar()].GetFloat();
		//	return val;
		//}

		////void putBool(const String& strKey, bool val);

		//bool JsonRap::Node::getBool(const String& strKey) const
		//{
		//	bool val = mValue[strKey.getChar()].GetBool();
		//	return val;
		//}

		//bool JsonRap::Node::getChild(IDBNode* node, const String& strChild) const
		//{
		//	bool bOk = false;
		//	if (nullptr != node && mValue.HasMember(strChild.getChar()))
		//	{
		//		//((JsonRap::Node*)node)->mValue = mValue[strChild.getChar()];
		//		bOk = true;
		//	}
		//	return bOk;
		//}

		//bool JsonRap::Node::arrayEle(IDBNode* node, uint idx, uint* uSubCnt /* = nullptr */) const
		//{
		//	const uint cnt = mValue.Size();
		//	if (nullptr == node || idx >= cnt)
		//		return false;
		//	//((JsonRap::Node*)node)->mValue = mValue[idx];
		//	if (nullptr != uSubCnt)
		//		*uSubCnt = cnt;
		//	return true;// val.IsNull();
		//}

		//void JsonRap::Node::arrayData(float* &pData, uint &uSize) const
		//{
		//	const uint cnt = mValue.Size();
		//	if (!(mValue.IsArray() && cnt > 0 && mValue[0].IsNumber()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new float[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mValue[i].GetFloat();
		//	}
		//	uSize = cnt;
		//}

		//void JsonRap::Node::arrayData(word* &pData, uint &uSize) const
		//{
		//	const uint cnt = mValue.Size();
		//	if (!(mValue.IsArray() && cnt > 0 && mValue[0].IsNumber()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new word[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mValue[i].GetUint();
		//	}
		//	uSize = cnt;
		//}

		//bool JsonRap::Node::find(const String& strKey, IDBNode* node /* = nullptr */) const
		//{
		//	bool bHas = mValue.HasMember(strKey.getChar());
		//	if (bHas && nullptr != node)
		//	{
		//		//((JsonRap::Node*)node)->mValue = mValue[strKey.getChar()];
		//	}
		//	return bHas;
		//}

		//void JsonRap::Node::addChild(const String& strKey, IDBNode* node)
		//{
		//	if (nullptr == node)
		//		return;
		//	mValue[strKey.getChar()] = ((JsonRap::Node*)node)->mValue;
		//}

		///*-----------------------------------------------------------
		//class JsonRap::Root
		//------------------------------------------------------------*/
		//JsonRap::Root::Root()
		//{

		//}

		//JsonRap::Root::~Root()
		//{
		//	mRoot.Clear();
		//}

		//bool JsonRap::Root::isEmpty() const
		//{
		//	return mRoot.Empty();
		//}

		//uint JsonRap::Root::size() const
		//{
		//	return mRoot.Size();
		//}

		////virtual IDBNode* child(const String& strChild) const = 0;

		//void JsonRap::Root::putString(const String& strKey, const String& strVal)
		//{
		//	//mRoot[strKey.getChar()] = strVal.getString();
		//}

		//String JsonRap::Root::getString(const String& strKey) const
		//{
		//	String val = mRoot[strKey.getChar()].GetString();
		//	return val;
		//}

		//void JsonRap::Root::putInt(const String& strKey, int val)
		//{
		//	//mRoot[strKey.getString()] = val;
		//}

		//int JsonRap::Root::getInt(const String& strKey) const
		//{
		//	int val = mRoot[strKey.getChar()].GetInt();
		//	return val;
		//}

		////void putFloat(const String& strKey, float val);

		//float JsonRap::Root::getFloat(const String& strKey) const
		//{
		//	float val = mRoot[strKey.getChar()].GetFloat();
		//	return val;
		//}

		////void putBool(const String& strKey, bool val);

		//bool JsonRap::Root::getBool(const String& strKey) const
		//{
		//	bool val = mRoot[strKey.getChar()].GetBool();
		//	return val;
		//}

		//bool JsonRap::Root::getChild(IDBNode* node, const String& strChild) const
		//{
		//	return false;
		//	//Json::Value val = mValue[strChild.getChar()];
		//	//((JsonRap::Node*)node)->mValue = val;
		//	//return val.isNull();
		//}

		//bool JsonRap::Root::arrayEle(IDBNode* node, uint idx, uint* uSubCnt /* = nullptr */) const
		//{
		//	return false;
		//	//const uint cnt = mValue.size();
		//	//if (nullptr == node || idx >= cnt)
		//	//	return false;
		//	//Json::Value val = mValue[idx];
		//	//((JsonRap::Node*)node)->mValue = val;
		//	//if (nullptr != uSubCnt)
		//	//	*uSubCnt = cnt;
		//	//return val.isNull();
		//}

		//void JsonRap::Root::arrayData(float* &pData, uint &uSize) const
		//{
		//	const uint cnt = mRoot.Size();
		//	if (!(mRoot.IsArray() && cnt > 0 && mRoot[0].IsNumber()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new float[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mRoot[i].GetFloat();
		//	}
		//	uSize = cnt;
		//}

		//void JsonRap::Root::arrayData(word* &pData, uint &uSize) const
		//{
		//	const uint cnt = mRoot.Size();
		//	if (!(mRoot.IsArray() && cnt > 0 && mRoot[0].IsNumber()))
		//	{
		//		pData = nullptr;
		//		uSize = 0;
		//		return;
		//	}
		//	pData = new word[cnt];
		//	for (uint i = 0; i < cnt; i++)
		//	{
		//		pData[i] = mRoot[i].GetUint();
		//	}
		//	uSize = cnt;
		//}

		//bool JsonRap::Root::find(const String& strKey, IDBNode* node /* = nullptr */) const
		//{
		//	bool bOk = false;
		//	rapidjson::Value::ConstMemberIterator itr = mRoot.FindMember(strKey.getChar());
		//	if (itr != mRoot.MemberEnd())
		//	{
		//		//((JsonRap::Node*)node)->mValue = mRoot[strKey.getChar()];
		//		bOk = true;
		//	}
		//	return bOk;
		//}

		//void JsonRap::Root::addChild(const String& strKey, IDBNode* node)
		//{
		//	if (nullptr == node)
		//		return;
		//	mRoot[strKey.getChar()] = ((JsonRap::Node*)node)->mValue;
		//}

		///*-----------------------------------------------------------
		//class JsonRap
		//------------------------------------------------------------*/
		//JsonRap::JsonRap()
		//	: mpRoot(nullptr)
		//{
		//	mpRoot = JsonRap::Root::createMem<JsonRap::Root>();
		//}

		//JsonRap::~JsonRap()
		//{
		//	JsonRap::Root::destroyMem<JsonRap::Root>(mpRoot);
		//}

		//bool JsonRap::open(const String& strOpen)
		//{
		//	ifstream ifs(strOpen.getString());
		//	if (ifs.bad())//.good();
		//		return false;
		//	rapidjson::IStreamWrapper isw(ifs);
		//	mpRoot->mRoot.ParseStream(isw);
		//	ifs.close();
		//	const bool bOk = mpRoot->mRoot.IsObject();
		//	return bOk;
		//}

		//void JsonRap::close()
		//{

		//}

		//void JsonRap::save()
		//{
		//	write(mstrPathFile);
		//}

		//bool JsonRap::write(const String& strWrite)
		//{
		//	std::ofstream ofs(strWrite.getString());
		//	rapidjson::OStreamWrapper osw(ofs);
		//	rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		//	mpRoot->mRoot.Accept(writer);
		//	ofs.flush();
		//	ofs.close();
		//	return true;
		//}

		//IDBNode* JsonRap::root()
		//{
		//	return mpRoot;
		//}

		//const IDBNode* JsonRap::root() const
		//{
		//	return mpRoot;
		//}


		/*-----------------------------------------------------------
		class JSRap
		------------------------------------------------------------*/
		bool JSRap::open(const String& strOpen)
		{
			ifstream ifs(strOpen.getChar());
			rapidjson::IStreamWrapper isw(ifs);
			mRoot.ParseStream(isw);
			const bool bOk = mRoot.IsObject();
			if (bOk)
			{
				mstrPathFile = strOpen;
			}
			return bOk;
		}

		void JSRap::close()
		{

		}

		void JSRap::save()
		{
			write(mstrPathFile);
		}

		void JSRap::write(const String& strWrite)
		{
			ofstream ofs(strWrite.getChar());
			rapidjson::OStreamWrapper osw(ofs);
			rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
			mRoot.Accept(writer);
		}

		//String JSRap::getString(const String& strKey) const
		//{
		//	if (!mRoot.HasMember(strKey.getChar()))
		//		return "";
		//	const rapidjson::Value& node = mRoot[strKey.getChar()];
		//	String val(node.GetString());
		//	return val;
		//}

		//void JSRap::setString(const String& strKey, const String& strVal)
		//{
		//	rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
		//	rapidjson::Value val(strVal.getChar(), strVal.getSize(), mRoot.GetAllocator());
		//	mRoot.AddMember(key, val, mRoot.GetAllocator());
		//}

		//bool JSRap::getStringArray(const String& strKey, TArray<String>& vData) const
		//{
		//	vData.clear();
		//	if (!mRoot.HasMember(strKey.getChar()))
		//		return false;

		//	const rapidjson::Value& node = mRoot[strKey.getChar()];
		//	if (!(node.IsArray() && node.Size() > 0))
		//	{
		//		return false;
		//	}
		//	uint size = node.Size();
		//	vData.resize(size);
		//	for (unsigned int i = 0; i < size; i++)
		//		vData[i] = node[i].GetString();
		//	return true;
		//}

		//bool JSRap::setStringArray(const String& strKey, const TArray<String>& vData)
		//{
		//	if (vData.size() <= 0)
		//		return false;

		//	rapidjson::Value node(rapidjson::kArrayType);
		//	for (int i = 0; i < vData.size(); i++)
		//	{
		//		rapidjson::Value val(vData[i].getChar(), vData[i].getSize(), mRoot.GetAllocator());
		//		node.PushBack(val, mRoot.GetAllocator());
		//	}
		//	rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
		//	mRoot.AddMember(key, node, mRoot.GetAllocator());
		//}

		bool JSRap::find(const String& strKey) const
		{
			return mRoot.HasMember(strKey.getChar());
		}

		uint JSRap::size() const
		{
			uint uSize = mRoot.MemberCount();
			return uSize;
		}

		uint JSRap::size(const String& strRoute) const
		{
			rapidjson::Value* node = (rapidjson::Value*)has(strRoute);
			uint uSize = (nullptr != node) ? ((node->IsArray())? node->Size() : node->MemberCount()) : 0;
			return uSize;
		}

		const void* JSRap::has(const String& strRoute) const
		{
			if (strRoute.isEmpty())
				return nullptr;
			TArray<String> vKey = strRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return nullptr;
			const rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
					return nullptr;
				node = &(*node)[vKey[i].getChar()];
			}
			return node;
		}

		void* JSRap::has(const String& strRoute)
		{
			if (strRoute.isEmpty())
				return nullptr;
			TArray<String> vKey = strRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return nullptr;
			rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
					return nullptr;
				node = &(*node)[vKey[i].getChar()];
			}
			return node;
		}

		void* JSRap::put(const String& strRoute, bool bObject /* = false */)
		{
			rapidjson::Value* node = (rapidjson::Value*)has(strRoute);
			if (nullptr != node)
			{
				return node;
			}
			//
			TArray<String> vKey = strRoute.split(".");
			const uint uSize = vKey.size();
			if (uSize <= 0)
				return nullptr;
			if (!mRoot.HasMember(vKey[0].getChar()))
			{
				rapidjson::Value key(vKey[0].getChar(), vKey[0].getSize(), mRoot.GetAllocator());
				rapidjson::Value val;
				if (uSize > 1)
					val.SetObject();
				mRoot.AddMember(key, val, mRoot.GetAllocator());
			}
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < uSize; i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
				{
					node->SetObject();
					rapidjson::Value key(vKey[i].getChar(), vKey[i].getSize(), mRoot.GetAllocator());
					rapidjson::Value val;
					node->AddMember(key, val, mRoot.GetAllocator());
				}
				node = &(*node)[vKey[i].getChar()];
			}
			if (bObject)
				node->SetObject();
			return node;
		}

		bool JSRap::hasString(const String& strRoute, String* strVal /* = nullptr */, const String& strNotFound /* = "" */) const
		{
			if(nullptr != strVal)
				*strVal = strNotFound;
			const rapidjson::Value* node = (rapidjson::Value*)has(strRoute);
			if (nullptr == node || !node->IsString())
				return false;
			if (nullptr != strVal)
				*strVal = node->GetString();
			return true;
		}

		String JSRap::findString(const String& strRoute, const String& strNotFound /* = "" */) const
		{
			String strVal;
			bool bOk = hasString(strRoute, &strVal, strNotFound);
			return strVal;
		}

		bool JSRap::putString(const String& strRoute, const String& strVal)
		{
			String objRoute, strKey;
			ulong uIdx = 0;
			bool bOk = false;
			bOk = strRoute.find(".", uIdx, 0, true);
			bOk = strRoute.split(uIdx, objRoute, strKey, true);
			//
			TArray<String> vKey = objRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return false;
			rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			if (!node->IsObject())
				return false;
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			rapidjson::Value val(strVal.getChar(), strVal.getSize(), mRoot.GetAllocator());
			node->AddMember(key, val, mRoot.GetAllocator());
			return true;
		}

		bool JSRap::hasStringArray(const String& strRoute, TArray<String>* vData /* = nullptr */)
		{
			if (nullptr != vData)
				vData->clear();
			TArray<String> vKey = strRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return false;
			const rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			//
			if (!(node->IsArray() && node->Size() > 0))
			{
				return false;
			}
			uint size = node->Size();
			vData->resize(size);
			for (unsigned int i = 0; i < size; i++)
				(*vData)[i] = node[i].GetString();
			return true;
		}

		TArray<String> JSRap::findStringArray(const String& strRoute)
		{
			TArray<String> vStr;
			bool bOk = hasStringArray(strRoute, &vStr);
			return vStr;
		}

		bool JSRap::putStringArray(const String& strRoute, const TArray<String>& vVal)
		{
			const uint uSize = vVal.size();
			if (uSize <= 0)
				return false;
			String objRoute, strKey;
			ulong uIdx = 0;
			bool bOk = false;
			bOk = strRoute.find(".", uIdx, 0, true);
			bOk = strRoute.split(uIdx, objRoute, strKey, true);
			//
			TArray<String> vKey = objRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return false;
			rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			if (!node->IsObject())
				return false;
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			rapidjson::Value val(rapidjson::kArrayType);
			for (uint i = 0; i < uSize; i++)
			{
				rapidjson::Value ele(vVal[i].getChar(), vVal[i].getSize(), mRoot.GetAllocator());
				val.PushBack(ele, mRoot.GetAllocator());
			}
			node->AddMember(key, val, mRoot.GetAllocator());
			return true;
		}

		/*-----------------------------------------------------------
		class FileSys
		------------------------------------------------------------*/
		void FileSys::createDir(const String& strPath)
		{
			String strTemp("");
			const TArray<String> vStr = strPath.split("\\");
			for (uint i = 0; i < vStr.size(); i++)
			{
				strTemp += vStr[i];
				if (_access(vStr[i].getChar(), 0) != 0)
				{
					_tmkdir(strTemp.toWString().c_str());
				}
				strTemp += "\\";
			}
		}

		void FileSys::deleteDir(const String& strPath)
		{
			if (!strPath.isEmpty())// && _access(strPath.getChar(), 0) == 0)
			{
				String strTemp(strPath);
				_trmdir(strTemp.toWString().c_str());
			}
		}

		bool FileSys::findDir(const String& strPath)
		{
			return (_access(strPath.getChar(), 0) == 0);
		}

		String FileSys::fileList(const String& strPath, const String& strFileExtend, uint* uCnt /* = nullptr */, bool bRemoveExt /* = false */, TArray<String>* vFiles /* = nullptr */)
		{
			String strFiles(""), strTemp;
			if (nullptr != vFiles)
				vFiles->clear();
			if (nullptr != uCnt)
				*uCnt = 0;
			//
			long   hFile = 0;
			struct _finddata_t fileinfo;
			string p;
			if ((hFile = _findfirst(p.assign(strPath.getString()).append("\\*").c_str(), &fileinfo)) != -1)
			{
				do
				{
					// if sub-dir  
					if ((fileinfo.attrib & _A_SUBDIR))
					{
						if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
							strFiles += fileList(p.assign(strPath.getString()).append("\\").append(fileinfo.name), strFileExtend, uCnt, bRemoveExt, vFiles);
					}
					else
					{
						strTemp = p.assign(strPath.getString()).append("\\").append(fileinfo.name);
						strFiles += strTemp;
						strFiles += ",";
						if (nullptr != vFiles)
							vFiles->add(strTemp);
						if (nullptr != uCnt)
							*uCnt++;
					}
				} while (_findnext(hFile, &fileinfo) == 0);
				_findclose(hFile);
			}
			return strFiles;
		}

		bool FileSys::findFile(const String& strPathFile)
		{
			return (_access(strPathFile.getChar(), 0) == 0);
		}

		void FileSys::deleteFile(const String& strPathFile)
		{
			
		}




	}
}