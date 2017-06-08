/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "inUtility.h"
#include "array.h"
#include "map.h"
#include "buffer.h"
#include <thread>

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class EState
		------------------------------------------------------------*/
		enum EState
		{
			State_MAKE,
			State_FREE,
			State_MAX
		};

		/*-----------------------------------------------------------
		class EMemory
		------------------------------------------------------------*/
		enum EMemory
		{
			Memory_Create,
			Memory_Refrence,
			Memory_Max
		};

		class String;
		class Tag;
		/*-----------------------------------------------------------
		class IRoot
		------------------------------------------------------------*/
		class IRoot : public IBase
		{
		public:
			struct InitParam
			{
			};

		public:
			IRoot();
			virtual ~IRoot();
			IRoot(const IRoot& other);
			IRoot& operator = (const IRoot& other);
			bool operator < (const IRoot& other) const;
			bool operator == (const IRoot& other) const;

			bool create(void* pData = nullptr);
			void destroy();

			// memory state.
			void memoryState(const EMemory& eState);
			const EMemory& memoryState() const;
			bool isMemoryCreate() const;
			bool isMemoryReference() const;
			// state
			void state(const EState& eState);
			const EState& state() const;
			// enable
			void enable(bool bEnable);
			bool enable() const;
			// if is already created.
			bool isMake() const;
			// if is already released.
			bool isFree() const;
			// tag
			void tag(const Tag& tag);
			Tag* tag();
			const Tag* tag() const;
			const Tag& getTag() const;
			bool isUnknowTag() const;
			void isUnknowTagThenSet(const Tag& flag);

		protected:
			void copyOther(const IRoot& other);
			virtual bool doCreate(void* pData = nullptr);
			virtual void doDestroy();

		public:
			template<class T>
			static T* createMem(void* pInitParam = nullptr);

			template<class T>
			static void destroyMem(T* &pt);

			template<class T>
			static void deepCopy(T* &pDes, const T* pSrc);

			template<class T>
			static void reference(T* &pDes, T* pSrc);

			template<class T>
			static bool isEquate(const T* ptA, const T* ptB);

		private:
			static const	uint BinMax = 512;
			static const	uint ClassMax = 256;
			static void*	gpBin[ClassMax][BinMax];	// Garbage collector.
			static uint		guSize[ClassMax][2];		// [][0]: can reused element size of bin. [][1]: size of new
			static std::map<String, word>	gmapClassID;
			static std::mutex				mMutex;
			//static TMap<String, IRoot*>		gmapRes;

			EState		meState;
			EMemory		meMemoryState;
			Tag*		mpTag;
			bool		mbEnable;
			
		};

		/*-----------------------------------------------------------
		class IRoot
		------------------------------------------------------------*/
		template<class T>
		T* IRoot::createMem(void* pInitParam /* = nullptr */)
		{
			T* pt = nullptr;
			pt = new T;
			if(nullptr != pInitParam)
				pt->create(pInitParam);
			return pt;
		}

		template<class T>
		void IRoot::destroyMem(T* &pt)
		{
			if (nullptr != pt)
			{
				pt->destroy();
				if (pt->isMemoryCreate())
					delete pt;
				pt = nullptr;
			}
		}

		template<class T>
		void IRoot::deepCopy(T* &pDes, const T* pSrc)
		{
			pDes = createMem<T>();
			*pDes = *pSrc;
		}

		template<class T>
		void IRoot::reference(T* &pDes, T* pSrc)
		{
			//destroyMem<T>(pDes);
			pDes = pSrc;
			pDes->memoryState(EMemory::Memory_Refrence);
		}

		template<class T>
		bool IRoot::isEquate(const T* ptA, const T* ptB)
		{
			return (ptA == ptB);
		}

		/*-----------------------------------------------------------
		class String
		------------------------------------------------------------*/
		class String : public IRoot
		{
		public:
			//enum EnumCodePage
			//{
			//	CodePage_ACP = CP_ACP,
			//	CodePage_UTF8 = CP_UTF8
			//};

		public:
			String();
			String(const byte* bt);
			String(const char* s);
			String(const wchar* s);
			String(const std::string& str);
			String(const std::wstring& wstr);
			String(char ch);
			String(bool b);
			String(int index);
			String(uint uStr);
			String(long uStr);
			String(ulong uStr);
			String(float fStr);
			//String(fdword dwStr);
			//String(char* szStr);
			//String(char* szMsg, ...);
			String(const String& s);
			//String(const std::string& s);
			virtual ~String();

			//virtual FRD create();
			//virtual FRD release();

			String& operator = (const String& s);
			bool operator == (const String& s) const;
			bool operator != (const String& s) const;
			bool operator > (const String& s) const;
			bool operator < (const String& s) const;
			String operator + (const String& s) const;
			String& operator += (const String& s);

			void setString(const char* s);
			void setString(const String& s);
			void append(const char* s);
			void append(const String& s);
			bool insert(ulong index, const String& s, ulong count = 1);
			bool insert(ulong uIndex, char ch);
			bool setAt(ulong uIndex, char ch);
			char getAt(ulong uIndex) const;
			void encryption();
			void decryption();
			bool isEncryption() const;
			// replace [index,index + count] with strReplace.
			void replace(ulong index, ulong count, const char* strReplace);
			// replace string: strOld with string: strNew.
			// @uIndex: index of search begin position.
			// @bAll: true for replace all, false for replace once only.
			void replace(const String& strOld, const String& strNew, ulong uFrom = 0, ulong uCount = 0, bool bAll = true);
			// @bIgnoreDelimit: = false. left = [0,index) , right = [index,end]
			// @bIgnoreDelimit: = true.  left = [0,index) , right = (index,end]
			bool split(ulong index, String& strLeft, String& strRight, bool bIgnoreDelimit = false) const;
			// @bIgnoreDelimit: = false. left = [0,index) , right = [index,end]
			// @bIgnoreDelimit: = true.  left = [0,index) , right = (index,end]
			bool split(const String& delimit, String& strLeft, String& strRight, bool bIgnoreDelimit = false) const;
			TArray<String> split(const String& delimit, bool bIgnoreEmptySubString = true) const;
			bool split(const String& delimit, TArray<String>& strArray, bool bIgnoreEmptySubString = true) const;
			//TArrayV<String> split(const String& delimit) const;
			//fbool split(const String& delimit,TArrayV<String>& strArray) const;
			const String& subString(String& sub, ulong from, ulong count) const;

			/*-----------------------------------------------------------
			get sub-string.
			!true:		get the sub-string ok.
			!false:		failed to get the sub-string.
			@strSub:	return value. The sub-string.
			@strFrom:	string find from.include from char/string.
			@strTo:		string find to.include to char/string.
			@uIndexSubStr:		index of sub-string.
			@bDelimit:	true for get the sub-string with left-limit and right-limit.true is [from,to],false is (from ,to).
			@uFrom:		index find from.
			------------------------------------------------------------*/
			bool subString(String& strSub, const String& strFrom, const String& strTo, ulong &uIndexSubStr, bool bDelimit = true, ulong uFrom = 0) const;

			const TArray<String>& subString(TArray<String>& subArray, const String& strFrom, const String& strTo, bool bDelimit = true, ulong uFrom = 0) const;
			//const String& remove(ulong index,ulong count,String& strRemove);
			bool remove(ulong index, ulong count, String* strRemoved = NULL);
			bool remove(const String& sub, bool bAll = false);
			bool findIgnoreCase(const String& sub) const;
			bool find(const String& sub) const;
			bool find(const String& sub, ulong& index, ulong from = 0, bool bReverse = false) const;
			// find range is [from,to)
			bool find(const String& sub, ulong& index, ulong from, ulong to) const;
			ulong getSubStringCount(const String& sub) const;
			void clear();
			bool isEmpty() const;
			void toUpper();
			void toLower();
			bool compareIgnoreCase(const String& strCmp) const;
			void trim(const String& strTrim = " ");
			void trimLeft(const String& strTrim = " ");
			void trimRight(const String& strTrim = " ");
			void fromDWord(dword dwStr, bool bKeep = true);
			dword toDWord(bool bKeep = true) const;
			void fromByte(byte byVal);
			byte toByte() const;
			bool isDigital() const;
			bool isDigital(float& val) const;
			bool isDigital(dword& val) const;
			bool isDigital(uint& val) const;
			//fbool isDigital(fint& val) const;
			//fbool isDigital(flong& val) const;

			// Access
			std::string& getString();
			const string& getString() const;
			std::wstring getWString() const;
			ulong getSize() const;
			char* getChar();
			const char* getChar() const;
			byte getASCII(ulong uIdx = 0) const;
			// fill sz[]
			// @return: string size, not include '\0'
			ulong getChar(char* sz, ulong uSize) const;
			// fill bt[]
			// @return: string size, not include '\0'
			ulong getByte(byte* bt, ulong uSize) const;
			// convert
			std::wstring toWString() const;
			std::string toString() const;
			const wchar_t* toWChar();
			const wchar_t* toWChar(std::wstring& wstrTemp) const;
			//LPTSTR getTChar();
			//LPCTSTR getCTChar() const;
			//LPWSTR getWChar();
			//LPCWSTR getCWChar() const;

			// convert
			//template<class T>
			//T toValue(const EnumShaderValue& eShaderValue);

			float toFloat() const;
			int toInt() const;
			uint toUInt() const;
			long toLong() const;
			ulong toULong() const;
			word toWord() const;
			//fdword toDWord() const;
			bool toBool() const;

			bool checkFormat(const String& strPredefine, bool bCanBeEmpty = true, bool bIgnoreCase = true) const;
			bool checkFormat(const TArray<String>& aPredefine, bool bCanBeEmpty = true, bool bIgnoreCase = true) const;
			// @strEnterFlag: ignore if it is empty.
			// @uSizePerLine: ignore if it is 0.
			void wordWrap(const String& strEnterFlag, uint uSizePerLine = 0);

			//virtual EnumClassType getClassType(String* pStrClassName = NULL) const;
			//static EnumClassType sGetClassType();
			//static EnumResourceType sGetResourceType();

		public:
			//static LPWSTR sCharToWChar(const char* szStr, int size, const String::EnumCodePage& CodePage = CodePage_ACP);
			//static LPCWSTR sCharToCWChar(const char* szStr, int size, const String::EnumCodePage& CodePage = CodePage_ACP);
			//static LPTSTR sWCharToChar(LPCWSTR wStr, int size, EnumCodePage CodePage = CodePage_ACP);
			//static LPCTSTR sWCharToCChar(LPCWSTR wStr, int size, EnumCodePage CodePage = CodePage_ACP);
			static std::wstring toWString(const std::string& s);
			static std::string toString(const std::wstring& ws);
			static void encryption(std::string& s);
			static void decryption(std::string& s);

			template<class T>
			static String fromNumArray(const T* pData, uint uSize, uint uPrecision = 0);
			template<class T>
			static void toNumArray(T*& pData, uint &uSize, const String& strNum);

			static String sGetExePath();
			static String sGetCurrentPath();
			static String sGetSystemTempPath();
			static String sGetSystemTime(const String strDelimit = ",", bool bAddDayOfWeek = false, dword* dwDayOfWeek = NULL);
			static String sExtractFileName(const String& strPathFile);
			static String sSpace(ulong uSize);
			static String sRandomChar(char* singleChar = NULL, bool bWChar = false, String* strWhole = NULL);
			static String sRandomString(uint uCnt, bool bWChar = false);

			// convert
			static bool sToValue(float& val, const String& strValue);
			static bool sToValue(int& val, const String& strValue);
			static bool sToValue(long& val, const String& strValue);
			static bool sToValue(ulong& val, const String& strValue);
			// @strValue: string
			// @factor: scale factor, only for float.
			template<class T>
			static TArray<T> sGetDataArray(const String& strValue, T factor = (T)1.0);

		private:
			void copyOther(const String& other);
			// create memory and initialize state if necessary.
			virtual bool doCreate();
			// delete memory and initialize state if necessary.
			virtual void doRelease();

		public:
			static const String Space;
			static const String Tab2;
			static const String Tab4;
			static const String Tab8;
			static const String Enter;
			static const String Terminate;

			static const String Comma;
			static const String Semicolon;
			static const String Point;

		private:
			std::string		m_String;
			std::wstring	m_WString;
			bool			mbEncryption;
		};

		/*-----------------------------------------------------------
		class String
		------------------------------------------------------------*/
		template<class T>
		String String::fromNumArray(const T* pData, uint uSize, uint uPrecision /* = 0 */)
		{
			String strRe = "";
			if (nullptr == pData || uSize <= 0)
				return strRe;
			char sz[16];
			char prec[8] = "%d";
			switch (uPrecision)
			{
			case 0: strcpy(prec, "%d"); break;
			case 1: strcpy(prec, "%.1f"); break;
			case 2: strcpy(prec, "%.2f"); break;
			case 3: strcpy(prec, "%.3f"); break;
			//case 4: strcpy(prec, "%.4f"); break;
			default:
				strcpy(prec, "%.4f"); break;
			}
			for (uint i = 0; i < uSize; i++)
			{
				sprintf(sz, prec, pData[i]);
				strRe += sz;
			}
			strRe.trimRight(",");
			return strRe;
		}

		template<class T>
		void String::toNumArray(T*& pData, uint &uSize, const String& strNum)
		{
			pData = nullptr;
			uSize = 0;
			TArray<String> vStr = strNum.split(",");
			const uint uCnt = vStr.size();
			if (strNum.isEmpty() || uCnt <= 0)
				return;
			uSize = uCnt;
			pData = new T[uSize];
			for (uint i = 0; i < uCnt; i++)
			{
				pData[i] = (T)atoll(vStr[i].getChar());
			}
		}

		/*-----------------------------------------------------------
		class Tag
		------------------------------------------------------------*/
		class Tag : public IRoot
		{
		public:
			Tag();
			Tag(const String& name);
			Tag(int iTag);
			Tag(uint uTag);
			Tag(long lTag);
			Tag(ulong uTag);
			Tag(float fTag);
			Tag(char* szTag);
			Tag(const Tag& other);
			virtual ~Tag();

			//const Tag& operator =(const Tag& other) const;
			bool operator ==(const Tag& other) const;
			bool operator !=(const Tag& other) const;
			Tag& operator =(const Tag& other);
			const Tag& operator +=(const Tag& other);
			bool operator <(const Tag& other) const;
			Tag operator + (const Tag& other) const;
			void name(const String& name);
			const String& name() const;
			void id(ulong id);
			ulong id() const;
			bool isEmpty() const;
			void clear();

		protected:
			void copyOther(const Tag& other);
			virtual bool doCreate();
			virtual void doDestroy();

		private:
			//String* mpStrName;
			String	mstrName;
			ulong	muID;
		};

		/*-----------------------------------------------------------
		class Maths
		------------------------------------------------------------*/
		class Maths : virtual public IRoot
		{
		public:
			enum EBoundType
			{
				Bound_None,
				Bound_Left,
				Bound_Right,
				Bound_Both,
				Bound_Max
			};

		public:
			Maths();
			virtual ~Maths();
			static float tolerance();
			static int maxSize16();
			static int maxSize32();
			static float minSizeFloat();
			static float maxSizeFloat();
			static float PI();
			static float PIHalf();
			static float radianPerDegreen();
			static float degreenPerRadian();
			static float radianToAngle(float radian);
			static float angleToRadian(float angle);
			static bool isZero(float val);
			static bool isNearZero(float val);
			static bool isNear(float val, float cmp);
			static bool isEqual(float val, float cmp);
			static bool isBetween(float val, float max, float min = 0.0f);
			static bool isBetween(ulong val, ulong max, ulong min = 0);

		public:
			static float DWToFloat(dword dwordVal);
			static dword FloatToDW(float floatVal);

		public:
			template<class T>
			static bool isBetween(const T& val, const T& maxVal, const T& minVal = 0, const Maths::EBoundType& eBoundInclude = Maths::EBoundType::Bound_Left);

			template<class T>
			static T saturate(const T& val, const T& minVal, const T& maxVal);

			template<class T>
			static T saturate(const T& val, const T& minVal, const T& maxVal, bool bKeepMin);

		private:

		};

		/*-----------------------------------------------------------
		class Maths
		------------------------------------------------------------*/
		template<class T>
		bool Maths::isBetween(const T& val, const T& maxVal, const T& minVal /* = 0 */, const Maths::EBoundType& eBoundInclude /* = Maths::EBoundTypeBound_Left */)
		{
			return (val >= minVal && val < maxVal);
		}

		template<class T>
		T Maths::saturate(const T& val, const T& minVal, const T& maxVal)
		{
			FASSERT(minVal < maxVal);
			T valResult = val;
			if (val < minVal)
				valResult = minVal;
			else if (val > maxVal)
				valResult = maxVal;
			return valResult;
		};

		/*-----------------------------------------------------------
		@ bKeepMin: if not in this range, then if bKeepMin = true, return minVla, or return maxVal.
		------------------------------------------------------------*/
		template<class T>
		T Maths::saturate(const T& val, const T& minVal, const T& maxVal, bool bKeepMin)
		{
			FASSERT(minVal < maxVal);
			T valResult = val;
			if (val < minVal || val > maxVal)
				valResult = bKeepMin ? minVal : maxVal;
			return valResult;
		};

		/*-----------------------------------------------------------
		class FUnit
		------------------------------------------------------------*/
		class FUnit
		{
		public:
			FUnit();
			virtual ~FUnit();
			// get map value from actual unit.
			static float getMapValue(float meter);
			// get actual value from map unit.
			static float getActualValue(float pixel);

			// set how many Meters per-pixel.
			static void setScale(float meterPerPixel);
			// return how many Meters per-pixel.
			static float getScale();
			// return reciprocal of how many Meters per-pixel.
			static float getMapScale();

		private:
			static float	mfUnitPerPixel;// Default:	How many Meters per-pixel.
		};

		/*-----------------------------------------------------------
		class ThreadLock
		------------------------------------------------------------*/
		class ThreadLock : public IRoot
		{
		public:
			ThreadLock();
			virtual ~ThreadLock();
			void lock();
			void unLock();

		protected:
			std::mutex mMutex;
			//CRITICAL_SECTION	mCriSec;
		};

	}
}
