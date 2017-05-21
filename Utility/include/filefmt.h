/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "base.h"
#include "rapidjson\document.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class IDBNode
		------------------------------------------------------------*/
		class IDBNode : public IRoot
		{
		public:
			virtual bool isEmpty() const = 0;
			virtual uint size() const = 0;
			//virtual IDBNode* child(const String& strChild) const = 0;
			virtual void putString(const String& strKey, const String& strVal) = 0;
			virtual String getString(const String& strKey) const = 0;
			virtual void putInt(const String& strKey, int val) = 0;
			virtual int getInt(const String& strKey) const = 0;
			//void putFloat(const String& strKey, float val);
			virtual float getFloat(const String& strKey) const = 0;
			//void putBool(const String& strKey, bool val);
			virtual bool getBool(const String& strKey) const = 0;

			virtual bool getChild(IDBNode* node, const String& strChild) const = 0;
			virtual bool arrayEle(IDBNode* node, uint idx, uint* uSubCnt = nullptr) const = 0;
			virtual void arrayData(float* &pData, uint &uSize) const = 0;
			virtual void arrayData(word* &pData, uint &uSize) const = 0;

			virtual bool find(const String& strKey, IDBNode* node = nullptr) const = 0;
			virtual void addChild(const String& strKey, IDBNode* node) = 0;

		};

		class IDBGroup : public IRoot
		{
		public:
			// @strOpen: path file string or sql string
			virtual bool open(const String& strOpen) = 0;
			virtual void close() = 0;
			virtual void save() = 0;
			// @strOpen: path file string or sql string
			virtual bool write(const String& strWrite) = 0;
			virtual IDBNode* root() = 0;
			virtual const IDBNode* root() const = 0;
		};

		///*-----------------------------------------------------------
		//class JsonCpp
		//------------------------------------------------------------*/
		//class JsonCpp : public IDBGroup
		//{
		//public:
		//	class Node : public IDBNode
		//	{
		//		friend JsonCpp;
		//	public:
		//		Node();
		//		~Node();

		//		bool isEmpty() const override;
		//		uint size() const override;
		//		//virtual IDBNode* child(const String& strChild) const = 0;
		//		void putString(const String& strKey, const String& strVal) override;
		//		String getString(const String& strKey) const override;
		//		void putInt(const String& strKey, int val) override;
		//		int getInt(const String& strKey) const override;
		//		//void putFloat(const String& strKey, float val);
		//		float getFloat(const String& strKey) const override;
		//		//void putBool(const String& strKey, bool val);
		//		bool getBool(const String& strKey) const override;

		//		bool getChild(IDBNode* node, const String& strChild) const override;
		//		bool arrayEle(IDBNode* node, uint idx, uint* uSubCnt = nullptr) const override;
		//		void arrayData(float* &pData, uint &uSize) const override;
		//		void arrayData(word* &pData, uint &uSize) const override;

		//		bool find(const String& strKey, IDBNode* node = nullptr) const override;
		//		void addChild(const String& strKey, IDBNode* node) override;

		//	private:
		//		Json::Value	mValue;
		//	};

		//public:
		//	JsonCpp();
		//	virtual ~JsonCpp();

		//	bool open(const String& strOpen) override;
		//	void close() override;
		//	void save() override;
		//	bool write(const String& strWrite) override;
		//	IDBNode* root() override;
		//	const IDBNode* root() const override;

		//private:
		//	JsonCpp::Node*	mpRoot;
		//	String			mstrPathFile;
		//};

		///*-----------------------------------------------------------
		//class JsonRap
		//------------------------------------------------------------*/
		//class JsonRap : public IDBGroup
		//{
		//public:
		//	class Node : public IDBNode
		//	{
		//		friend JsonRap;
		//	public:
		//		Node();
		//		~Node();

		//		bool isEmpty() const override;
		//		uint size() const override;
		//		//virtual IDBNode* child(const String& strChild) const = 0;
		//		void putString(const String& strKey, const String& strVal) override;
		//		String getString(const String& strKey) const override;
		//		void putInt(const String& strKey, int val) override;
		//		int getInt(const String& strKey) const override;
		//		//void putFloat(const String& strKey, float val);
		//		float getFloat(const String& strKey) const override;
		//		//void putBool(const String& strKey, bool val);
		//		bool getBool(const String& strKey) const override;

		//		bool getChild(IDBNode* node, const String& strChild) const override;
		//		bool arrayEle(IDBNode* node, uint idx, uint* uSubCnt = nullptr) const override;
		//		void arrayData(float* &pData, uint &uSize) const override;
		//		void arrayData(word* &pData, uint &uSize) const override;

		//		bool find(const String& strKey, IDBNode* node = nullptr) const override;
		//		void addChild(const String& strKey, IDBNode* node) override;

		//	private:
		//		rapidjson::Value mValue;
		//		IDBNode*			mpRootRef;
		//	};

		//	class Root : public IDBNode
		//	{
		//		friend JsonRap;
		//	public:
		//		Root();
		//		~Root();

		//		bool isEmpty() const override;
		//		uint size() const override;
		//		//virtual IDBNode* child(const String& strChild) const = 0;
		//		void putString(const String& strKey, const String& strVal) override;
		//		String getString(const String& strKey) const override;
		//		void putInt(const String& strKey, int val) override;
		//		int getInt(const String& strKey) const override;
		//		//void putFloat(const String& strKey, float val);
		//		float getFloat(const String& strKey) const override;
		//		//void putBool(const String& strKey, bool val);
		//		bool getBool(const String& strKey) const override;

		//		bool getChild(IDBNode* node, const String& strChild) const override;
		//		bool arrayEle(IDBNode* node, uint idx, uint* uSubCnt = nullptr) const override;
		//		void arrayData(float* &pData, uint &uSize) const override;
		//		void arrayData(word* &pData, uint &uSize) const override;

		//		bool find(const String& strKey, IDBNode* node = nullptr) const override;
		//		void addChild(const String& strKey, IDBNode* node) override;

		//	private:
		//		rapidjson::Document	mRoot;
		//	};

		//public:
		//	JsonRap();
		//	virtual ~JsonRap();

		//	bool open(const String& strOpen) override;
		//	void close() override;
		//	void save() override;
		//	bool write(const String& strWrite) override;
		//	IDBNode* root() override;
		//	const IDBNode* root() const override;

		//private:
		//	JsonRap::Root*	mpRoot;
		//	String			mstrPathFile;
		//};

		/*-----------------------------------------------------------
		class JSRap
		------------------------------------------------------------*/
		class JSRap : public IRoot
		{
		public:
			bool open(const String& strOpen);
			void close();
			void save();
			void write(const String& strWrite);

		public:
			bool find(const String& strKey) const;

			template<class T>
			T getVal(const String& strKey) const;
			template<class T>
			void setVal(const String& strKey, T tVal);

			template<class T>
			bool getArray(const String& strKey, TArray<T>& vData) const;
			template<class T>
			void setArray(const String& strKey, const TArray<T>& vData);

		public:
			uint size() const;
			uint size(const String& strRoute) const;
			const void* has(const String& strRoute) const;
			void* has(const String& strRoute);
			void* put(const String& strRoute, bool bObject = false);
			template<class T>
			void put(const String& strRoute, T tVal);
			template<class T>
			void put(const String& strRoute, const String& strKey, T tVal);

			bool hasString(const String& strRoute, String* strVal = nullptr, const String& strNotFound = "") const;
			String findString(const String& strRoute, const String& strNotFound = "") const;
			bool putString(const String& strRoute, const String& strVal);

			// Must set tNotFound if T is string , e.g. const char*
			template<class T>
			bool hasVal(const String& strRoute, T* tVal = nullptr, const T& tNotFound = T()) const;
			template<class T>
			T findVal(const String& strRoute, const T& tNotFound) const;
			template<class T>
			bool putVal(const String& strRoute, const T& tVal);

			bool hasStringArray(const String& strRoute, TArray<String>* vData = nullptr);
			TArray<String> findStringArray(const String& strRoute);
			bool putStringArray(const String& strRoute, const TArray<String>& vVal);

			template<class T>
			bool hasValArray(const String& strRoute, TArray<T>* vData = nullptr);
			template<class T>
			TArray<T> findValArray(const String& strRoute);
			template<class T>
			bool putValArray(const String& strRoute, const TArray<T>& vVal);

		protected:

		private:
			rapidjson::Document	mRoot;
			String				mstrPathFile;
		};

		/*-----------------------------------------------------------
		class JSRap
		------------------------------------------------------------*/
		template<class T>
		void JSRap::put(const String& strRoute, T tVal)
		{
			if (strRoute.isEmpty())
				return;
			rapidjson::Value* node = (rapidjson::Value*)put(strRoute, false);
			node->Set<T>(tVal, mRoot.GetAllocator());
		}

		template<class T>
		void JSRap::put(const String& strRoute, const String& strKey, T tVal)
		{
			if (strRoute.isEmpty() || strKey.isEmpty())
				return;
			rapidjson::Value* node = (rapidjson::Value*)put(strRoute, true);
			rapidjson::Value key, val;
			key.Set<const char*>(strKey.getChar(), mRoot.GetAllocator());
			val.Set<T>(tVal, mRoot.GetAllocator());
			if (node->HasMember(strKey.getChar()))
				(*node)[strKey.getChar()] = val;
			else
				node->AddMember(key, val, mRoot.GetAllocator());
		}

		template<class T>
		T JSRap::getVal(const String& strKey) const
		{
			if (!mRoot.HasMember(strKey.getChar()))
				return T();
			const rapidjson::Value& node = mRoot[strKey.getChar()];
			T val = node.Get<T>();
			return val;
		}

		template<class T>
		void JSRap::setVal(const String& strKey, T tVal)
		{
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			rapidjson::Value val;
			val.Set<T>(tVal, mRoot.GetAllocator());
			mRoot.AddMember(key, val, mRoot.GetAllocator());
		}

		template<class T>
		bool JSRap::getArray(const String& strKey, TArray<T>& vData) const
		{
			vData.clear();
			if (!mRoot.HasMember(strKey.getChar()))
				return false;

			const rapidjson::Value& node = mRoot[strKey.getChar()];
			if (!(node.IsArray() && node.Size() > 0))
			{
				return false;
			}
			uint size = node.Size();
			vData.resize(size);
			for (unsigned int i = 0; i < size; i++)
				vData[i] = node[i].Get<T>();
			return true;
		}

		template<class T>
		void JSRap::setArray(const String& strKey, const TArray<T>& vData)
		{
			if (vData.size() <= 0)
				return;
			rapidjson::Value node(rapidjson::kArrayType);
			for (int i = 0; i < vData.size(); i++)
			{
				rapidjson::Value val;
				val.Set<T>(vData[i], mRoot.GetAllocator());
				node.PushBack(val, mRoot.GetAllocator());
			}
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			mRoot.AddMember(key, node, mRoot.GetAllocator());
		}

		template<class T>
		bool JSRap::hasVal(const String& strRoute, T* tVal /* = nullptr */, const T& tNotFound /* = T() */) const
		{
			if (nullptr != tVal)
				*tVal = tNotFound;
			TArray<String> vKey = strRoute.split(".");
			if (vKey.isEmpty() || !mRoot.HasMember(vKey[0].getChar()))
				return false;
			const rapidjson::Value* node = nullptr;
			node = &mRoot[vKey[0].getChar()];
			for (int i = 1; i < vKey.size(); i++)
			{
				if (!node->IsObject() || !node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			if (!node->Is<T>())
				return false;
			if (nullptr != tVal)
				*tVal = node->Get<T>();
			return true;
		}

		template<class T>
		T JSRap::findVal(const String& strRoute, const T& tNotFound) const
		{
			T tVal;
			bool bOk = hasVal<T>(strRoute, &tVal, tNotFound);
			return tVal;
		}

		template<class T>
		bool JSRap::putVal(const String& strRoute, const T& tVal)
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
				if (!node->IsObject() || !node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			if (!node->IsObject())
				return false;
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			rapidjson::Value val(strVal.getChar(), strVal.getSize(), mRoot.GetAllocator());
			node->AddMember<T>(key, val, mRoot.GetAllocator());
			return true;
		}

		template<class T>
		bool JSRap::hasValArray(const String& strRoute, TArray<T>* vData /* = nullptr */)
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
				if (!node->IsObject() || !node->HasMember(vKey[i].getChar()))
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
				(*vData)[i] = node[i].Get<T>();
			return true;
		}

		template<class T>
		TArray<T> JSRap::findValArray(const String& strRoute)
		{
			TArray<T> vVal;
			bool bOk = hasValArray<T>(strRoute, &vVal);
			return vVal;
		}

		template<class T>
		bool JSRap::putValArray(const String& strRoute, const TArray<T>& vVal)
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
				if (!node->IsObject() || !node->HasMember(vKey[i].getChar()))
					return false;
				node = &(*node)[vKey[i].getChar()];
			}
			if (!node->IsObject())
				return false;
			rapidjson::Value key(strKey.getChar(), strKey.getSize(), mRoot.GetAllocator());
			rapidjson::Value val(rapidjson::kArrayType);
			for (uint i = 0; i < uSize; i++)
			{
				val.PushBack<T>(vVal[i], mRoot.GetAllocator());
			}
			node->AddMember(key, val, mRoot.GetAllocator());
			return true;
		}

		/*-----------------------------------------------------------
		class FileSys
		------------------------------------------------------------*/
		class FileSys : public IRoot
		{
		public:
			static void createDir(const String& strPath);
			static void deleteDir(const String& strPath);
			static bool findDir(const String& strPath);
			static String fileList(const String& strPath, const String& strFileExtend, uint* uCnt = nullptr, bool bRemoveExt = false, TArray<String>* vFiles = nullptr);
			static bool findFile(const String& strPathFile);
			static void deleteFile(const String& strPathFile);
		};



	}
}
