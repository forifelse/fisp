/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <list>
#include <algorithm>

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class TList
		------------------------------------------------------------*/
		template <class T>
		class TList : public IRoot
		{
		public:
			TList();
			virtual ~TList();

			void push(const T& val, bool bBack = true);
			T pop(bool bFront = true);
			void insert(ulong uIndex, const T& val, ulong uCount = 1);
			void remove(const T& val);
			ulong size() const;
			void begin();
			void next();
			bool isEnd() const;
			T& itVal();

			template<class TFinder>
			bool find(T &val, const TFinder& key);

		private:
			std::list<T>	mList;
			typename std::list<T>::iterator mit;
		};

		/*-----------------------------------------------------------
		class TList
		------------------------------------------------------------*/
		template<class T>
		TList<T>::TList()
		{
			mList.clear();
		}

		template<class T>
		TList<T>::~TList()
		{
			mList.clear();
		}

		template<class T>
		void TList<T>::push(const T& val, bool bBack /* = true */)
		{
			if (bBack)
				mList.push_back(val);
			else
				mList.push_front(val);
		}

		template<class T>
		T TList<T>::pop(bool bFront /* = true */)
		{
			T val;
			if (bFront)
			{
				val = *mList.begin();
				mList.pop_front();
			}
			else
			{
				val = *mList.end();
				mList.pop_back();
			}
			return val;
		}

		template<class T>
		void TList<T>::insert(ulong uIndex, const T& val, ulong uCount /* = 1 */)
		{
			if (!(uIndex >= 0 && uIndex < mList.size()))
				return;
			std::list<T>::iterator it = mList.begin();
			for (ulong i = 0; i < muIndex; i++)
				++it;
			mList.insert(it,uCount,val);
		}

		template<class T>
		void TList<T>::remove(const T& val)
		{
			mList.remove(val);
		}

		template<class T>
		ulong TList<T>::size() const
		{
			return mList.size();
		}

		template <class T>
		void TList<T>::begin()
		{
			mit = mList.begin();
		}

		template <class T>
		void TList<T>::next()
		{
			mit++;
		}

		template <class T>
		bool TList<T>::isEnd() const
		{
			bool bEnd = (mList.end() == mit);
			return bEnd;
		}

		template <class T>
		T& TList<T>::itVal()
		{
			assert(!isEnd());
			return *mit;
		}

		template<class T>
		template<class TFinder>
		bool TList<T>::find(T &val, const TFinder& finder)
		{
			bool bOk = false;
			std::list<T>::iterator it = std::find_if(mList.begin(), mList.end(), finder);
			if (it != mList.end())
			{
				val = *it;
				bOk = true;
			}
			return bOk;
		}

		//template<class T>
		//T& TList<T>::getAt(ulong uIndex)
		//{
		//	FASSERT(uIndex >= 0 && uIndex < mList.size());
		//	std::list<T>::iterator it = mList.begin();
		//	for (ulong i = 0; i < uIndex; i++)
		//	{
		//		it++;
		//	}
		//	return *it;
		//}

		//template<class T>
		//const T& TList<T>::getAt(ulong uIndex) const
		//{
		//	FASSERT(uIndex >= 0 && uIndex < mList.size());
		//	std::list<T>::const_iterator it = mList.begin();
		//	for (ulong i = 0; i < uIndex; i++)
		//	{
		//		it++;
		//	}
		//	return *it;
		//}

		/*-----------------------------------------------------------
		class TTree
		------------------------------------------------------------*/
		template <class T, int D = 2>
		class TTree : public IRoot
		{
		public:
			TTree();
			virtual ~TTree();
			TTree(T* pNode);
			TTree(const TTree<T, D>& other);
			TTree<T, D>& operator = (const TTree<T, D>& other);

			bool setChild(uint idx, T* pNode);
			TTree<T, D>* root();
			TTree<T, D>* parent();
			TTree<T, D>* child(uint idx);
			T* node();
			bool isRoot() const;

		protected:
			T*	mpNode;
			TTree<T, D>* mpParent;
			TTree<T, D>* mpChild[D];
		};

		/*-----------------------------------------------------------
		class TTree
		------------------------------------------------------------*/
		template <class T, int D = 2>
		TTree<T, D>::TTree<T, D>()
			: mpNode(nullptr)
			, mpParent(nullptr)
		{
			for (int i = 0; i < D; i++)
				mpChild[i] = nullptr;
		}

		template <class T, int D = 2>
		TTree<T, D>::~TTree<T, D>()
		{
			T::destroyMem<T>(mpNode);
			mpParent = nullptr;
			for (int i = 0; i < D; i++)
			{
				if (nullptr != mpChild[i])
					freeptr(mpChild[i]);
			}
		}

		template <class T, int D = 2>
		TTree<T, D>::TTree<T, D>(T* pNode)
			: mpNode(pNode)
			, mpParent(nullptr)
		{
			for (int i = 0; i < D; i++)
				mpChild[i] = nullptr;
		}

		template <class T, int D = 2>
		TTree<T, D>::TTree<T, D>(const TTree<T, D>& other)
			: mpNode(nullptr)
			, mpParent(nullptr)
		{
			freeptr(mpNode);
			if (nullptr != other.mpNode)
			{
				mpNode = new T;
				*mpNode = *other.mpNode;
			}
			mpParent = other.mpParent;
			for (int i = 0; i < D; i++)
				mpChild[i] = other.mpChild[i];
		}

		template <class T, int D = 2>
		TTree<T, D>& TTree<T, D>::operator = (const TTree<T, D>& other)
		{
			freeptr(mpNode);
			if (nullptr != other.mpNode)
			{
				mpNode = new T;
				*mpNode = *other.mpNode;
			}
			mpParent = other.mpParent;
			for (int i = 0; i < D; i++)
				mpChild[i] = other.mpChild[i];
			return *this;
		}

		template <class T, int D = 2>
		bool TTree<T, D>::setChild(uint idx, T* pNode)
		{
			if (idx < 0 || idx >= D)
				return false;
			TTree<T, D>* pChild = new TTree<T, D>(pNode);
			mpChild[idx] = pChild;
			return true;
		}

		template <class T, int D = 2>
		TTree<T, D>* TTree<T, D>::root()
		{
			TTree<T, D>* pNode = this;
			while (nullptr != pNode->parent())
			{
				pNode = pNode->parent();
			}
			return pNode;
		}

		template <class T, int D = 2>
		TTree<T, D>* TTree<T, D>::parent()
		{
			return mpParent;
		}

		template <class T, int D = 2>
		TTree<T, D>* TTree<T, D>::child(uint idx)
		{
			if (idx < 0 || idx >= D)
				return nullptr;
			return mpChild[idx];
		}

		template <class T, int D = 2>
		bool TTree<T, D>::isRoot() const
		{
			return (nullptr == mpParent);
		}

		template <class T, int D = 2>
		T* TTree<T, D>::node()
		{
			return mpNode;
		}








	}
}