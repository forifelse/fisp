/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "inUtility.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class TBuffer
		------------------------------------------------------------*/
		template<class T>
		class TBuffer //: public IRoot
		{
		public:
			TBuffer();
			virtual ~TBuffer();
			TBuffer(const TBuffer<T>& other);
			TBuffer<T>& operator = (const TBuffer<T>& other);
			bool create(ulong uSize, ulong uSplitPitch = 0);
			bool copyFrom(T* pData, ulong uSize, ulong uSplitPitch = 0);
			//bool copyFrom(TDArray<T>* pData);
			bool resize(ulong uNewSize);
			// set size to zero, but not delete buffer.
			void clear();
			bool referFrom(T* pData, ulong uSize);
			void zeroMemory();
			// overall copy.
			// @pData: start of source data.
			// @uSize: element/index count of array. NOT byte width
			// @uOffset: uOffset index of destination.
			bool copyMemory(T* pData, ulong uSize, ulong uOffset = 0);
			bool getMemory(T* pData, ulong uSize, ulong uOffset = 0) const;
			bool setAt(ulong uIndex, const T& val);
			bool getAt(ulong uIndex, T &val) const;
			T* getData();
			const T* getData() const;
			ulong getSize() const;
			// byte width of current used data.
			ulong getByteWidth() const;

			// for 2D access. [uRow][uCol]
			// @uPitch: size of per-group.
			// @uRow: group count.
			// @uCol: size of per-group.
			void split(ulong uPitch, ulong &uRow, ulong &uCol);
			void split(ulong uPitch);
			void setAt(ulong iRow, ulong jCol, const T& val);
			const T& getAt(ulong iRow, ulong jCol) const;
			uint splitPitch() const;
			bool create(void* pData = NULL){ return doCreate(pData); }
			bool release() { return doRelease(); }

		private:
			virtual bool doCreate(void* pData = NULL);
			virtual bool doRelease();
			void copyOther(const TBuffer<T>& other);

		private:
			T*		mpData;
			// size of current used.
			ulong	muSize;
			// memory size created by new operator.
			// muMemSize > 0 means create memory.
			// muMemSize = 0 means reference memory.
			ulong	muMemSize;
			// size of per-group after split. muCol <=0 means not split yet.
			ulong	muCol;
		};

		/*-----------------------------------------------------------
		class TBuffer
		------------------------------------------------------------*/
		template<class T>
		TBuffer<T>::TBuffer()
			: mpData(NULL)
			, muSize(0)
			, muMemSize(0)
			, muCol(0)
		{
		}

		template<class T>
		TBuffer<T>::~TBuffer()
		{
			release();
		}

		template<class T>
		TBuffer<T>::TBuffer(const TBuffer<T>& other)
			: mpData(NULL)
			, muSize(0)
			, muMemSize(0)
			, muCol(0)
		{
			copyOther(other);
		}

		template<class T>
		TBuffer<T>& TBuffer<T>::operator = (const TBuffer<T>& other)
		{
			copyOther(other);
			return *this;
		}

		template<class T>
		bool TBuffer<T>::doCreate(void* pData /* = NULL */)
		{
			mpData = NULL;
			muSize = 0;
			muMemSize = 0;
			muCol = 0;
			return true;
		}

		template<class T>
		bool TBuffer<T>::doRelease()
		{
			if (muMemSize <= 0)
			{
				mpData = NULL;
			}
			else
			{
				FREE_ARRAY(mpData);
			}
			muSize = 0;
			muMemSize = 0;
			muCol = 0;
			return true;
		}

		template<class T>
		void TBuffer<T>::copyOther(const TBuffer<T>& other)
		{
			//IRoot::operator = (other);
			mpData = NULL;
			if (other.muMemSize <= 0)
			{
				referFrom(other.mpData, other.muSize);
			}
			else
			{
				copyFrom(other.mpData, other.muSize);
			}
			muCol = other.muCol;
		}

		template<class T>
		bool TBuffer<T>::create(ulong uSize, ulong uSplitPitch /* = 0 */)
		{
			if(uSize <= 0)
				return false;
			//
			bool bRe = false;
			if (muMemSize > 0 && uSize <= muMemSize)
			{
				muSize = uSize;
				muCol = 0;
				bRe = true;
			}
			else
			{
				release();
				try
				{
					mpData = new T[uSize];
					muSize = uSize;
					muMemSize = uSize;
					bRe = true;
				}
				catch (...)
				{
					mpData = NULL;
					muSize = 0;
					muMemSize = 0;
					muCol = 0;
					return false;
				}
			}
			if (uSplitPitch > 0)
			{
				split(uSplitPitch);
			}
			zeroMemory();
			return bRe;
		}

		template<class T>
		bool TBuffer<T>::copyFrom(T* pData, ulong uSize, ulong uSplitPitch /* = 0 */)
		{
			if (NULL == pData || uSize <= 0)
				return false;
			create(uSize, (uSplitPitch > 0)? uSplitPitch : muCol);
			memcpy(mpData, pData, uSize * sizeof(T));
			return true;
		}

		//template<class T>
		//bool TBuffer<T>::copyFrom(TDArray<T>* pData)
		//{
		//	FASSERT(NULL != pData);
		//	ulong uRow = pData->getRow();
		//	ulong uCol = pData->getCol();
		//	FCHECK(uRow > 0 && uCol > 0,false);
		//	create(uRow * uCol,uCol);
		//	for(ulong i=0; i<uRow; i++)
		//	{
		//		for(ulong j=0; j<uCol; j++)
		//		{
		//			setAt(i,j,pData[i][j]);
		//		}
		//	}
		//	return true;
		//}

		template<class T>
		bool TBuffer<T>::resize(ulong uNewSize)
		{
			return create(uNewSize);
		}

		template<class T>
		void TBuffer<T>::clear()
		{
			muSize = 0;
		}

		template<class T>
		bool TBuffer<T>::referFrom(T* pData, ulong uSize)
		{
			FASSERT(NULL != pData && uSize > 0);
			release();
			mpData = pData;
			muSize = uSize;
			muMemSize = 0;
			return true;
		}

		template<class T>
		void TBuffer<T>::zeroMemory()
		{
			if (NULL != mpData && muSize > 0)
			{
				memset(mpData, 0, muSize * sizeof(T));
			}
		}

		template<class T>
		bool TBuffer<T>::copyMemory(T* pData, ulong uSize, ulong uOffset /* = 0 */)
		{
			FCHECK(NULL != mpData && NULL != pData && uSize > 0 && uOffset + uSize <= muSize, false);
			memcpy(mpData + uOffset, pData, uSize * sizeof(T));
			return true;
		}

		template<class T>
		bool TBuffer<T>::getMemory(T* pData, ulong uSize, ulong uOffset /* = 0 */) const
		{
			FCHECK(NULL != mpData && NULL != pData && uSize > 0 && uOffset + uSize <= muSize, false);
			memcpy(pData, mpData + uOffset, uSize * sizeof(T));
			return true;
		}

		template<class T>
		bool TBuffer<T>::setAt(ulong uIndex, const T& val)
		{
			FCHECK(NULL != mpData && uIndex >= 0 && uIndex < muSize, false);
			mpData[uIndex] = val;
			return true;
		}

		template<class T>
		bool TBuffer<T>::getAt(ulong uIndex, T &val) const
		{
			FCHECK(NULL != mpData && uIndex >= 0 && uIndex < muSize, false);
			val = mpData[uIndex];
			return true;
		}

		template<class T>
		T* TBuffer<T>::getData()
		{
			return mpData;
		}

		template<class T>
		const T* TBuffer<T>::getData() const
		{
			return mpData;
		}

		template<class T>
		ulong TBuffer<T>::getSize() const
		{
			return muSize;
		}

		template<class T>
		ulong TBuffer<T>::getByteWidth() const
		{
			return muSize * sizeof(T);
		}

		template<class T>
		void TBuffer<T>::split(ulong uPitch, ulong &uRow, ulong &uCol)
		{
			uRow = 0;
			uCol = 0;
			if (NULL != mpData && muSize > 0 && uPitch > 0)
			{
				if (muSize <= uPitch)
				{
					uRow = 1;
					uCol = muSize;
				}
				else
				{
					uRow = muSize / uPitch;
					uCol = uPitch;
				}
			}
			muCol = uCol;
		}

		template<class T>
		void TBuffer<T>::split(ulong uPitch)
		{
			ulong uRow, uCol;
			split(uPitch, uRow, uCol);
		}

		template<class T>
		void TBuffer<T>::setAt(ulong iRow, ulong jCol, const T& val)
		{
			FASSERT(NULL != mpData && muCol > 0 && iRow * muCol + jCol < muSize);
			mpData[iRow * muCol + jCol] = val;
		}

		template<class T>
		const T& TBuffer<T>::getAt(ulong iRow, ulong jCol) const
		{
			FASSERT(NULL != mpData && muCol > 0 && iRow * muCol + jCol < muSize);
			return mpData[iRow * muCol + jCol];
		}

		template<class T>
		uint TBuffer<T>::splitPitch() const
		{
			return muCol;
		}

		/*-----------------------------------------------------------
		class BufferByte
		------------------------------------------------------------*/
		class BufferByte : public TBuffer < byte >
		{
		};

		/*-----------------------------------------------------------
		class BufferWord
		------------------------------------------------------------*/
		class BufferWord : public TBuffer < word >
		{
		};

		/*-----------------------------------------------------------
		class BufferDWord
		------------------------------------------------------------*/
		class BufferDWord : public TBuffer < dword >
		{
		};

		/*-----------------------------------------------------------
		class BufferFloat
		------------------------------------------------------------*/
		class BufferFloat : public TBuffer < float >
		{
		};

			














	}
}