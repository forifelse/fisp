/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/base.h"

/*-----------------------------------------------------------
class String
------------------------------------------------------------*/
namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class IRoot
		------------------------------------------------------------*/
		IRoot::IRoot()
			:meState(EState::State_MAX)
			,meMemoryState(EMemory::Memory_Create)
		{

		}

		IRoot::~IRoot()
		{
			destroy();
			meMemoryState = Memory_Max;
			meState = State_MAX;
		}

		IRoot::IRoot(const IRoot& other)
		{
			Tag::destroyMem<Tag>(mpTag);
		}

		IRoot& IRoot::operator = (const IRoot& other)
		{
			return *this;
		}

		bool IRoot::operator < (const IRoot& other) const
		{
			return true;
		}

		bool IRoot::operator == (const IRoot& other) const
		{
			return true;
		}

		bool IRoot::create(void* pData /* = nullptr */)
		{
			if (State_MAKE == state())
				return false;
			bool rd = doCreate(pData);
			if (rd)
			{
				//Init();
				state(State_MAKE);
			}
			meMemoryState = EMemory::Memory_Create;
			return rd;
		}

		void IRoot::destroy()
		{
			if (State_FREE == state())
				return;
			//UnInit();
			doDestroy();
			state(State_FREE);
		}

		void IRoot::copyOther(const IRoot& other)
		{
			meMemoryState = other.meMemoryState;
			meState = other.meState;
			deepCopy<Tag>(mpTag, other.mpTag);
			mbEnable = other.mbEnable;
		}

		void IRoot::memoryState(const EMemory& eState)
		{
			meMemoryState = eState;
		}

		const EMemory& IRoot::memoryState() const
		{
			return meMemoryState;
		}

		bool IRoot::isMemoryCreate() const
		{
			return (Memory_Create == meMemoryState);
		}

		bool IRoot::isMemoryReference() const
		{
			return (Memory_Refrence == meMemoryState);
		}

		void IRoot::state(const EState& eState)
		{
			if (eState >= 0 && eState < State_MAX)
				meState = eState;
		}

		const EState& IRoot::state() const
		{
			return meState;
		}

		void IRoot::enable(bool bEnable)
		{
			mbEnable = bEnable;
		}

		bool IRoot::enable() const
		{
			return mbEnable;
		}

		bool IRoot::isMake() const
		{
			return (State_MAKE == meState);
		}

		bool IRoot::isFree() const
		{
			return (State_FREE == meState);
		}

		void IRoot::tag(const Tag& tag)
		{
			if (nullptr == mpTag)
			{
				mpTag = Tag::createMem<Tag>();
			}
			*mpTag = tag;
		}

		Tag* IRoot::tag()
		{
			return mpTag;
		}

		const Tag* IRoot::tag() const
		{
			return mpTag;
		}

		const Tag& IRoot::getTag() const
		{
			if (nullptr != mpTag)
			{
				return *mpTag;
			}
			return Tag();
		}

		bool IRoot::isUnknowTag() const
		{
			return (nullptr == mpTag || mpTag->name().isEmpty());
		}

		void IRoot::isUnknowTagThenSet(const Tag& flag)
		{
			if (isUnknowTag() && !flag.name().isEmpty())
			{
				tag(flag);
			}
		}

		bool IRoot::doCreate(void* pData /* = NULL */)
		{
			meMemoryState = Memory_Max;
			meState = State_MAX;
			return true;
		}

		void IRoot::doDestroy()
		{
			
		}

		/*-----------------------------------------------------------
		class String
		------------------------------------------------------------*/
		const String String::Space(" ");
		const String String::Tab2("  ");
		const String String::Tab4("    ");
		const String String::Tab8("        ");
		const String String::Enter("\r\n");
		const String String::Terminate("\0");

		const String String::Comma(",");
		const String String::Semicolon(";");
		const String String::Point(".");

		String::String()
			:mbEncryption(false)
		{
			//m_String.clear();
		}

		String::~String()
		{
			//m_String.clear();
		}

		String::String(const byte* bt)
			:mbEncryption(false)
			, m_String((const char*)bt)
		{
		}

		String::String(const char* s)
			: mbEncryption(false)
			//, m_String(s)
		{
			m_String = std::string(s);
		}

		String::String(const wchar* s)
			: mbEncryption(false)
			//,m_String(s)
		{
			m_WString = std::wstring(s);
			m_String = toString(m_WString);
		}

		String::String(const std::string& str)
			: m_String(str)
			, mbEncryption(false)
		{
		}

		String::String(const std::wstring& wstr)
			: m_String("")
			, mbEncryption(false)
		{
			m_String = toString(wstr);
		}

		String::String(char ch)
			:mbEncryption(false)
		{
			char szStr[4] = { ch };
			m_String = szStr;
		}

		String::String(bool b)
			:mbEncryption(false)
		{
			char szStr[8];
			b ? sprintf(szStr, "%s", "true") : sprintf(szStr, "%s", "false");
			m_String = szStr;
		}

		String::String(int index)
			:mbEncryption(false)
		{
			char szStr[256];
			sprintf(szStr, "%d", index);
			m_String = szStr;
		}

		String::String(uint uStr)
			:mbEncryption(false)
		{
			char szStr[256];
			sprintf(szStr, "%u", uStr);
			m_String = szStr;
		}

		String::String(long uStr)
			:mbEncryption(false)
		{
			char szStr[256];
			sprintf(szStr, "%lu", uStr);
			m_String = szStr;
		}

		String::String(ulong uStr)
			:mbEncryption(false)
		{
			char szStr[256];
			sprintf(szStr, "%u", uStr);
			m_String = szStr;
		}

		String::String(float fStr)
			:mbEncryption(false)
		{
			char szStr[256];
			sprintf(szStr, "%.15f", fStr);
			m_String = szStr;
			ulong idx = 0;
			if (find(String(".")))
			{
				trimRight("0");
				//trimRight(".");
				if (find(String("."), idx) && (getSize() == idx + 1))
				{
					operator += ("0");
				}
			}
		}

		//String::String(fdword dwStr)
		//{
		//	fromDWord(dwStr);
		//}

		//String::String(char* szStr)
		//{
		//	if(NULL == szMsg || strlen(szMsg) <= 0)
		//		return ;
		//	m_String = szStr;
		//}

		//String::String(char* szMsg, ...)
		//	:mbEncryption(false)
		//{
		//	if (NULL == szMsg || strlen(szMsg) <= 0)
		//		return;
		//	const ulong uSize = strlen(szMsg) + 1;
		//	assert(uSize <= 65535);
		//	//char* msg = new char[uSize];
		//	//char msg[uSize];
		//	char msg[65535];
		//	va_list valist;
		//	va_start(valist, szMsg);
		//	vsprintf(msg, szMsg, valist);
		//	va_end(valist);
		//	m_String = msg;
		//	//delete []msg;
		//	//msg = NULL;
		//}

		String::String(const String& other)
			:mbEncryption(false)
		{
			copyOther(other);
		}

		//String::String(String& s)
		//{
		//	m_String.clear();
		//	m_String.append(s.m_String);
		//}

		//FRD String::create()
		//{
		//	return F_OK;
		//}

		//FRD String::release()
		//{
		//	m_String.clear();
		//	return F_OK;
		//}

		String& String::operator = (const String& other)
		{
			IRoot::operator = (other);
			copyOther(other);
			return *this;
		}

		void String::copyOther(const String& other)
		{
			IRoot::operator = (other);
			m_String = other.m_String;
			mbEncryption = other.mbEncryption;
		}

		bool String::operator == (const String& s) const
		{
			return (m_String.compare(s.m_String) == 0);
		}

		bool String::operator != (const String& s) const
		{
			return (m_String.compare(s.m_String) != 0);
		}

		bool String::operator > (const String& s) const
		{
			return (m_String.compare(s.m_String) > 0);
		}

		bool String::operator < (const String& s) const
		{
			return (m_String.compare(s.m_String) < 0);
		}

		String String::operator + (const String& s) const
		{
			return String(m_String + s.m_String);
		}

		String& String::operator += (const String& s)
		{
			m_String += s.m_String;
			return *this;
		}

		bool String::doCreate()
		{
			m_String.clear();
			mbEncryption = false;
			return true;
		}

		void String::doRelease()
		{
			m_String.clear();
			mbEncryption = false;
		}

		//LPWSTR String::sCharToWChar(const char* szStr, int size, const String::EnumCodePage& CodePage /* = CodePage_ACP */)
		//{
		//	if (szStr == NULL || size <= 0)
		//		return NULL;
		//	LPWSTR wStr = new WCHAR[size];
		//	MultiByteToWideChar(CodePage, 0, szStr, size, wStr, size);
		//	return wStr;
		//}

		//LPCWSTR String::sCharToCWChar(const char* szStr, int size, const String::EnumCodePage& CodePage /* = CodePage_ACP */)
		//{
		//	if (szStr == NULL || size <= 0)
		//		return NULL;
		//	LPWSTR wStr = new WCHAR[size];
		//	MultiByteToWideChar(CodePage, 0, szStr, size, wStr, size);
		//	return wStr;
		//}

		//LPTSTR String::sWCharToChar(LPCWSTR wStr, int size, EnumCodePage CodePage)
		//{
		//	if (wStr == NULL || size <= 0)
		//		return NULL;
		//	LPCPINFO cp = NULL;
		//	GetCPInfo(CodePage, cp);
		//	LPSTR tStr = new char[size];
		//	WideCharToMultiByte(CodePage, 0, wStr, size, tStr, size, NULL, NULL);
		//	return (LPTSTR)tStr;
		//}

		//LPCTSTR String::sWCharToCChar(LPCWSTR wStr, int size, EnumCodePage CodePage)
		//{
		//	if (wStr == NULL || size <= 0)
		//		return NULL;
		//	LPCPINFO cp = NULL;
		//	GetCPInfo(CodePage, cp);
		//	LPSTR tStr = new char[size];
		//	WideCharToMultiByte(CodePage, 0, wStr, size, tStr, size, NULL, NULL);
		//	return (LPCTSTR)tStr;
		//}

		void String::setString(const char* s)
		{
			if (NULL == s)
			{
				m_String.clear();
				return;
			}
			m_String = s;
		}

		void String::setString(const String& s)
		{
			m_String = s.m_String;
		}

		void String::append(const char* s)
		{
			if (s == NULL)
				return;
			m_String.append(s);
		}

		void String::append(const String& s)
		{
			m_String += s.m_String;
		}

		bool String::insert(ulong index, const String& s, ulong count /*= 1*/)
		{
			FCHECK(index >= 0 && index <= getSize() && !s.isEmpty() && count > 0, false);
			m_String.insert(index, s.getString());
			return true;
		}

		bool String::insert(ulong uIndex, char ch)
		{
			m_String.insert(uIndex, 1, ch);
			return true;
		}

		bool String::setAt(ulong uIndex, char ch)
		{
			replace(uIndex, 1, &ch);
			return true;
		}

		char String::getAt(ulong uIndex) const
		{
			char ch = m_String.at(uIndex);
			return ch;
		}

		void String::encryption()
		{
			if (isEmpty())
			{
				return;
			}
			const ulong uSize = getSize();
			for (ulong i = 0; i<uSize; i++)
			{
				char ch = getAt(i);
				ch ^= 0xfa;
				if (0 == ch)
					continue;
				setAt(i, ch);
			}
			mbEncryption = true;
		}

		void String::decryption()
		{
			if (isEmpty())
			{
				return;
			}
			//char szVal[1];
			const ulong uSize = getSize();
			for (ulong i = 0; i<uSize; i++)
			{
				char ch = getAt(i);
				ch ^= 0xfa;
				if (0 == ch)
					continue;
				setAt(i, ch);
			}
			mbEncryption = false;
		}

		bool String::isEncryption() const
		{
			return mbEncryption;
		}

		void String::replace(ulong index, ulong count, const char* strReplace)
		{
			assert(index >= 0 && index < getSize() && count > 0 && strReplace != NULL);
			m_String.replace(index, count, strReplace);
		}

		void String::replace(const String& strOld, const String& strNew, ulong uFrom /* = 0 */, ulong uCount /* = 0 */, bool bAll /* = true */)
		{
			assert(!strOld.isEmpty() && !isEmpty());
			assert(uFrom >= 0 && uFrom < getSize());
			if (uCount <= 0)
			{
				uCount = getSize() - uFrom;
			}
			assert(uFrom + uCount <= getSize());
			bool bSameSize = (strOld.getSize() == strNew.getSize());
			ulong uSize = strOld.getSize();
			ulong uIndex = 0;
			while (find(strOld, uIndex, uFrom, uFrom + uCount))
			{
				if (bSameSize)
				{
					replace(uIndex, uSize, strNew.getChar());
				}
				else
				{
					//remove();
					//insert(uIndex)
				}
				if (!bAll)
					break;
			}
		}

		bool String::split(ulong index, String& strLeft, String& strRight, bool bIgnoreDelimit /* = false */) const
		{
			if (!Maths::isBetween(index, getSize()))
				return false;
			const string l = m_String.substr(0, index);
			if (bIgnoreDelimit)
				index++;
			const string r = (index <= m_String.size() - 1) ? m_String.substr(index, getSize()) : string("");
			strLeft = String(l.c_str());
			strRight = String(r.c_str());
			return true;
		}

		bool String::split(const String& delimit, String& strLeft, String& strRight, bool bIgnoreDelimit /* = false */) const
		{
			FCHECK(!isEmpty() && !delimit.isEmpty(), false);
			String str(delimit);
			ulong index = m_String.find(str.getString().c_str(), 0);
			return split(index, strLeft, strRight, bIgnoreDelimit);
		}

		TArray<String> String::split(const String& delimit, bool bIgnoreEmptySubString /* = true */) const
		{
			TArray<String> strList;
			strList.clear();
			if (isEmpty() || delimit.isEmpty())
				return strList;
			String strTemp(m_String.c_str());
			String strLine("");
			ulong index = 0;
			while (!strTemp.isEmpty() && strTemp.find(delimit, index))
			{
				strTemp.subString(strLine, 0, index);
				if (!strLine.isEmpty() || !bIgnoreEmptySubString)
					strList.add(strLine);
				strTemp.remove(strLine + delimit);
			}
			if (!strTemp.isEmpty())
			{
				strList.add(strTemp);
			}
			return strList;
		}

		bool String::split(const String& delimit, TArray<String>& strArray, bool bIgnoreEmptySubString /* = true */) const
		{
			FCHECK(!isEmpty() && !delimit.isEmpty(), false);
			strArray = split(delimit, bIgnoreEmptySubString);
			return strArray.size() > 0;
		}

		//TArrayV<String> String::split(const String& delimit) const
		//{
		//	TArrayV<String> strList;
		//	strList.clear();
		//	if(isEmpty() || delimit.isEmpty())
		//		return strList;
		//	String strTemp(m_String.c_str());
		//	String strLine("");
		//	ulong index = 0;
		//	while(!strTemp.isEmpty() && strTemp.find(delimit,index))
		//	{
		//		strTemp.subString(strLine,0,index);
		//		if(!strLine.isEmpty())
		//			strList.append(strLine);
		//		strTemp.remove(strLine + delimit);
		//	}
		//	if(!strTemp.isEmpty())
		//	{
		//		strList.append(strTemp);
		//	}
		//	return strList;
		//}

		//bool String::split(const String& delimit,TArrayV<String>& strArray) const
		//{
		//	strArray.clear();
		//	if(isEmpty() || delimit.isEmpty())
		//		return false;
		//	String strTemp(m_String.c_str());
		//	String strLine("");
		//	ulong index = 0;
		//	while(!strTemp.isEmpty() && strTemp.find(delimit,index))
		//	{
		//		strTemp.subString(strLine,0,index);
		//		if(!strLine.isEmpty())
		//			strArray.append(strLine);
		//		strTemp.remove(strLine + delimit);
		//	}
		//	if(!strTemp.isEmpty())
		//	{
		//		strArray.append(strTemp);
		//	}
		//	return true;
		//}

		const String& String::subString(String& sub, ulong from, ulong count) const
		{
			sub.clear();
			if (!Maths::isBetween(from, getSize()) || !Maths::isBetween(count - 1, getSize()) || (from + count - 1 > getSize()))
				return sub;
			string strRe = m_String.substr(from, count);
			sub.setString(strRe.c_str());
			return sub;
		}

		bool String::subString(String& strSub, const String& strFrom, const String& strTo, ulong &uIndexSubStr, bool bDelimit /* = true */, ulong uFrom /* = 0 */) const
		{
			FCHECK(!isEmpty() && !strFrom.isEmpty() && !strTo.isEmpty() && uFrom >= 0 && uFrom < m_String.size(), false);
			ulong idxFrom, idxTo;
			bool bOk = find(strFrom, idxFrom, uFrom);
			if (bOk && idxFrom + 1 < m_String.size())
			{
				bOk = find(strTo, idxTo, idxFrom + 1);
			}
			else
			{
				bOk = false;
			}
			if (!bOk)
			{
				strSub.clear();
				return false;
			}
			if (!bDelimit)
			{
				idxFrom += strFrom.getSize();
				idxTo--;
			}
			else
			{
				idxTo += strTo.getSize() - 1;
			}
			assert(idxFrom >= 0 && idxFrom < m_String.size());
			assert(idxTo >= idxFrom && idxTo < m_String.size());
			subString(strSub, idxFrom, idxTo - idxFrom + 1);
			uIndexSubStr = idxFrom;
			return true;
		}

		const TArray<String>& String::subString(TArray<String>& subArray, const String& strFrom, const String& strTo, bool bDelimit /* = true */, ulong uFrom /* = 0 */) const
		{
			subArray.clear();
			FCHECK(!isEmpty() && !strFrom.isEmpty() && !strTo.isEmpty() && uFrom >= 0 && uFrom < m_String.size(), subArray);
			ulong idxFrom = uFrom;
			String strSub;
			while (idxFrom < m_String.size())
			{
				if (!subString(strSub, strFrom, strTo, idxFrom, bDelimit, idxFrom))
				{
					break;
				}
				if (!strSub.isEmpty())
				{
					subArray.add(strSub);
				}
				idxFrom += strSub.getSize();
			}
			return subArray;
		}

		std::string& String::getString()
		{
			return m_String;
		}

		const string& String::getString() const
		{
			return m_String;
		}

		std::wstring String::getWString() const
		{
			//wstring wstr(m_String.begin(),m_String.end());
			//return wstr;
			return toWString(m_String);
		}

		ulong String::getSize() const
		{
			return m_String.size();
		}

		bool String::isEmpty() const
		{
			return (m_String.empty() || ('\0' == m_String.at(0)));
		}

		bool String::remove(ulong index, ulong count, String* strRemoved /* = NULL */)
		{
			FCHECK(index >= 0 && index < getSize() && index + count <= getSize(), false);
			string strRemovedTemp = m_String.substr(index, count);
			m_String.erase(index, count);
			if (NULL != strRemoved)
			{
				*strRemoved = String(strRemovedTemp.c_str());
			}
			return true;
		}

		bool String::remove(const String& sub, bool bAll /* = false */)
		{
			ulong index = m_String.find(sub.getString());
			bool bOk = remove(index, sub.getSize());
			if (bAll && bOk)
			{
				bool bRemove = true;
				while (bRemove)
				{
					index = m_String.find(sub.getString());
					bRemove = remove(index, sub.getSize());
				}
			}
			return bOk;
		}

		void String::toUpper()
		{
			char* str = const_cast<char*>(m_String.c_str());
			strupr(str);
			str = NULL;
		}

		void String::toLower()
		{
			char* str = const_cast<char*>(m_String.c_str());
			strlwr(str);
			str = NULL;
		}

		bool String::compareIgnoreCase(const String& strCmp) const
		{
			String strSrc(*this), strDec(strCmp);
			strSrc.toLower();
			strDec.toLower();
			return strSrc == strDec;
		}

		void String::trim(const String& strTrim /* = " " */)
		{
			trimLeft(strTrim);
			trimRight(strTrim);
		}

		void String::trimLeft(const String& strTrim /* = " " */)
		{
			FCHECK(!isEmpty() && !strTrim.isEmpty(), void());
			ulong uTrimSize = strTrim.getSize();
			ulong idx;
			String strRemove;
			while (m_String.size() > 0)
			{
				if (find(strTrim, idx) && idx == 0)
				{
					remove(idx, uTrimSize, &strRemove);
					assert(strRemove == strTrim);
				}
				else
				{
					break;
				}
			}
		}

		void String::trimRight(const String& strTrim /* = " " */)
		{
			FCHECK(!isEmpty() && !strTrim.isEmpty(), void());
			ulong uTrimSize = strTrim.getSize(), uCnt = getSize();
			ulong idx;
			String strRemove;
			while (m_String.size() > 0)
			{
				if (find(strTrim, idx, getSize() - strTrim.getSize()) && idx + uTrimSize == uCnt)
				{
					remove(idx, uTrimSize, &strRemove);
					uCnt = getSize();
					assert(strRemove == strTrim);
				}
				else
				{
					break;
				}
			}
		}

		bool String::findIgnoreCase(const String& sub) const
		{
			String strSrc(*this), strDec(sub);
			strSrc.toLower();
			strDec.toLower();
			return strSrc.find(strDec);
		}

		bool String::find(const String& sub) const
		{
			ulong idx = 0;
			return find(sub, idx, 0);
		}

		bool String::find(const String& sub, ulong& index, ulong from /* = 0 */, bool bReverse /* = false */) const
		{
			if (isEmpty() || sub.isEmpty() || from < 0 || from >= getSize())
				return false;
			if (bReverse)
				index = (ulong)m_String.rfind(sub.getChar(), from);
			else
				index = (ulong)m_String.find(sub.getChar(), from);
			return Maths::isBetween(index, getSize());
		}

		bool String::find(const String& sub, ulong& index, ulong from, ulong to) const
		{
			//if(to == 0)
			//	to = getSize();
			if (isEmpty() || sub.isEmpty() || to - from <= 0)
				return false;
			std::string str = m_String.substr(from, to - from);
			String strSub(str.c_str());
			bool bRe = strSub.find(sub, index, 0);
			return (bRe && Maths::isBetween(index, getSize()));
		}

		ulong String::getSubStringCount(const String& sub) const
		{
			if (isEmpty() || sub.isEmpty())
				return 0;
			ulong index = 0, from = 0, cnt = 0;
			while (find(sub, index, from))
			{
				cnt++;
				from = index + 1;
			}
			return cnt;
		}

		void String::clear()
		{
			m_String.clear();
		}

		char* String::getChar()
		{
			return (char*)(m_String.c_str());
		}

		const char* String::getChar() const
		{
			return m_String.c_str();
		}

		byte String::getASCII(ulong uIdx /* = 0 */) const
		{
			byte ascii = 0;
			if (!m_String.empty())
			{
				ascii = m_String[uIdx];
			}
			return ascii;
		}

		ulong String::getChar(char* sz, ulong uSize) const
		{
			FCHECK(NULL != sz && uSize > getSize(), 0);
			strcpy(sz, getChar());
			return getSize();
		}

		ulong String::getByte(byte* bt, ulong uSize) const
		{
			FCHECK(NULL != bt && uSize > getSize(), 0);
			memset(bt, 0, uSize);
			memcpy(bt, getChar(), getSize());
			return getSize();
		}

		std::wstring String::toWString() const
		{
			return toWString(m_String);
		}

		std::string String::toString() const
		{
			return m_String;
		}

		const wchar_t* String::toWChar()
		{
			m_WString = toWString();
			return m_WString.c_str();
		}

		const wchar_t* String::toWChar(std::wstring& wstrTemp) const
		{
			wstrTemp = toWString();
			return wstrTemp.c_str();
		}

		//LPTSTR String::getTChar()
		//{

		//	return getWChar();
		//}

		//LPCTSTR String::getCTChar() const
		//{

		//	return (TCHAR*)m_String.c_str();
		//}

		//LPWSTR String::getWChar()
		//{
		//	int len = (int)m_String.size() + 1;
		//	return sCharToWChar(m_String.c_str(), len);
		//}

		//LPCWSTR String::getCWChar() const
		//{
		//	int len = (int)m_String.size() + 1;//sizeof(m_String.c_str());
		//	return sCharToCWChar(m_String.c_str(), len);
		//}

		bool String::isDigital() const
		{
			if (isEmpty())
				return false;
			uint uSize = getSize();
			uint uDotSum = 0;
			uint uPositiveSignSum = 0;
			uint uNegtiveSignSum = 0;
			char ch;
			for (uint i = 0; i<uSize; i++)
			{
				ch = m_String.at(i);
				if (ch == '+')
				{
					uPositiveSignSum++;
					if (i != 0 || uPositiveSignSum > 1)
						return false;
				}
				else if (ch == '-')
				{
					uNegtiveSignSum++;
					if (i != 0 || uNegtiveSignSum > 1)
						return false;
				}
				else if (ch == '.')
				{
					uDotSum++;
					if (uDotSum > 1)
						return false;
				}
				else if (ch < '0' || ch > '9')
					return false;
			}
			return true;
		}

		bool String::isDigital(float& val) const
		{
			if (isDigital())
			{
				val = (float)(atof(m_String.c_str()));
				return true;
			}
			return false;
		}

		bool String::isDigital(dword& val) const
		{
			float fVal = 0.f;
			if (isDigital(fVal))
			{
				val = *((dword*)(&fVal));//Maths::PFFloatToDW(fVal);
				return true;
			}
			return false;
		}

		bool String::isDigital(uint& val) const
		{
			float fVal = 0.f;
			if (isDigital(fVal))
			{
				fVal = fabs(fVal);
				val = (uint)fVal;//Maths::PFFloatToDW(fVal);
				return true;
			}
			return false;
		}

		//bool String::isDigital(fint& val) const
		//{
		//	if(isEmpty())
		//		return false;
		//	fuint uSize = getSize();
		//	fuint uDotSum = 0;
		//	char ch;
		//	for(fuint i=0; i<uSize; i++)
		//	{
		//		ch = m_String.at(i);
		//		if(ch == '.')
		//		{
		//			uDotSum ++;
		//			if(uDotSum > 1)
		//				return false;
		//			else
		//				continue;
		//		}
		//		if(ch < '0' || ch > '9')
		//			return false;
		//	}
		//	val = atoi(m_String.c_str());
		//	return true;
		//}

		//bool String::isDigital(flong& val) const
		//{
		//	if(isEmpty())
		//		return false;
		//	fuint uSize = getSize();
		//	fuint uDotSum = 0;
		//	char ch;
		//	for(fuint i=0; i<uSize; i++)
		//	{
		//		ch = m_String.at(i);
		//		if(ch == '.')
		//		{
		//			uDotSum ++;
		//			if(uDotSum > 1)
		//				return false;
		//			else
		//				continue;
		//		}
		//		if(ch < '0' || ch > '9')
		//			return false;
		//	}
		//	val = atol(m_String.c_str());
		//	return true;
		//}

		std::wstring String::toWString(const std::string& s)
		{
			std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
			setlocale(LC_ALL, "chs");
			const char* _Source = s.c_str();
			size_t _Dsize = s.size() + 1;
			wchar_t *_Dest = new wchar_t[_Dsize];
			wmemset(_Dest, 0, _Dsize);
			mbstowcs(_Dest, _Source, _Dsize);
			std::wstring result = _Dest;
			delete[]_Dest;
			setlocale(LC_ALL, curLocale.c_str());
			return result;
		}

		std::string String::toString(const std::wstring& ws)
		{
			string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
			setlocale(LC_ALL, "chs");
			const wchar_t* _Source = ws.c_str();
			size_t _Dsize = 2 * ws.size() + 1;
			char *_Dest = new char[_Dsize];
			memset(_Dest, 0, _Dsize);
			wcstombs(_Dest, _Source, _Dsize);
			string result = _Dest;
			delete[]_Dest;
			setlocale(LC_ALL, curLocale.c_str());
			return result;
		}

		void String::encryption(std::string& s)
		{
			String str(s);
			str.encryption();
			s = str.getString();
		}

		void String::decryption(std::string& s)
		{
			String str(s);
			str.decryption();
			s = str.getString();
		}

		String String::sGetExePath()
		{
			return String();
			//TCHAR sz[MAX_PATH] = { 0 };
			//::GetModuleFileName(NULL, sz, MAX_PATH);
			//String str(sz);
			//ulong uIdx = 0, uFrom = 0;
			//while (str.find(String("\\"), uIdx, uFrom, false))
			//{
			//	uFrom = uIdx + 1;
			//}
			//str.remove(uFrom, str.getSize() - uFrom);
			//return str;
		}

		String String::sGetCurrentPath()
		{
			return String();
			//WCHAR path[MAX_PATH];
			//::GetCurrentDirectory(MAX_PATH, path);
			//return String(path);
		}

		String String::sGetSystemTempPath()
		{
			return String();
			//WCHAR path[MAX_PATH];
			//::GetTempPath(MAX_PATH, path);
			//return String(path);
		}

		String String::sGetSystemTime(const String strDelimit /* = "," */, bool bAddDayOfWeek /* = false */, dword* dwDayOfWeek /* = NULL */)
		{
			return String();
			//char day[16], time[16];
			//SYSTEMTIME st;
			//::GetLocalTime(&st);
			////sprintf(time,"%04d-%02d-%02d, %02d:%02d:%02d %03d  ",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
			//sprintf(day, "%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
			//sprintf(time, "%02d:%02d:%02d %03d ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
			//String strTime(day);
			//strTime += strDelimit;
			//strTime += String(time);
			//if (bAddDayOfWeek)
			//{
			//	String dow;
			//	switch (st.wDayOfWeek)
			//	{
			//	case 0: dow = "Sunday";		break;
			//	case 1: dow = "Monday";		break;
			//	case 2: dow = "Tuesday";	break;
			//	case 3: dow = "Wednesday";	break;
			//	case 4: dow = "Thursday";	break;
			//	case 5: dow = "Friday";		break;
			//	case 6: dow = "Saturday";	break;
			//	default:
			//		dow = "";
			//		break;
			//	}
			//	strTime += dow;
			//}
			//if (NULL != dwDayOfWeek)
			//{
			//	*dwDayOfWeek = st.wDayOfWeek;
			//}
			//return strTime;
		}

		String String::sExtractFileName(const String& strPathFile)
		{
			assert(!strPathFile.isEmpty());
			String strRe("");
			ulong uIndex, uIndex_0;
			const ulong uFrom = strPathFile.getSize() - 1;
			bool bFind = strPathFile.find("/", uIndex, uFrom, true);
			bool bFind_0 = strPathFile.find("\\", uIndex_0, uFrom, true);
			if (bFind && bFind_0)
			{
				uIndex = (uIndex >= uIndex_0) ? uIndex : uIndex_0;
			}
			else if (bFind)
			{
				;//uIndex = uIndex
			}
			else if (bFind_0)
			{
				uIndex = uIndex_0;
			}
			else
			{
				strRe = strPathFile;
				return strRe;
			}
			uIndex++;
			strPathFile.subString(strRe, uIndex, strPathFile.getSize() - uIndex);

			return strRe;
		}

		String String::sSpace(ulong uSize)
		{
			String strRe("");
			for (ulong i = 0; i<uSize; i++)
			{
				strRe += String::Space;
			}
			return strRe;
		}

		String String::sRandomChar(char* singleChar /* = NULL */, bool bWChar /* = false */, String* strWhole /* = NULL */)
		{
			const uint uMax = bWChar ? 256 : 128;
			char flag[256];
			for (uint i = 0; i<256; i++)
				flag[i] = i;
			const uint uTurns = rand() % 5;
			for (uint i = 0; i<uTurns; i++)
				std::random_shuffle(flag, flag + uMax);
			char ch = flag[0];
			if (NULL != singleChar)
				*singleChar = ch;
			if (NULL != strWhole)
				*strWhole = String(flag);
			String strRe(ch);
			return strRe;
		}

		String String::sRandomString(uint uCnt, bool bWChar /* = false */)
		{
			String strRe, strTemp;
			const uint uMax = bWChar ? 256 : 128;
			uint uTimes = uCnt / uMax;
			for (uint i = 0; i<uTimes; i++)
			{
				sRandomChar(NULL, bWChar, &strTemp);
				strRe += strTemp;
			}
			uTimes = uCnt - uTimes * uMax;
			assert(uTimes < uMax);
			if (uTimes > 0)
			{
				sRandomChar(NULL, bWChar, &strTemp);
				strTemp.remove(uTimes, strTemp.getSize() - uTimes);
				strRe += strTemp;
			}
			return strRe;
		}

		bool String::sToValue(float& val, const String& strValue)
		{
			CHECK_EXP(!strValue.isEmpty(), false);
			try
			{
				val = (float)(atof(strValue.getChar()));
				return true;
			}
			//catch (CMemoryException* e)
			//{
			//	return false;
			//}
			//catch (CFileException* e)
			//{
			//	return false;
			//}
			//catch (CException* e)
			//{
			//	return false;
			//}
			catch (...)
			{
				return false;
			}
		}

		bool String::sToValue(int& val, const String& strValue)
		{
			CHECK_EXP(!strValue.isEmpty(), false);
			try
			{
				val = atoi(strValue.getChar());
				return true;
			}
			//catch (CMemoryException* e)
			//{
			//	return false;
			//}
			//catch (CFileException* e)
			//{
			//	return false;
			//}
			//catch (CException* e)
			//{
			//	return false;
			//}
			catch (...)
			{
				return false;
			}
		}

		bool String::sToValue(long& val, const String& strValue)
		{
			CHECK_EXP(!strValue.isEmpty(), false);
			try
			{
				val = atol(strValue.getChar());
				return true;
			}
			//catch (CMemoryException* e)
			//{
			//	return false;
			//}
			//catch (CFileException* e)
			//{
			//	return false;
			//}
			//catch (CException* e)
			//{
			//	return false;
			//}
			catch (...)
			{
				return false;
			}
		}

		bool String::sToValue(ulong& val, const String& strValue)
		{
			CHECK_EXP(!strValue.isEmpty(), false);
			try
			{
				val = atol(strValue.getChar());
				return true;
			}
			//catch (CMemoryException* e)
			//{
			//	return false;
			//}
			//catch (CFileException* e)
			//{
			//	return false;
			//}
			//catch (CException* e)
			//{
			//	return false;
			//}
			catch (...)
			{
				return false;
			}
		}

		void String::fromByte(byte byVal)
		{
			char sz[256];
			_itoa(byVal, sz, 10);
			m_String = sz;
		}

		byte String::toByte() const
		{
			FCHECK(!isEmpty(), 0);
			uint val = atoi(getChar());
			return (byte)val;
		}

		void String::fromDWord(dword dwStr, bool bKeep /* = true */)
		{
			char szStr[256];
			if (bKeep)
			{
				_ltoa(dwStr, szStr, 10);
			}
			else
			{
				//ltoa(dwStr,szStr,16);
				char* szStr = (char*)dwStr;
				m_String = szStr;
			}
			m_String = szStr;
		}

		dword String::toDWord(bool bKeep /* = true */) const
		{
			dword dwStr = 0;
			if (bKeep)
			{
				dwStr = (dword)atol(m_String.c_str());
			}
			else
			{
				dwStr = (dword)(m_String.c_str());
			}
			return dwStr;
		}

		float String::toFloat() const
		{
			FCHECK(!isEmpty(), 0);
			return (float)(atof(getChar()));
		}

		int String::toInt() const
		{
			FCHECK(!isEmpty(), 0);
			return atoi(getChar());
		}

		uint String::toUInt() const
		{
			FCHECK(!isEmpty(), 0);
			return atoi(getChar());
		}

		long String::toLong() const
		{
			FCHECK(!isEmpty(), 0);
			return atol(getChar());
		}

		ulong String::toULong() const
		{
			FCHECK(!isEmpty(), 0);
			return atol(getChar());
		}

		word String::toWord() const
		{
			return (word)(toLong());
		}

		//fdword String::toDWord() const
		//{
		//	return toLong();
		//}

		bool String::toBool() const
		{
			assert(checkFormat(String("true,false")));
			bool bRe = false;
			if (compareIgnoreCase("true"))
				bRe = true;
			else if (compareIgnoreCase("false") || isEmpty())
				bRe = false;

			return bRe;
		}

		bool String::checkFormat(const String& strPredefine, bool bCanBeEmpty /* = true */, bool bIgnoreCase /* = true */) const
		{
			TArray<String> strArray;
			strArray = strPredefine.split(",");
			return checkFormat(strArray, bCanBeEmpty, bIgnoreCase);
		}

		bool String::checkFormat(const TArray<String>& aPredefine, bool bCanBeEmpty /* = true */, bool bIgnoreCase /* = true */) const
		{
			if (bCanBeEmpty && isEmpty())
				return true;
			bool bHas = false;
			for (uint i = 0; i<aPredefine.size(); i++)
			{
				//bHas = bIgnoreCase? aPredefine[i].compareIgnoreCase(*this) : (aPredefine[i] == *this);
				bHas = bIgnoreCase ? aPredefine.getAt(i).compareIgnoreCase(*this) : (aPredefine.getAt(i) == *this);
				if (bHas)
					return true;
			}
			return false;
		}

		void String::wordWrap(const String& strEnterFlag, uint uSizePerLine /* = 0 */)
		{
			if (isEmpty())
				return;

			if (!strEnterFlag.isEmpty())
			{
				replace(strEnterFlag, String::Enter);
			}
			if (uSizePerLine > 0 && uSizePerLine < getSize())
			{
				ulong uIndex = 0, uFrom = 0;
				const ulong uCnt = uSizePerLine + String::Enter.getSize();
				bool bFind = false;
				while (uFrom < getSize())
				{
					bFind = find(String::Enter, uIndex, uFrom, uFrom + uCnt);
					if (bFind)
					{
						uFrom += uIndex + String::Enter.getSize();
						continue;
					}
					else
					{
						insert(uFrom + uSizePerLine, String::Enter);
						uFrom += uCnt;
					}
				}
			}
		}

		//EnumClassType String::getClassType(String* pStrClassName /* = NULL */) const
		//{
		//	if (NULL != pStrClassName)
		//		*pStrClassName = "String";
		//	return Class_FString;
		//}

		//EnumClassType String::sGetClassType()
		//{
		//	return Class_FString;
		//}

		//EnumResourceType String::sGetResourceType()
		//{
		//	return Resource_RawString;
		//}

		/*-----------------------------------------------------------
		class Tag
		------------------------------------------------------------*/
		Tag::Tag()
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
		}

		Tag::Tag(const String& name)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = name;
			mstrName = name;
		}

		Tag::Tag(int iTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(iTag);
			mstrName = String(iTag);
		}

		Tag::Tag(uint uTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(uTag);
			mstrName = String(uTag);
		}

		Tag::Tag(long lTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(lTag);
			mstrName = String(lTag);
		}

		Tag::Tag(ulong uTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(uTag);
			mstrName = String(uTag);
		}

		Tag::Tag(float fTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(fTag);
			mstrName = String(fTag);
		}

		Tag::Tag(char* szTag)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			create();
			//*mpStrName = String(szTag);
			mstrName = String(szTag);
		}

		Tag::Tag(const Tag &other)
			//:mpStrName(NULL)
			:mstrName("")
			, muID(0)
		{
			copyOther(other);
		}

		Tag::~Tag()
		{
			destroy();
		}

		bool Tag::operator ==(const Tag& other) const
		{
			return (mstrName == other.mstrName && muID == other.muID);
			//return (NULL != mpStrName && NULL != other.mpStrName && *mpStrName == other.getName() && muID == other.muID);
		}

		bool Tag::operator !=(const Tag& other) const
		{
			return !(*this == (other));
		}

		//const Tag& Tag::operator =(const Tag& other) const
		//{
		//	if(*this == other)
		//		return *this;
		//	//m_strName = other.getName();
		//	return *this;
		//}

		Tag& Tag::operator = (const Tag& other)
		{
			copyOther(other);
			return *this;
		}

		const Tag& Tag::operator += (const Tag& other)
		{
			//assert(NULL != mpStrName);
			//*mpStrName += other.getName();
			mstrName += other.mstrName;
			return *this;
		}

		bool Tag::operator <(const Tag& other) const
		{
			return (muID == other.muID) ? (mstrName < other.mstrName) : (muID < other.muID);
			//return (muID == other.muID)? (*mpStrName < other.getName()) : (muID < other.muID);
		}

		Tag Tag::operator + (const Tag& other) const
		{
			Tag tagResult(*this);
			tagResult.name(mstrName + other.mstrName);
			//tagResult.getName() += other.getName();
			return tagResult;
		}

		void Tag::copyOther(const Tag& other)
		{
			IRoot::operator = (other);
			if (*this == other)
				return;
			mstrName = other.mstrName;
			//String::sDeepCopy<String>(mpStrName,other.mpStrName);
			muID = other.muID;
		}

		bool Tag::doCreate()
		{
			mstrName = String("");
			//mpStrName	= String::sNew<String>();
			muID = 0;
			return true;
		}

		void Tag::doDestroy()
		{
			mstrName = String("");
			//String::sDelete<String>(mpStrName);
			muID = 0;
		}

		const String& Tag::name() const
		{
			//assert(NULL != mpStrName);
			//return *mpStrName;
			return mstrName;
		}

		void Tag::name(const String& name)
		{
			//if(NULL == mpStrName)
			//	create();
			//*mpStrName = name;
			mstrName = name;
		}

		void Tag::id(ulong uID)
		{
			muID = uID;
		}
		ulong Tag::id() const
		{
			return muID;
		}

		bool Tag::isEmpty() const
		{
			//if(NULL == mpStrName)
			//	return true;
			//return mpStrName->isEmpty();
			return mstrName.isEmpty();
		}

		void Tag::clear()
		{
			//if(NULL != mpStrName)
			//	mpStrName->clear();
			mstrName.clear();
			muID = 0;
		}

		/*-----------------------------------------------------------
		class Maths
		------------------------------------------------------------*/
		Maths::Maths()
		{

		}

		Maths::~Maths()
		{

		}

		float Maths::tolerance()
		{
			return 0.0000000001f;
		}

		int Maths::maxSize16()
		{
			return 65535;      //2^16 -1
		}

		int Maths::maxSize32()
		{
			return 4294967295; //2^32 -1;
		}

		float Maths::minSizeFloat()
		{
			return -1.7976931348623158e+38f;//2.2250738585072014e-308;//DBL_MIN
		}

		float Maths::maxSizeFloat()
		{
			return 1.7976931348623158e+38f;//1.7976931348623158e+308;//DBL_MAX
		}

		float Maths::PI()
		{
			return 3.14159265358979323846f;
		}

		float Maths::PIHalf()
		{
			return 1.57079632679489661923f;
		}

		float Maths::radianPerDegreen()
		{
			return 0.0174533f;	// PI/180.0
		}

		float Maths::degreenPerRadian()
		{
			return 57.29578f;	// 180.0/PI
		}

		float Maths::radianToAngle(float radian)
		{
			return (radian * 180.f / PI());
		}

		float Maths::angleToRadian(float angle)
		{
			return (angle * PI() / 180.f);
		}

		bool Maths::isZero(float val)
		{
			return val == 0.f;
		}

		bool Maths::isNearZero(float val)
		{
			return (val < tolerance()) && (val >= -1.f * tolerance());
		}

		bool Maths::isNear(float val, float cmp)
		{
			return fabs(val - cmp) <= Maths::tolerance();
		}

		bool Maths::isEqual(float val, float cmp)
		{
			return val == cmp;
		}

		bool Maths::isBetween(float val, float max, float min /* = 0.0f */)
		{
			return (val >= min && val < max);
		}

		bool Maths::isBetween(ulong val, ulong max, ulong min /* = 0 */)
		{
			return (val >= min && val < max);
		}

		float Maths::DWToFloat(dword dwordVal)
		{
			return *(float*)(&dwordVal);
		}

		dword Maths::FloatToDW(float floatVal)
		{
			return *(dword*)(&floatVal);
		}

		/*-----------------------------------------------------------
		class FUnit
		------------------------------------------------------------*/
		float FUnit::mfUnitPerPixel = 10;
		FUnit::FUnit()
		{
			;
		}

		FUnit::~FUnit()
		{
			;
		}

		float FUnit::getMapValue(float meter)
		{
			assert(mfUnitPerPixel > 0.f);
			return (meter / mfUnitPerPixel);
		}

		float FUnit::getActualValue(float pixel)
		{
			assert(mfUnitPerPixel > 0.f);
			return (pixel * mfUnitPerPixel);
		}

		void FUnit::setScale(float unitPerPixel)
		{
			assert(!Maths::isNearZero(unitPerPixel));
			if (unitPerPixel > 0.f)
			{
				mfUnitPerPixel = unitPerPixel;
			}
		}

		float FUnit::getScale()
		{
			return mfUnitPerPixel;
		}

		float FUnit::getMapScale()
		{
			assert(mfUnitPerPixel > 0.f);
			return 1.f / mfUnitPerPixel;
		}

		/*-----------------------------------------------------------
		class ThreadLock
		------------------------------------------------------------*/
		ThreadLock::ThreadLock()
		{
			//InitializeCriticalSection(&mCriSec);
		}

		ThreadLock::~ThreadLock()
		{
			//DeleteCriticalSection(&mCriSec);
		}

		void ThreadLock::lock()
		{
			mMutex.lock();
			//EnterCriticalSection(&mCriSec);
		}

		void ThreadLock::unLock()
		{
			mMutex.unlock();
			//LeaveCriticalSection(&mCriSec);
		}

	}
}