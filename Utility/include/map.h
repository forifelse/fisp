/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <map>
using namespace std;
#include "inUtility.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class TMap
		------------------------------------------------------------*/
		template<class TKey, class TVal>
		class TMap : public IRoot
		{
		public:
			TMap();
			virtual ~TMap();
			TVal& operator[] (const TKey& key);
			const TVal& operator[] (const TKey& key) const;
			bool add(const TKey& key, const TVal& val);
			//bool insert(ulong uIndex,const TKey& key,const TVal& val);
			bool remove(const TKey& key, TVal* removedVal = NULL);
			bool replace(const TKey& oldKey, const TKey& newKey, TVal* newVal = NULL);
			TVal* getBufferPointor(TVal* &pVal, ulong &uNumber) const;
			ulong getBufferSize() const;
			bool fromBufferPointor(const TVal* &pVal, ulong uNumber);
			// @ifNotFound: return this value if not found
			bool findElement(const TKey& key, TVal &val, const TVal& ifNotFound = TVal()) const;
			bool findElement(const TKey& key) const;
			bool findKeyFromValue(TKey &key, const TVal& val) const;
			bool setAtBegin(const TKey& key);
			bool setAtEnd(const TKey& key);
			bool swap(const TKey& keyA, const TKey& keyB);
			bool sort(bool bAscend = true);
			bool sortAs(const std::vector<TKey>& vKey);
			bool checkCanSort() const;
			bool checkCanSortAs(const std::vector<TKey>& vKey) const;
			TVal& getAt(ulong index);
			//const TVal& getAt(ulong index) const;
			TVal getAt(ulong index) const;
			TVal& getAt(TKey& key, TVal& val, ulong index);
			const TVal& getAt(TKey& key, TVal& val, ulong index) const;
			ulong size() const;
			void clear();

		private:
			std::map<TKey, TVal>	mMap;
			std::vector<TKey>		mvKey;
		};

		/*-----------------------------------------------------------
		class TMap
		------------------------------------------------------------*/
		template<class TKey, class TVal>
		TMap<TKey, TVal>::TMap()
		{
			;
		}

		template<class TKey, class TVal>
		TMap<TKey, TVal>::~TMap()
		{
			mMap.clear();
			mvKey.clear();
		}

		template<class TKey, class TVal>
		TVal& TMap<TKey, TVal>::operator[] (const TKey& key)
		{
			return mMap[key];
		}

		template<class TKey, class TVal>
		const TVal& TMap<TKey, TVal>::operator[] (const TKey& key) const
		{
			return mMap[key];
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::add(const TKey& key, const TVal& val)
		{
			FASSERT(mvKey.size() == mMap.size());
			bool bAdded = false;
			const ulong uSize = mMap.size();
			mMap.insert(pair<TKey, TVal>(key, val));
			if (uSize == mMap.size() - 1)
			{
				mvKey.push_back(key);
				bAdded = true;
			}
			FASSERT(mMap.size() == mvKey.size());
			return bAdded;
		}

		//bool insert(ulong uIndex,const TKey& key,const TVal& val);

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::remove(const TKey& key, TVal* removedVal /* = NULL */)
		{
			FASSERT(mMap.size() == mvKey.size());
			std::map<TKey, TVal>::iterator it = mMap.find(key);
			if (mMap.end() == it)
				return false;
			if (NULL != removedVal)
				*removedVal = mMap[key];
			std::vector<TKey>::iterator itKey = mvKey.begin();
			for (; itKey != mvKey.end(); itKey++)
			{
				if (*itKey == (*it).first)
					break;
			}
			mvKey.erase(itKey);
			mMap.erase(it);
			FASSERT(mMap.size() == mvKey.size());
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::replace(const TKey& oldKey, const TKey& newKey, TVal* newVal /* = NULL */)
		{
			FASSERT(mMap.size() == mvKey.size());
			TVal val;
			if (!remove(oldKey, &val))
				return false;
			if (NULL != newVal)
				val = *newVal;
			bool bOk = add(newKey, val);
			FASSERT(mMap.size() == mvKey.size());
			return bOk;
		}

		template<class TKey, class TVal>
		TVal* TMap<TKey, TVal>::getBufferPointor(TVal* &pVal, ulong &uNumber) const
		{
			FREE_BASEPTR(pVal);
			uNumber = 0;
			FCHECK(mMap.size() > 0, pVal);
			uNumber = mMap.size();
			pVal = new TVal[uNumber];
			TVal* pTemp = pVal;
			for (ulong i = 0; i < mMap.size(); i++)
			{
				*pTemp = mMap[i];
				pTemp++;
			}
			pTemp = NULL;
			return pVal;
		}

		template<class TKey, class TVal>
		ulong TMap<TKey, TVal>::getBufferSize() const
		{
			return  mMap.size() * sizeof(TVal);
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::fromBufferPointor(const TVal* &pVal, ulong uNumber)
		{
			FCHECK(pVal != NULL && uNumber > 0, false);
			mMap.resize(uNumber);
			const TVal* pTemp = pVal;
			for (ulong i = 0; i < mMap.size(); i++)
			{
				mMap[i] = *pTemp;
				pTemp++;
			}
			pTemp = NULL;
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::findElement(const TKey& key, TVal &val, const TVal& ifNotFound = TVal()) const
		{
			std::map<TKey, TVal>::const_iterator it = mMap.find(key);
			if (it == mMap.end())
			{
				val = ifNotFound;
				return false;
			}
			val = (TVal)((*it).second);
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::findElement(const TKey& key) const
		{
			std::map<TKey, TVal>::const_iterator it = mMap.find(key);
			return (it != mMap.end());
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::findKeyFromValue(TKey &key, const TVal& val) const
		{
			map<TKey, TVal>::const_iterator it = mMap.begin();
			for (; it != mMap.end(); ++it)
			{
				if (it->second == val)
				{
					key = it->first;
					return true;
				}
			}
			return false;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::setAtBegin(const TKey& key)
		{
			return  true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::setAtEnd(const TKey& key)
		{
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::swap(const TKey& keyA, const TKey& keyB)
		{
			FASSERT(keyA != keyB);
			flong iA = -1, iB = -1;
			for (flong i = 0; i < mvKey.size() && (iA == -1 || iB == -1); i++)
			{
				if (keyA == mvKey[i] && iA == -1)
				{
					iA = i;
				}
				if (keyB == mvKey[i] && iB == -1)
				{
					iB = i;
				}
			}
			std::swap(mvKey[iA], mvKey[iB]);
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::sort(bool bAscend = true)
		{
			FASSERT(checkCanSort());
			std::sort(mvKey.begin(), mvKey.end());
			if (!bAscend)
				std::reverse(mvKey.begin(), mvKey.end());
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::sortAs(const std::vector<TKey>& vKey)
		{
			if (std::equal(mvKey.begin(), mvKey.end(), vKey.begin()))
				return true;
			FASSERT(checkCanSortAs(vKey));
			mvKey = vKey;
			return true;
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::checkCanSort() const
		{
			return (mvKey.size() == mMap.size());
		}

		template<class TKey, class TVal>
		bool TMap<TKey, TVal>::checkCanSortAs(const std::vector<TKey>& vKey) const
		{
			FASSERT(checkCanSort());
			FASSERT(mvKey.size() == vKey.size());
			std::vector<TKey> v1(mvKey), v2(vKey);
			std::sort(v1.begin(), v1.end());
			std::sort(v2.begin(), v2.end());
			return std::equal(v1.begin(), v1.end(), v2.begin());
		}

		template<class TKey, class TVal>
		TVal& TMap<TKey, TVal>::getAt(ulong index)
		{
			assert(index >= 0 && index < mMap.size());
			TKey key;
			key = mvKey[index];
			return mMap[key];
		}

		template<class TKey, class TVal>
		//const TVal& TMap<TKey,TVal>::getAt(ulong index) const
		TVal TMap<TKey, TVal>::getAt(ulong index) const
		{
			assert(index >= 0 && index < mMap.size());
			TKey key;
			key = mvKey[index];
			TVal val;
			bool bOk = findElement(key, val);
			FASSERT(bOk);
			return val;//mMap[key];
		}

		template<class TKey, class TVal>
		TVal& TMap<TKey, TVal>::getAt(TKey& key, TVal& val, ulong index)
		{
			assert(index >= 0 && index < mMap.size());
			key = mvKey[index];
			val = mMap[key];
			return mMap[key];
		}

		template<class TKey, class TVal>
		const TVal& TMap<TKey, TVal>::getAt(TKey& key, TVal& val, ulong index) const
		{
			assert(index >= 0 && index < mMap.size());
			key = mvKey[index];
			bool bOk = findElement(key, val);
			FASSERT(bOk);
			return val;
		}

		template<class TKey, class TVal>
		ulong TMap<TKey, TVal>::size() const
		{
			FASSERT(mMap.size() == mvKey.size());
			return (ulong)mMap.size();
		}

		template<class TKey, class TVal>
		void TMap<TKey, TVal>::clear()
		{
			mMap.clear();
			mvKey.clear();
			FASSERT(mMap.size() == 0 && mvKey.size() == 0);
		}














		/*-----------------------------------------------------------
		class FMapBase
		------------------------------------------------------------*/
		class FMapBase //: public IContainer
		{
		private:

		public:
			FMapBase()				{}
			virtual ~FMapBase()		{}
			virtual int GetSize() const
			{
				return 0;
			}

			virtual bool operator < (const FMapBase& other)
			{
				return GetSize() < other.GetSize();
			}
		};

		/*-----------------------------------------------------------
		class TMaps
		------------------------------------------------------------*/
		template <class TKey, class TVal>
		class TIteratorMapS;

		template <class TKey, class TVal>
		class TMaps //: public FMapBase//,public TIIterator<TVal>
		{
		protected:
			typedef std::map<TKey, TVal> MAPS;
			MAPS m_maps;
			//MAPS::iterator mIterator;
			std::vector<TKey>	mvKey;

		public:
			friend class IIterator;

			TMaps()
			{
				//Init();
				m_maps.clear();
				//m_curIterator = m_maps.begin();
				mvKey.clear();
			}

			virtual ~TMaps()
			{
				//UnInit();
				m_maps.clear();
				//m_curIterator = m_maps.end();
				mvKey.clear();
			}

			TMaps(const TMaps<TKey, TVal>& other)
			{
				//m_maps = other;
			}

			void Init()
			{
				m_maps.clear();
				mvKey.clear();
			}

			void UnInit()
			{
				m_maps.clear();
				mvKey.clear();
			}

			int GetSize() const
			{
				return (int)m_maps.size();
			}

			bool isEmpty() const
			{
				return (GetSize() <= 0);// || m_maps.size() != mvKey.size());
			}

			//bool Add(const TKey& tag,const TVal& val)
			//{
			//	FASSERT(mvKey.size() == m_maps.size());
			//	bool bAdded = false;
			//	const ulong uSize = m_maps.size();
			//	m_maps.insert(pair<TKey,TVal>(tag,val));
			//	if(uSize == m_maps.size() - 1)
			//	{
			//		mvKey.push_back(tag);
			//		bAdded = true;
			//	}
			//	FASSERT(m_maps.size() == mvKey.size());
			//	return bAdded;
			//}

			bool Add(TKey tag, const TVal& val)
			{
				FASSERT(mvKey.size() == m_maps.size());
				bool bAdded = false;
				const ulong uSize = m_maps.size();
				m_maps.insert(pair<TKey, TVal>(tag, val));
				if (uSize == m_maps.size() - 1)
				{
					mvKey.push_back(tag);
					bAdded = true;
				}
				FASSERT(m_maps.size() == mvKey.size());
				return bAdded;
			}

			//void Cutdown()
			//{
			//	if(GetSize() <= 0)
			//		return ;
			//	m_maps.pop_back();
			//}

			bool Remove(const TKey& tag, TVal& val)
			{
				//if(!ValidIndex(index))
				//	return ;
				MAPS::iterator it = m_maps.find(tag);
				if (it != m_maps.end())
				{
					val = (TVal)((*it).second);
					m_maps.erase(it);
					//
					std::vector<TKey>::iterator& begin = mvKey.begin();
					ulong index = 0;
					if (GetIndex(tag, index))
					{
						mvKey.erase(begin + index);
					}
					return true;
				}
				return false;
			}

			bool GetIndex(const TKey& key, ulong& index)
			{
				std::vector<TKey>::iterator it = mvKey.begin();
				for (ulong i = 0; i < mvKey.size() && it != mvKey.end(); it++, i++)
				{
					if (*it == key)
					{
						index = i;
						return true;
					}
				}
				return false;
			}

			void clear()
			{
				m_maps.clear();
				mvKey.clear();
			}

			bool setAtBegin(const TKey& key)
			{
				std::vector<TKey>::const_iterator it = std::find(mvKey.begin(), mvKey.end(), key);
				if (it == mvKey.end() || it == mvKey.begin())
					return false;
				ulong uKey = it - mvKey.begin();
				FASSERT(uKey >= 0 && uKey < mvKey.size());
				TKey val = mvKey[uKey];
				for (ulong i = uKey; i > 0; i--)
				{
					mvKey[i] = mvKey[i - 1];
				}
				mvKey[0] = val;
				return  true;
			}

			bool setAtEnd(const TKey& key)
			{
				std::vector<TKey>::const_iterator it = std::find(mvKey.begin(), mvKey.end(), key);
				if (it == mvKey.end() || it == mvKey.begin() + mvKey.size() - 1)
					return false;
				ulong uKey = it - mvKey.begin();
				FASSERT(uKey >= 0 && uKey < mvKey.size());
				TKey val = mvKey[uKey];
				for (ulong i = uKey; i < mvKey.size() - 1; i++)
				{
					mvKey[i] = mvKey[i + 1];
				}
				mvKey[mvKey.size() - 1] = val;
				return  true;
			}

			bool swap(const TKey& keyA, const TKey& keyB)
			{
				FASSERT(keyA != keyB);
				flong iA = -1, iB = -1;
				for (flong i = 0; i < mvKey.size() && (iA == -1 || iB == -1); i++)
				{
					if (keyA == mvKey[i] && iA == -1)
					{
						iA = i;
					}
					if (keyB == mvKey[i] && iB == -1)
					{
						iB = i;
					}
				}
				std::swap(mvKey[iA], mvKey[iB]);
				return true;
			}

			bool swap(ulong idxA, ulong idxB)
			{
				FASSERT(idxA != idxB && idxA >= 0 && idxA < GetSize() && idxB >= 0 && idxB < GetSize());
				std::swap(mvKey[idxA], mvKey[idxB]);
				return true;
			}

			bool sort(bool bAscend = true)
			{
				FASSERT(checkCanSort());
				std::sort(mvKey.begin(), mvKey.end());
				if (!bAscend)
					std::reverse(mvKey.begin(), mvKey.end());
				return true;
			}

			//template<class TValOther>
			bool sortAs(const std::vector<TKey>& vKey)
			{
				if (std::equal(mvKey.begin(), mvKey.end(), vKey.begin()))
					return true;
				//FASSERT(checkCanSortAs(vKey));
				//mvKey = vKey;
				setAtBegin(vKey[2]);
				setAtBegin(vKey[1]);
				setAtBegin(vKey[0]);
				return true;
			}

			bool checkCanSort() const
			{
				return (mvKey.size() == m_maps.size());
			}

			bool checkCanSortAs(const std::vector<TKey>& vKey) const
			{
				FASSERT(checkCanSort());
				FASSERT(mvKey.size() == vKey.size());
				std::vector<TKey> v1(mvKey), v2(vKey);
				std::sort(v1.begin(), v1.end());
				std::sort(v2.begin(), v2.end());
				return std::equal(v1.begin(), v1.end(), v2.begin());
			}

			//bool insert(const T& val,int index,bool fromBegin = true)
			//{
			//	if(!CanAdd(index))
			//		return false;
			//	if(fromBegin)
			//		m_vector.insert(m_vector.begin() + index,val);
			//	else
			//		m_vector.insert(m_vector.end() - index,val);
			//}

			bool Find(const TKey& tag, TVal& val)
			{
				MAPS::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return false;
				val = (TVal)((*it).second);
				return true;
			}

			bool Replace(const TKey& tag, const TVal& val)
			{
				//if(!ValidIndex(index))
				//	return false;
				MAPS::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return false;
				m_maps[tag] = val;
				return true;
			}

			const TVal& getValue(const TKey& tag, TVal& val) const
			{
				//if(!ValidIndex(index))
				//	return T();
				//return m_maps[TKey];
				// other way
				MAPS::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return val;
				val = (TVal)((*it).second);
				return val;
			}

			TVal& getValue(const TKey& tag, TVal& val)
			{
				//if(!ValidIndex(index))
				//	return T();
				//return m_maps[TKey];
				// other way
				MAPS::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return val;
				val = (TVal)((*it).second);
				return val;
			}

			TVal& getValueByIndex(TKey& tag, TVal& val, ulong uIndex)
			{
				FASSERT(uIndex >= 0 && uIndex < m_maps.size() && uIndex < mvKey.size());
				tag = mvKey[uIndex];
				FASSERT(m_maps.find(tag) != m_maps.end());
				//val = (TVal)((*it).second);
				val = m_maps[tag];
				return val;
			}

			//const TVal& getValueByIndex(TKey& tag,TVal& val,ulong uIndex) const
			//{
			//	FASSERT(uIndex >= 0 && uIndex < m_maps.size() && uIndex < mvKey.size());
			//	tag = mvKey[uIndex];
			//	FASSERT(m_maps.find(tag) != m_maps.end());
			//	//val = (TVal)((*it).second);
			//	val = m_maps[tag];
			//	return val;
			//}

			const std::vector<TKey>& getKeyVector() const
			{
				return mvKey;
			}

			TVal& operator [] (ulong uIndex);
			const TVal& operator [] (ulong uIndex) const;
			TVal& operator [] (const TKey& key);
			const TVal& operator [] (const TKey& key) const;
			TVal& operator () (ulong index);
			//const TVal& operator () (ulong index) const;
			TVal& element(ulong index);
			TVal& element(TKey& key, TVal& val, ulong index);
			//const TVal& element(ulong index) const;


			// For iterator
			void First()
			{
				m_iIndex = 0;
				//m_curIterator = m_maps.begin();
				//mIterator = m_maps.begin();
			}

			void Next()
			{
				if (m_iIndex < (int)m_maps.size() && m_iIndex < (int)mvKey.size())
				{
					m_iIndex++;
					//mIterator++;
				}
				else
				{
					//throw exception;
				}
				//if(m_curIterator != m_maps.end())
				//m_curIterator++;
			}

			bool IsEnd() const
			{
				return (m_iIndex >= (int)m_maps.size() || m_iIndex >= (int)mvKey.size());
				//return (m_curIterator == m_maps.end());
			}

			bool NullIterator()
			{
				return false;
			}

			const TVal& Value(TKey& tag, TVal& val) const
			{
				FCheck::Assert(m_iIndex >= 0 && m_iIndex < m_maps.size() && m_iIndex < mvKey.size());
				tag = mvKey[m_iIndex];
				const TKey tmTag(tag);
				val = getValue(tmTag, val);
				return val;
			}

			TVal& Value(TKey& tag, TVal& val)
			{
				FCheck::Assert(m_iIndex >= 0 && m_iIndex < m_maps.size() && m_iIndex < mvKey.size());
				tag = mvKey[m_iIndex];
				const TKey tmTag(tag);
				val = getValue(tmTag, val);
				return val;
			}

			//// Create iterator
			//void CreateIterator(TIteratorMapS<TKey,TVal>& it,EnumContainerIterator ecit)
			//{
			//	it = TIteratorMapS<TKey,TVal>(this);
			//}

			//TIteratorMapS<TKey,TVal>& CreateIterator(EnumContainerIterator ecit)
			//{
			//	return TIteratorMapS<TKey,TVal>(this);
			//}

		private:
			bool CanAdd(const TKey& tag)
			{
				return false;//(ValidKey(tag) && m_maps.size() < m_maps.max_size());
			}

			bool ValidKey(const TKey& tag)
			{
				MAPS::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return true;
				return false;
			}
		};

		template<class TKey, class TVal>
		TVal& TMaps<TKey, TVal>::operator [] (ulong uIndex)
		{
			assert(uIndex >= 0 && uIndex < m_maps.size());
			TKey tag;
			tag = mvKey[uIndex];
			return m_maps[tag];
		}

		template<class TKey, class TVal>
		const TVal& TMaps<TKey, TVal>::operator [] (ulong uIndex) const
		{
			assert(uIndex >= 0 && uIndex < m_maps.size());
			TKey tag;
			tag = mvKey[uIndex];
			return m_maps[tag];
		}

		template<class TKey, class TVal>
		TVal& TMaps<TKey, TVal>::operator [] (const TKey& key)
		{
			return m_maps[key];
		}

		template<class TKey, class TVal>
		const TVal& TMaps<TKey, TVal>::operator [] (const TKey& key) const
		{
			return m_maps[key];
		}

		template<class TKey, class TVal>
		TVal& TMaps<TKey, TVal>::operator () (ulong index)
		{
			assert(index >= 0 && index < m_maps.size());
			TKey tag;
			tag = mvKey[index];
			return m_maps[tag];
		}

		//template<class TKey,class TVal>
		//const TVal& TMaps<TKey,TVal>::operator () (ulong index) const
		//{
		//	assert(index >= 0 && index < m_maps.size());
		//	TKey tag = mvKey[index];
		//	return m_maps[tag];
		//}

		template<class TKey, class TVal>
		TVal& TMaps<TKey, TVal>::element(ulong index)
		{
			assert(index >= 0 && index < m_maps.size());
			TKey tag;
			tag = mvKey[index];
			return m_maps[tag];
		}

		template<class TKey, class TVal>
		TVal& TMaps<TKey, TVal>::element(TKey& key, TVal& val, ulong index)
		{
			assert(index >= 0 && index < m_maps.size() && mvKey.size() == m_maps.size());
			key = mvKey[index];
			val = m_maps[key];
			return m_maps[key];//val;
		}

		//template<class TKey,class TVal>
		//const TVal& TMaps<TKey,TVal>::element(ulong index) const
		//{
		//	assert(index >= 0 && index < m_maps.size());
		//	TKey tag = mvKey[index];
		//	return m_maps[tag];
		//}

		/*-----------------------------------------------------------
		class FIteratorMap
		------------------------------------------------------------*/
		template<class TVal>
		class TIteratorMap //: public TIIterator<TVal>
		{
		private:

		public:
			TIteratorMap()				{}
			virtual ~TIteratorMap()		{}
		};

		/*-----------------------------------------------------------
		class FIteratorMapS
		------------------------------------------------------------*/
		template <class TKey, class TVal>
		class TIteratorMapS : public TIteratorMap < TVal >
		{
		private:
			int m_iIndex;
			TMaps<TKey, TVal> m_maps;

		public:
			template <class TKey, class TVal>
			TIteratorMapS(TMaps<TKey, TVal> maps)
			{
				m_iIndex = 0;
				m_maps = maps;
			}
			virtual ~TIteratorMapS()
			{
				m_iIndex = 0;
			}
			virtual void First()
			{
				m_iIndex = 0;
			}
			virtual void Next()
			{
				m_iIndex++;
			}
			virtual bool IsEnd() const
			{
				return m_iIndex >= m_maps.GetSize();
			}

			template<class TKey, class TVal>
			bool NullIterator() const
			{
				return false;
			}

			template<class TKey, class TVal>
			const TVal& Value(TKey& tag, TVal& val) const
			{
				return TVal();
			}

			template<class TKey, class TVal>
			TVal& Value(TKey& tag, TVal& val)
			{
				return TVal();
			}

			virtual bool operator < (const TIteratorMapS& other)
			{
				return false;
			}

		};


		/*-----------------------------------------------------------
		class FMapM
		------------------------------------------------------------*/
		template <class TKey, class TVal>
		class TIteratorMapM;

		template <class TKey, class TVal>
		class FMapM //: public FMapBase,public TIIterator<TVal>
		{
		protected:
			typedef std::multimap<TKey, TVal> MAP_M;
			MAP_M m_maps;

		public:
			friend class IIterator;

			FMapM()
			{
				//Init();
				m_maps.clear();
			}

			virtual ~FMapM()
			{
				//UnInit();
				m_maps.clear();
			}

			template <class TKey, class TVal>
			FMapM(const FMapM<TKey, TVal>& other)
			{
				m_maps = other;
			}

			//template <class TKey,class TVal>
			void Init()
			{
				m_maps.clear();
			}

			//template <class TKey,class TVal>
			void UnInit()
			{
				m_maps.clear();
			}

			int GetSize() const
			{
				return (int)m_maps.size();
			}

			bool isEmpty() const
			{
				return (GetSize() <= 0);
			}

			template <class TKey, class TVal>
			void Add(const TKey& tag, const TVal& val)
			{
				//if(CanAdd(tag))
				if (m_maps.size() < m_maps.max_size())
				{
					//m_maps[tag] = val;
					m_maps.insert(pair<TKey, TVal>(tag, val));
				}
			}

			//template <class TKey,class TVal>
			//void Cutdown()
			//{
			//	if(GetSize() <= 0)
			//		return ;
			//	m_maps.pop_back();
			//}

			template <class TKey, class TVal>
			bool Remove(const TKey& tag, TVal& val, bool all = false)
			{
				//if(!ValidIndex(index))
				//	return ;
				MAP_M::iterator it = m_maps.find(tag);
				if (it != m_maps.end())
				{
					val = (TVal)((*it).second);
					m_maps.erase(it);
					if (all)
					{
						m_maps.erase(tag);
					}
					return true;
				}
				return false;
			}

			//template <class TKey,class TVal>
			void clear()
			{
				m_maps.clear();
			}

			//template <class TKey,class TVal>
			//bool insert(const T& val,int index,bool fromBegin = true)
			//{
			//	if(!CanAdd(index))
			//		return false;
			//	if(fromBegin)
			//		m_vector.insert(m_vector.begin() + index,val);
			//	else
			//		m_vector.insert(m_vector.end() - index,val);
			//}

			template <class TKey, class TVal>
			bool Find(const TKey& tag, TVal& val)
			{
				MAP_M::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return false;
				val = (TVal)((*it).second);
				return true;
			}

			template <class TKey, class TVal>
			bool Replace(const TKey& tag, const TVal& val)
			{
				//if(!ValidIndex(index))
				//	return false;
				MAP_M::iterator it = m_maps.find(tag);
				if (it == m_maps.end())
					return false;
				m_maps[tag] = val;
				return true;
			}

			template <class TKey, class TVal>
			const TVal& Value(const TKey& tag) const
			{
				//if(!ValidIndex(index))
				//	return T();
				//return m_maps[TKey];
				// other way
				MAP_M::iterator it = m_maps.find(tag);
				//if(it == MAP_S::end())
				//	return TVal();
				return (TVal)(it->second);
			}

			template <class TKey, class TVal>
			TVal& Value(const TKey& tag)
			{
				//if(!ValidIndex(index))
				//	return T();
				//return m_maps[TKey];
				// other way
				MAP_M::iterator it = m_maps.find(tag);
				//if(it == MAP_S::end())
				//	return TVal();
				return (TVal)(it->second);
			}

			// For iterator
			void First()
			{
				m_iIndex = 0;
			}

			void Next()
			{
				m_iIndex++;
				if (m_iIndex >= (int)m_maps.size())
					m_iIndex = m_maps.size();
			}

			bool IsEnd() const
			{
				return m_iIndex >= (int)m_maps.size();
			}

			bool NullIterator()
			{
				return false;
			}

			template <class TKey, class TVal>
			const TVal& Value(TKey& tag, TVal& val) const
			{
				MAP_M::iterator it = m_maps.begin();
				//for(int i = 0; it != m_maps.end() && i < m_iIndex; it++,i++)
				//	;
				// ?? I don't known if this way is correct?
				//it += m_iIndex;
				tag = (TKey)((*it).first);
				return (TVal)((*it).second);
			}

			template <class TKey, class TVal>
			TVal& Value(TKey& tag, TVal& val)
			{
				MAP_M::iterator it = m_maps.begin();
				//for(int i = 0; it != m_maps.end() && i < m_iIndex; it++,i++)
				//	;
				// ?? I don't known if this way is correct?
				//it += m_iIndex;
				tag = (TKey)((*it).first);
				return (TVal)((*it).second);
			}

			//// Create iterator
			//template<class TKey,class TVal>
			//void CreateIterator(TIteratorMapM<TKey,TVal>& it,EnumContainerIterator ecit)
			//{
			//	it = TIteratorMapM<TKey,TVal>(this);
			//}

			//template<class TKey,class TVal>
			//TIteratorMapM<TKey,TVal>& CreateIterator(EnumContainerIterator ecit)
			//{
			//	return TIteratorMapM<TKey,TVal>(this);
			//}

		private:
			template <class TKey, class TVal>
			bool CanAdd(const TKey& tag)
			{
				return false;//(ValidKey(tag) && m_maps.size() < m_maps.max_size());
			}

		};

		/*-----------------------------------------------------------
		class FIteratorMapM
		------------------------------------------------------------*/
		template <class TKey, class TVal>
		class TIteratorMapM : public TIteratorMap < TVal >
		{
		private:
			int m_iIndex;
			FMapM<TKey, TVal> m_maps;

		public:
			template <class TKey, class TVal>
			TIteratorMapM(FMapM<TKey, TVal> maps)
			{
				m_iIndex = 0;
				m_maps = maps;
			}
			virtual ~TIteratorMapM()
			{
				m_iIndex = 0;
			}
			virtual void First()
			{
				m_iIndex = 0;
			}
			virtual void Next()
			{
				m_iIndex++;
			}
			virtual bool IsEnd() const
			{
				return m_iIndex >= m_maps.GetSize();
			}

			template<class TKey, class TVal>
			bool NullIterator() const
			{
				return false;
			}

			template<class TKey, class TVal>
			const TVal& Value(TKey& tag, TVal& val) const
			{
				return TVal();
			}

			template<class TKey, class TVal>
			TVal& Value(TKey& tag, TVal& val)
			{
				return TVal();
			}

			virtual bool operator < (const TIteratorMapM& other)
			{
				return false;
			}

		};








	}
}