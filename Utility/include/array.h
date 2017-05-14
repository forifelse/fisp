/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <vector>
#include "buffer.h"
using namespace std;

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class TArray
		------------------------------------------------------------*/
		template<class TVal>
		class TArray : public IRoot
		{
		public:
			TArray();
			virtual ~TArray();
			TArray(ulong uSize);
			TArray(ulong uSize, const TVal& initVal);
			TArray(const TArray<TVal>& other);
			bool operator == (const TArray<TVal>& other) const;
			TArray<TVal>& operator = (const TArray<TVal>& other);
			TArray<TVal> operator + (const TArray<TVal>& other) const;
			TArray<TVal>& operator += (const TArray<TVal>& other);
			TVal& operator [] (ulong uIndex);
			const TVal& operator [] (ulong uIndex) const;
			void add(const TArray<TVal>& other);
			void add(const TVal& val);
			void addNotRepeat(const TArray<TVal>& other);
			void addNotRepeat(const TVal& val);
			void reset(const TVal& initVal);
			void pop();
			void remove(const TArray<TVal>& other, bool bAll = true);
			void remove(const TVal& val, bool bAll = true);
			void remove(ulong uIndex);
			void clear();
			void sort();
			//bool find(const TVal& val,flong uCnt = -1,ulong uFrom = 0) const;
			//bool find(const TVal& val,ulong &uIndex,flong uCnt = -1,ulong uFrom = 0) const;
			bool find(const TVal& val) const;
			bool find(const TVal& val, ulong uFrom, ulong uCnt) const;
			bool find(const TVal& val, ulong &uIndex) const;
			bool find(const TVal& val, ulong &uIndex, ulong uFrom, ulong uCnt) const;
			void setAt(ulong index, const TVal& val);
			TVal& getAt(ulong index);
			const TVal& getAt(ulong index) const;
			const TArray<TVal>& subArray(TArray<TVal>& subArray, ulong index, ulong uCount) const;
			bool replace(const TVal& value, int index, bool fromBegin = true);
			bool setCapacity(ulong uSize);
			TVal* getBufferPointor(TVal* &pVal, ulong &uNumber, bool bDerivedFromIBase = true) const;
			ulong getBufferSize() const;
			bool fromBufferPointor(const TVal* &pVal, ulong uNumber, bool bResize = true);
			// only for basic type. e.g. int,word/dword,float.
			TBuffer<TVal>* getBuffer() const;
			bool isEmpty() const;
			ulong size() const;
			void resize(ulong uSize);
			void reserve(uint uReserved);
			void shuffle();

		private:
			static std::vector<TVal> detach(std::vector<TVal> src, std::vector<TVal> sub);

		private:
			void copyOther(const TArray<TVal>& other);

		private:
			std::vector<TVal>	mVector;

		};

		typedef	TArray<unsigned int> TArrayBool;

		/*-----------------------------------------------------------
		class TArray
		------------------------------------------------------------*/
		template<class TVal>
		TArray<TVal>::TArray()
		{
		}

		template<class TVal>
		TArray<TVal>::~TArray()
		{
			mVector.clear();
		}

		template<class TVal>
		TArray<TVal>::TArray(ulong uSize)
			:mVector(uSize)
		{
		}

		template<class TVal>
		TArray<TVal>::TArray(ulong uSize, const TVal& initVal)
			:mVector(uSize, initVal)
		{
		}

		template<class TVal>
		TArray<TVal>::TArray(const TArray<TVal>& other)
		{
			copyOther(other);
		}

		template<class TVal>
		bool TArray<TVal>::operator == (const TArray<TVal>& other) const
		{
			bool bRe = (other.mVector == mVector);
			return bRe;
		}

		template<class TVal>
		TArray<TVal>& TArray<TVal>::operator = (const TArray<TVal>& other)
		{
			copyOther(other);
			return *this;
		}

		template<class TVal>
		TArray<TVal> TArray<TVal>::operator + (const TArray<TVal>& other) const
		{
			TArray<TVal> reArray(*this);
			reArray.add(other);
			return reArray;
		}

		template<class TVal>
		TArray<TVal>& TArray<TVal>::operator += (const TArray<TVal>& other)
		{
			add(other);
			return *this;
		}

		template<class TVal>
		TVal& TArray<TVal>::operator [] (ulong uIndex)
		{
			FASSERT(uIndex >= 0 && uIndex < mVector.size());
			return mVector[uIndex];
		}

		template<class TVal>
		const TVal& TArray<TVal>::operator [] (ulong uIndex) const
		{
			FASSERT(uIndex >= 0 && uIndex < mVector.size());
			return mVector[uIndex];
		}

		template<class TVal>
		void TArray<TVal>::copyOther(const TArray<TVal>& other)
		{
			//IRoot::operator = (other);
			mVector = other.mVector;
		}

		template<class TVal>
		void TArray<TVal>::add(const TArray<TVal>& other)
		{
			ulong uSize = other.size();
			if (uSize <= 0)
				return;
			for (ulong i = 0; i < uSize; i++)
			{
				mVector.push_back(other.getAt(i));
			}
		}

		template<class TVal>
		void TArray<TVal>::add(const TVal& val)
		{
			mVector.push_back(val);
		}

		template<class TVal>
		void TArray<TVal>::addNotRepeat(const TArray<TVal>& other)
		{
			ulong uSize = other.size();
			if (uSize <= 0)
				return;
			for (ulong i = 0; i < uSize; i++)
			{
				addNotRepeat(other.getAt(i));
			}
		}

		template<class TVal>
		void TArray<TVal>::addNotRepeat(const TVal& val)
		{
			std::vector<TVal>::iterator it;
			it = std::find(mVector.begin(), mVector.end(), val);
			if (it == mVector.end())
				mVector.push_back(val);
		}

		template<class TVal>
		void TArray<TVal>::reset(const TVal& initVal)
		{
			//memset(mVector.data(), initVal, sizeof(TVal) * mVector.size());
			for (size_t i = 0; i < mVector.size(); i++)
				mVector[i] = initVal;
		}

		template<class TVal>
		void TArray<TVal>::pop()
		{
			mVector.pop_back();
		}

		template<class TVal>
		void TArray<TVal>::remove(const TArray<TVal>& other, bool bAll /* = true */)
		{
			ulong uSize = other.size();
			if (uSize <= 0)
				return;
			for (ulong i = 0; i < uSize; i++)
			{
				remove(other.getAt(i), bAll);
			}
		}

		template<class TVal>
		void TArray<TVal>::remove(const TVal& val, bool bAll /* = true */)
		{
			if (mVector.size() <= 0)
				return;
			std::vector<TVal>::iterator it = std::find(mVector.begin(), mVector.end(), val);
			while (it != mVector.end())
			{
				mVector.erase(it);
				if (!bAll)
					break;
				it = std::find(mVector.begin(), mVector.end(), val);
			}
		}

		template<class TVal>
		void TArray<TVal>::remove(ulong uIndex)
		{
			if (mVector.size() <= 0 || uIndex >= mVector.size())
				return;
			std::vector<TVal>::iterator it = mVector.begin() + uIndex;
			mVector.erase(it);
		}

		template<class TVal>
		void TArray<TVal>::clear()
		{
			mVector.clear();
		}

		template<class TVal>
		void TArray<TVal>::sort()
		{
			std::sort(mVector.begin(), mVector.end());
		}

		//template<class TVal>
		//bool TArray<TVal>::find(const TVal& val,flong uCnt /* = -1 */,ulong uFrom /* = 0 */) const
		//{
		//	//return (std::find(mVector.begin(),mVector.end(),val) != mVector.end());

		//	ulong uIndex = 0;
		//	return find(val,uIndex,uCnt,uFrom);
		//}

		//template<class TVal>
		//bool TArray<TVal>::find(const TVal& val,ulong &uIndex,flong uCnt /* = -1 */,ulong uFrom /* = 0 */) const
		//{
		//	//std::vector<TVal>::const_iterator it = std::find(mVector.begin(),mVector.end(),val);
		//	//if(it == mVector.end())
		//	//	return false;
		//	//uIndex = it - mVector.begin();
		//	//return true;

		//	//FCHECK(mVector.size() > 0 && uFrom >= 0 && uFrom < mVector.size(),false);
		//	const ulong uSize = (uCnt < 0 || uFrom + uCnt > mVector.size())? mVector.size() : (uFrom + uCnt);
		//	for(ulong i=uFrom; i<uSize; i++)
		//	{
		//		if(val == mVector[i])
		//		{
		//			uIndex = i;
		//			return true;
		//		}
		//	}
		//	return false;
		//}

		template<class TVal>
		bool TArray<TVal>::find(const TVal& val) const
		{
			return (std::find(mVector.begin(), mVector.end(), val) != mVector.end());
		}

		template<class TVal>
		bool TArray<TVal>::find(const TVal& val, ulong uFrom, ulong uCnt) const
		{
			FASSERT(uFrom >= 0 && uCnt > 0 && uFrom + uCnt <= mVector.size());
			std::vector<TVal>::const_iterator itTo = (uFrom + uCnt <= mVector.size()) ? (mVector.begin() + uFrom + uCnt) : (mVector.end());
			std::vector<TVal>::const_iterator it = std::find(mVector.begin() + uFrom, itTo, val);
			return !(it == mVector.end() || it >= itTo);
		}

		template<class TVal>
		bool TArray<TVal>::find(const TVal& val, ulong &uIndex) const
		{
			std::vector<TVal>::const_iterator it = std::find(mVector.begin(), mVector.end(), val);
			if (it == mVector.end())
				return false;
			uIndex = it - mVector.begin();
			return true;
		}

		template<class TVal>
		bool TArray<TVal>::find(const TVal& val, ulong &uIndex, ulong uFrom, ulong uCnt) const
		{
			FASSERT(uFrom >= 0 && uCnt > 0 && uFrom + uCnt <= mVector.size());
			std::vector<TVal>::const_iterator itTo = (uFrom + uCnt <= mVector.size()) ? (mVector.begin() + uFrom + uCnt) : (mVector.end());
			std::vector<TVal>::const_iterator it = std::find(mVector.begin() + uFrom, itTo, val);
			if (it == mVector.end() || it >= itTo)
				return false;
			uIndex = it - mVector.begin();
			return true;
		}

		template<class TVal>
		void TArray<TVal>::setAt(ulong uIndex, const TVal& val)
		{
			FASSERT(uIndex >= 0 && uIndex < mVector.size());
			mVector[uIndex] = val;
		}

		template<class TVal>
		TVal& TArray<TVal>::getAt(ulong uIndex)
		{
			FASSERT(uIndex >= 0 && uIndex < mVector.size());
			return mVector[uIndex];
		}

		template<class TVal>
		const TVal& TArray<TVal>::getAt(ulong uIndex) const
		{
			FASSERT(uIndex >= 0 && uIndex < mVector.size());
			return mVector[uIndex];
		}

		template<class TVal>
		const TArray<TVal>& TArray<TVal>::subArray(TArray<TVal>& subArray, ulong index, ulong uCount) const
		{
			subArray.clear();
			if(!ConstValue::IsBetween(index,size()) || uCount <= 0 || index + uCount > size())
				return subArray;
			for (ulong i = index; i<index + uCount; i++)
			{
				subArray.add(mVector[i]);
			}
			return subArray;
		}

		template <class TVal>
		bool TArray<TVal>::replace(const TVal& value, int index, bool fromBegin /* = true */)
		{
			if(!ValidIndex(index))
				return false;
			if (fromBegin)
			{
				mVector[index] = value;
			}
			else
			{
				mVector[size() - 1 - index] = value;
			}
			return true;
		}

		template<class TVal>
		bool TArray<TVal>::setCapacity(ulong uSize)
		{
			if (uSize <= 0 || uSize > mVector.max_size())
				return false;
			mVector.clear();
			mVector = std::vector<TVal>(uSize);
			return true;
		}

		template<class TVal>
		TVal* TArray<TVal>::getBufferPointor(TVal* &pVal, ulong &uNumber, bool bDerivedFromIBase /* = true */) const
		{
#if (bDerivedFromIBase)
			FREE_PTR(pVal);
#else
			FREE_BASEPTR(pVal);
#endif
			uNumber = 0;
			FCHECK(mVector.size() > 0, pVal);
			uNumber = mVector.size();
			//#if (bDerivedFromIBase)
			pVal = new TVal[uNumber];
			TVal* pTemp = pVal;
			for (ulong i = 0; i < mVector.size(); i++)
			{
				*pTemp = mVector[i];
				pTemp++;
			}
			pTemp = NULL;
			return pVal;
		}

		template<class TVal>
		ulong TArray<TVal>::getBufferSize() const
		{
			return  mVector.size() * sizeof(TVal);
		}

		template<class TVal>
		bool TArray<TVal>::fromBufferPointor(const TVal* &pVal, ulong uNumber, bool bResize /* = true */)
		{
			FCHECK(pVal != NULL && uNumber > 0, false);
			if (bResize)
				mVector.resize(uNumber);
			else if (mVector.size() < uNumber)
				return false;
			const TVal* pTemp = pVal;
			for (ulong i = 0; i < uNumber; i++)
			{
				mVector[i] = *pTemp;
				pTemp++;
			}
			pTemp = NULL;
			return true;
		}

		template<class TVal>
		TBuffer<TVal>* TArray<TVal>::getBuffer() const
		{
			FCHECK(mVector.size() > 0, NULL);
			TBuffer<TVal>* pData = new TBuffer < TVal > ;
			pData->create(mVector.size());
			for (ulong i = 0; i < mVector.size(); i++)
			{
				pData->setAt(i, mVector[i]);
			}
			return pData;
		}

		template<class TVal>
		bool TArray<TVal>::isEmpty() const
		{
			return mVector.size() <= 0;
		}

		template<class TVal>
		ulong TArray<TVal>::size() const
		{
			return (ulong)mVector.size();
		}

		template<class TVal>
		void TArray<TVal>::resize(ulong uSize)
		{
			mVector.resize(uSize);
		}

		template<class TVal>
		void TArray<TVal>::reserve(uint uReserved)
		{
			mVector.reserve(uReserved);
		}

		template<class TVal>
		void TArray<TVal>::shuffle()
		{
			//const uint uCnt = mVector.size();
			//uint uLast = uCnt - 1;
			//for(uint i=0; i<uCnt; i++)
			//{
			//	srand((uint)time(NULL));
			//	uint uIndex = rand() % (uLast + 1);
			//	if(uIndex != uLast)
			//	{
			//		uint uTemp = mVector[uLast];
			//		mVector[uLast] = mVector[uIndex];
			//		mVector[uIndex] = uTemp;
			//	}
			//	uLast --;
			//}

			// std
			std::random_shuffle(mVector.begin(), mVector.end());
		}

		template<class TVal>
		std::vector<TVal> TArray<TVal>::detach(std::vector<TVal> src, std::vector<TVal> sub)
		{
			std::vector<TVal> v(src);
			for (ulong i = 0; i < sub.size(); i++)
			{
				v = remove(v.begin(), v.end(), sub[i]);
			}
			return v;
		}

		//template<class TVal>
		//EnumClassType TArray<TVal>::getClassType(FString* pStrClassName /* = NULL */) const
		//{
		//	if(NULL != pStrClassName)
		//		*pStrClassName = "TArray";
		//	return Class_TArray + TVal::sGetClassType();
		//}

		/*-----------------------------------------------------------
		class TDArray
		------------------------------------------------------------*/
		template<class TVal>
		class TDArray : public IRoot
		{
		public:
			TDArray();
			virtual ~TDArray();
			TDArray(ulong uRow, ulong uCol);
			TDArray(ulong uRow, ulong uCol, const TVal& initVal);
			TDArray(const TDArray& other);
			bool operator == (const TDArray<TVal>& other) const;
			TDArray<TVal>& operator = (const TDArray<TVal>& other);
			void add(const TArray<TVal>& vNewRow);
			void add(const TDArray<TVal>& other);
			void clear();
			void sort();
			void setAt(ulong uRow, ulong uCol, const TVal& val);
			TVal& getAt(ulong uRow, ulong uCol);
			const TVal& getAt(ulong uRow, ulong uCol) const;
			void grow(ulong uNewRowSize, ulong uNewColSize);
			void growRow(ulong uNewSize);
			void growCol(ulong uNewSize);
			void reset(const TVal& initVal);
			TArray<TVal>& operator[](ulong uIndex);
			const TArray<TVal>& operator[](ulong uIndex) const;
			TArray< TArray<TVal> >& getBaseVector();
			const TArray< TArray<TVal> >& getBaseVector() const;
			ulong getRow() const;
			ulong getCol() const;
			const TVal* getBufferPointer(TVal* &pBufferPointer, ulong &uSize) const;
			bool fromBufferPointer(TVal* pBufferPointer, ulong uRow, ulong uCol);
			static bool sGetBufferPointor(TVal* &pData, ulong &uSize, const TArray<TVal>& vVal);
			// only for basic type. e.g. int,word/dword,float.
			TBuffer<TVal>* getBuffer() const;
			size_t size() const;

		private:
			void copyOther(const TDArray<TVal>& other);

		private:
			TArray< TArray <TVal> > mv2DVector;
			ulong muDimRow;
			ulong muDimCol;

		};

		/*-----------------------------------------------------------
		class TDArray
		------------------------------------------------------------*/
		template<class TVal>
		TDArray<TVal>::TDArray()
			:muDimRow(0)
			, muDimCol(0)
		{
		}

		template<class TVal>
		TDArray<TVal>::~TDArray()
		{
			clear();
		}

		template<class TVal>
		TDArray<TVal>::TDArray(ulong uRow, ulong uCol)
			: muDimRow(uRow)
			, muDimCol(uCol)
		{
			FASSERT(uRow > 0 && uCol > 0);
			mv2DVector.resize(uRow);
			for (ulong i = 0; i < uRow; i++)
			{
				TArray<TVal> x(uCol);
				mv2DVector.setAt(i, x);
			}
		}

		template<class TVal>
		TDArray<TVal>::TDArray(ulong uRow, ulong uCol, const TVal& initVal)
			: muDimRow(uRow)
			, muDimCol(uCol)
		{
			FASSERT(uRow > 0 && uCol > 0);
			mv2DVector.resize(uRow);
			for (ulong i = 0; i < uRow; i++)
			{
				TArray<TVal> x(uCol, initVal);
				mv2DVector.setAt(i, x);
			}
		}

		template<class TVal>
		TDArray<TVal>::TDArray(const TDArray<TVal>& other)
			: muDimRow(0)
			, muDimCol(0)
		{
			copyOther(other);
		}

		template<class TVal>
		bool TDArray<TVal>::operator == (const TDArray<TVal>& other) const
		{
			bool bRe = (mv2DVector == other.mv2DVector && muDimRow == other.muDimRow && muDimCol == other.muDimCol);
			return bRe;
		}

		template<class TVal>
		TDArray<TVal>& TDArray<TVal>::operator = (const TDArray<TVal>& other)
		{
			copyOther(other);
			return *this;
		}

		template<class TVal>
		void TDArray<TVal>::copyOther(const TDArray<TVal>& other)
		{
			IRoot::operator = (other);
			grow(other.getRow(), other.getCol());
			mv2DVector = other.mv2DVector;
		}

		template<class TVal>
		void TDArray<TVal>::add(const TArray<TVal>& vNewRow)
		{
			mv2DVector.add(vNewRow);
			muDimRow++;
		}

		template<class TVal>
		void TDArray<TVal>::add(const TDArray<TVal>& other)
		{
			FASSERT(getRow() == 0 || other.getCol() == getCol());
			for (ulong i = 0; i < other.getRow(); i++)
			{
				mv2DVector.add(other[i]);
				muDimRow++;
			}
			if (muDimCol == 0)
				muDimCol = other.getCol();
			FASSERT(other.getCol() == muDimCol);
		}

		template<class TVal>
		void TDArray<TVal>::clear()
		{
			for (ulong i = 0; i < getRow(); i++)
			{
				mv2DVector[i].clear();
			}
			mv2DVector.clear();
			muDimRow = 0;
			muDimCol = 0;
		}

		template<class TVal>
		void TDArray<TVal>::sort()
		{
			for (ulong i = 0; i < getRow(); i++)
			{
				mv2DVector[i].sort();
			}
			mv2DVector.sort();
		}

		template<class TVal>
		void TDArray<TVal>::setAt(ulong uRow, ulong uCol, const TVal& val)
		{
			FASSERT(uRow < muDimRow && uCol < muDimCol);
			if (uRow >= muDimRow || uCol >= muDimCol)
				throw out_of_range("Array out of bound");
			else
				mv2DVector[uRow][uCol] = val;
		}

		template<class TVal>
		TVal& TDArray<TVal>::getAt(ulong uRow, ulong uCol)
		{
			FASSERT(uRow < muDimRow && uCol < muDimCol);
			if (uRow >= muDimRow || uCol >= muDimCol)
				throw out_of_range("Array out of bound");
			return mv2DVector[uRow][uCol];
		}

		template<class TVal>
		const TVal& TDArray<TVal>::getAt(ulong uRow, ulong uCol) const
		{
			FASSERT(uRow < muDimRow && uCol < muDimCol);
			if (uRow >= muDimRow || uCol >= muDimCol)
				throw out_of_range("Array out of bound");
			return mv2DVector[uRow][uCol];
		}

		template<class TVal>
		void TDArray<TVal>::grow(ulong uNewRowSize, ulong uNewColSize)
		{
			if ((uNewRowSize == muDimRow) && (uNewColSize == muDimCol))
			{
				return;
			}
			if (uNewRowSize > muDimRow)
			{
				try
				{
					mv2DVector.resize(uNewRowSize);
				}
				catch (const std::bad_alloc& e)
				{
					FASSERT(!"Failed to create memory!");
				}

				for (ulong i = 0; i < uNewRowSize; i++)
				{
					try
					{
						mv2DVector[i].resize(uNewColSize);
					}
					catch (const std::bad_alloc& e)
					{
						FASSERT(!"Failed to create memory!");
					}
				}
				muDimRow = uNewRowSize;
				muDimCol = uNewColSize;
			}
			else
			{
				growRow(uNewRowSize);
				growCol(uNewColSize);
			}
		}

		template<class TVal>
		void TDArray<TVal>::growRow(ulong uNewSize)
		{
			ulong delta = uNewSize - muDimRow;
			if (delta == 0)
			{
				return;
			}
			else if (delta < 0)
			{
				for (ulong i = 0; i < 0 - delta; i++)
				{
					mv2DVector.pop();
				}
			}
			else //if(delta > 0)
			{
				try
				{
					mv2DVector.resize(uNewSize);
				}
				catch (const std::bad_alloc& e)
				{
					FASSERT(!"Failed to create memory!");
				}

				for (ulong i = 0; i < uNewSize; i++)
				{
					try
					{
						mv2DVector[i].resize(muDimCol);
					}
					catch (const std::bad_alloc& e)
					{
						FASSERT(!"Failed to create memory!");
					}
				}
			}
			//
			muDimRow = uNewSize;
		}

		template<class TVal>
		void TDArray<TVal>::growCol(ulong uNewSize)
		{
			if (uNewSize - muDimCol == 0)
			{
				return;
			}
			muDimCol = uNewSize;
			for (ulong i = 0; i < muDimRow; i++)
			{
				try
				{
					mv2DVector[i].resize(muDimCol);
				}
				catch (const std::bad_alloc& e)
				{
					FASSERT(!"Failed to create memory!");
				}
			}
		}

		template<class TVal>
		void TDArray<TVal>::reset(const TVal& initVal)
		{
			for (ulong i = 0; i < muDimRow; i++)
			{
				for (size_t j = 0; j < muDimCol; j++)
				{
					mv2DVector[i][j] = initVal;
				}
			}
		}

		template<class TVal>
		TArray<TVal>& TDArray<TVal>::operator[](ulong uIndex)
		{
			FASSERT(uIndex >= 0 && uIndex < mv2DVector.size());
			return mv2DVector[uIndex];
		}

		template<class TVal>
		const TArray<TVal>& TDArray<TVal>::operator[](ulong uIndex) const
		{
			FASSERT(uIndex >= 0 && uIndex < mv2DVector.size());
			return mv2DVector[uIndex];
		}

		template<class TVal>
		TArray< TArray<TVal> >& TDArray<TVal>::getBaseVector()
		{
			return mv2DVector;
		}

		template<class TVal>
		const TArray< TArray<TVal> >& TDArray<TVal>::getBaseVector() const
		{
			return mv2DVector;
		}

		template<class TVal>
		ulong TDArray<TVal>::getRow() const
		{
			return muDimRow;
		}

		template<class TVal>
		ulong TDArray<TVal>::getCol() const
		{
			return muDimCol;
		}

		template<class TVal>
		const TVal* TDArray<TVal>::getBufferPointer(TVal* &pBufferPointer, ulong &uSize) const
		{
			FREE_BASEPTR(pBufferPointer);
			uSize = getRow() * getCol();
			FCHECK(uSize > 0, NULL);
			pBufferPointer = new TVal[uSize];
			TVal* pTemp = pBufferPointer;
			for (ulong i = 0; i < getRow(); i++)
			{
				for (ulong j = 0; j < getCol(); j++)
				{
					*pTemp = mv2DVector[i][j];
					pTemp++;
				}
			}
			pTemp = NULL;
			return pBufferPointer;
		}

		template<class TVal>
		bool TDArray<TVal>::fromBufferPointer(TVal* pBufferPointer, ulong uRow, ulong uCol)
		{
			FCHECK(pBufferPointer != NULL && uRow > 0 && uCol > 0, false);

			grow(uRow, uCol);
			TVal* pTemp = pBufferPointer;
			for (ulong i = 0; i < getRow(); i++)
			{
				for (ulong j = 0; j < getCol(); j++)
				{
					mv2DVector[i][j] = *pTemp;
					pTemp++;
				}
			}
			pTemp = NULL;
			return true;
		}

		template<class TVal>
		bool TDArray<TVal>::sGetBufferPointor(TVal* &pData, ulong &uSize, const TArray<TVal>& vVal)
		{
			FREE_BASEPTR(pData);
			uSize = 0;
			FCHECK(vVal.size() > 0, false);
			uSize = vVal.size();
			pData = new TVal[uSize];
			TVal* pTemp = pData;
			for (ulong i = 0; i < uSize; i++)
			{
				*pTemp = vVal[i];
				pTemp++;
			}
			pTemp = NULL;
			return true;
		}

		template<class TVal>
		TBuffer<TVal>* TDArray<TVal>::getBuffer() const
		{
			FCHECK(muDimRow > 0 && muDimCol > 0, NULL);
			TBuffer<TVal>* pData = new TBuffer < TVal > ;
			pData->create(muDimRow * muDimCol, muDimCol);
			for (ulong i = 0; i < muDimRow; i++)
			{
				for (ulong j = 0; j < muDimCol; j++)
				{
					pData->setAt(i, j, mv2DVector[i][j]);
				}
			}
			return pData;
		}

		template<class TVal>
		size_t TDArray<TVal>::size() const
		{
			size_t cnt = 0;
			for (size_t i = 0; i < muDimRow; i++)
			{
				cnt += mv2DVector[i].size();
			}
			return cnt;
		}






	}
}