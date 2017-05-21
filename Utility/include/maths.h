/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <directxmath.h>
#include <directxcolors.h>
using namespace DirectX;
#include "base.h"
#include "maths2d.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		enum EAlongWith
		------------------------------------------------------------*/
		enum EAlongWith
		{
			AlongWith_X,
			AlongWith_Y,
			AlongWith_Z,
			AlongWith_Max
		};

		/*-----------------------------------------------------------
		class Color
		------------------------------------------------------------*/
		class Color : public IRoot
		{
		private:
			dword	mdwColor;	// 0xaarrggbb

		public:
			Color();
			virtual ~Color();
			// For float color value between 0.0 - 1.0
			Color(float r, float g, float b, float a);
			// For uint color value between 0 - 255
			Color(uint R, uint G, uint B, uint A);
			// byte color
			Color(byte R, byte G, byte B, byte A);
			// For U V H
			//Color(float h,float u,float v,float a);
			Color(dword dwColor);
			Color(const Color& other);

			bool operator < (const Color& other) const;
			Color& operator = (const Color& other);
			Color operator * (float fScale) const;
			//operator Color * (float fScale) const;
			void operator *= (float fScale);
			Color operator + (const Color& other) const;
			void operator += (const Color& other);
			bool operator == (const Color& other) const;
			bool operator != (const Color& other) const;
			// Convert color format for DX.
			//static float FromDWord(dword dwColor);
			//static dword& sRandom(dword& clr);
			void setColor(dword dwColor);
			void setColor(float fColor);
			void setColor(const Color& clr);

			static const Color& FromDWord(Color& clr, dword dwClr);
			static dword ToDWord(dword& dwClr, const Color& clr);
			static const Color& sRandom(uint uLoop = 3, bool bReverse = true);
			void fromDWord(dword dwColor);
			void fromFloat(float fColor);
			float toFloat() const;
			dword toDWord() const;
			void reverse();
			void gradient(float delta, float speed = 1.f);
			//
			void setR(float r, bool percent = true);
			void setG(float g, bool percent = true);
			void setB(float b, bool percent = true);
			void setA(float a, bool percent = true);
			void setRGBA(float r, float g, float b, float a = 1.f, bool percent = true);
			float r() const;
			float g() const;
			float b() const;
			float a() const;
			//
			void setR(uint R);
			void setG(uint G);
			void setB(uint B);
			void setA(uint A);
			void setRGBA(uint R, uint G, uint B, uint A = 255);
			uint R() const;
			uint G() const;
			uint B() const;
			uint A() const;
			//
			String toString() const;

		private:
			void copyOther(const Color& other);
			void valid(uint &C);
			void valid(float &c);


		public:
			static Color sLerp(const Color& clrA, const Color& clrB, float s);
			static Color sFromString(const String& strColor);

		public:
			static const Color	Red;
			static const Color	Green;
			static const Color	Blue;
			static const Color	White;
			static const Color	Black;
			static const Color	Gray;
			static const Color	Gold;
			static const Color	Silver;
			static const Color	Orange;
			static const Color	Yellow;
			static const Color	Pink;
			static const Color	Cyan;
			static const Color Vermilion;
			static const Color	RoyalBlue;
			static const Color Azury;
			static const Color Aquamarine4;

		};

		/*-----------------------------------------------------------
		class Vector
		------------------------------------------------------------*/
		class Vector : public IRoot
		{
		public:
			Vector();
			~Vector();
			Vector(float x, float y, float z, float w = 1.f);
			Vector(const Vector& other);
			bool operator == (const Vector& other) const;
			bool operator != (const Vector& other) const;
			bool operator < (const Vector& other) const;
			Vector& operator = (const Vector& other);
			Vector operator + (const Vector& other) const;
			Vector operator - (const Vector& other) const;
			Vector operator * (const Vector& other) const;
			//Vector operator / (const Vector& other) const;
			Vector operator * (float scale) const;
			Vector& operator *= (float scale);
			Vector& operator += (const Vector& other);
			Vector& operator -= (const Vector& other);
			//Vector& operator *= (const Vector& other);
			//Vector& operator /= (const Vector& other);

			friend Vector operator * (float scale, const Vector& v);

			void x(float x);
			void y(float y);
			void z(float z);
			void w(float w);
			void xyzw(float x, float y, float z, float w = 1.f);
			float x() const;
			float y() const;
			float z() const;
			float w() const;

			void normalize();
			// make vAxisY and self(as axisZ) ortho, and vAxisX = vAxisY X self(axisZ), normalize all axises.
			void orthoAxisWith(Vector &vAxisY, Vector &vAxisX);
			float dot(const Vector& v) const;
			Vector cross(const Vector& v) const;
			bool isParallel(const Vector& v) const;
			float length() const;
			bool intersect(float &distance, const Vector& vDir, const Vector& v0, const Vector& v1, const Vector& v2, float* pU = nullptr, float* pV = nullptr) const;
			void hermite(const Vector& v1, const Vector& t1, const Vector& v2, const Vector& t2, float s, Vector* vTangent = nullptr);

			void asVector();
			bool isVector() const;
			void asPoint();
			bool isPoint() const;
			bool isZero() const;

		public:
			static Vector fromString(const String& strVector);

		public:
			static const Vector PXAxis;
			static const Vector PYAxis;
			static const Vector PZAxis;
			static const Vector NXAxis;
			static const Vector NYAxis;
			static const Vector NZAxis;
			static const Vector Origin;

		private:
			void copyOther(const Vector& other);

		private:
			float mx, my, mz, mw;
		};

		/*-----------------------------------------------------------
		class Matrix
		------------------------------------------------------------*/
		class Matrix : public IRoot
		{
		public:
			Matrix();
			~Matrix();
			Matrix(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33);
			Matrix(float val[4][4]);
			Matrix(const Matrix& other);
			Matrix& operator = (const Matrix& other);
			Matrix operator * (const Matrix& other) const;
			Matrix& operator *= (const Matrix& other);
			void setData(float val[4][4]);
			bool setData(float* pData, uint uSize, bool bRowOrder = false);
			bool getData(float* pData, uint uSize, bool bRowOrder = false) const;
			void identity();
			Matrix inverse() const;
			void translate(float x, float y, float z, bool bOffset = true);
			void rotate(float x, float y, float z, bool bOffset = true);
			void rotate(const Vector& vAxis, float radianRot);
			void rotate(const Vector& vAxisX, float radianRotX, const Vector& vAxisY, float radianRotY, const Vector& vAxisZ, float radianRotZ);
			void scale(float x, float y, float z, bool bOffset = true);

			void fromXMATRIX(const XMMATRIX& xmat);
			XMMATRIX toXMMATRIX() const;

		private:
			void copyOther(const Matrix& other);
			XMFLOAT4X4 toXMFLOAT4X4() const;

		private:
			float m[4][4];
		};

		/*-----------------------------------------------------------
		class HitInfo
		------------------------------------------------------------*/
		class HitInfo
		{
		public:
			HitInfo();
			virtual ~HitInfo();
			HitInfo(const HitInfo& other);
			bool operator < (const HitInfo& other);
			HitInfo& operator = (const HitInfo& other);
			bool operator == (const HitInfo& other) const;
			float computerClosestPos(dword &dwIndex, Vector &vPos);
			void clear();
			void copyOther(const HitInfo& other);

		public:
			bool	mbHit;
			float	mfDistance;
			float	mU, mV, mW;
			ulong	muFace;
			dword	mIndex[3];
			Vector	mvPos[3];
			Vector	mvPick;
			uint	muSubID;		// sub-mesh ID of mesh.
			bool	mbSaveAllHits;	// save all hits
			TArray<HitInfo>*	mpAllHits;
		};

		/*-----------------------------------------------------------
		class Ray
		------------------------------------------------------------*/
		class Ray : public IRoot
		{
		public:
			Ray();
			virtual ~Ray();
			Ray(const Ray& o);
			Ray(const Vector& vStartPoint, const Vector& vDirection);
			Ray& operator = (const Ray& o);
			void startPoint(const Vector& vStart);
			const Vector& startPoint() const;
			void direction(const Vector& vDirection);
			const Vector& direction() const;
			void setRay(const Vector& vStartPoint, const Vector& vDirection);
			bool intersect(float &distance, const Vector& v0, const Vector& v1, const Vector& v2, float* pU = nullptr, float* pV = nullptr) const;

		private:
			void copyOther(const Ray& o);

		private:
			Vector	mvStartPoint;
			Vector	mvDirection;
		};

		/*-----------------------------------------------------------
		class LerpKey
		------------------------------------------------------------*/
		class LerpKey : public IRoot
		{
		public:
			LerpKey();
			virtual ~LerpKey();
			LerpKey(const LerpKey& other);
			LerpKey& operator = (const LerpKey& other);
			bool operator < (const LerpKey& other);
			bool operator == (const LerpKey& other);
			bool operator != (const LerpKey& other);

			void setLerpKey(const Vector& vPos, const FVector2& vStepFlag, const Vector& tangent, const EAlongWith& eFlag = AlongWith_X);
			void setLerpKey(const Vector& vPos, const FVector2& vStepFlag, const TArray<Vector>& aTangent);
			void getLerpKey(Vector& vPos, FVector2& vStepFlag, TArray<Vector>& aTangent) const;

			void setPos(const Vector& vPos);
			const Vector& getPos() const;
			void setStepFlag(const FVector2& vStepFlag);
			const FVector2& getStepFlag() const;
			void setTangent(const EAlongWith& eFlag, const Vector& vTan);
			const Vector& getTangent(const EAlongWith& eFlag) const;
			const TArray<Vector>& getTangent() const;

			static LerpKey sLoadLerpKeyFromString(const String& strLerpKey, float xRowStepFlag, float zColStepFlag);


		private:
			void copyOther(const LerpKey& other);

		private:
			Vector			mvPos;
			FVector2		mvStepFlag;	// x for 1D,(x,y) for 2D,such as i,(i,j).
			TArray<Vector>	maTangent;	// Tangent of x-axis,y-axis,z-axis. e.g.x for 1D,(x,y) for 2D,(x,y,z) for 3D.

		};

		/*-----------------------------------------------------------
		class Lerp
		------------------------------------------------------------*/
		class Lerp : public IRoot
		{
		public:
			// single-array lerp
			static bool sLerp(TArray<Vector> &aVector, const TArray<LerpKey>& aLerpKey, const EAlongWith& eFlag = AlongWith_X, bool bNotChangeBoundVertex = true);
			static bool sLerp(TArray<LerpKey> &aKeyOut, const TArray<LerpKey>& aLerpKey, const EAlongWith& eFlag = AlongWith_X, bool bNotChangeBoundVertex = true);
			// double-array lerp
			static bool sLerp(TDArray<Vector> &aPos, TDArray<Vector>* pTangentArray, const TArray<LerpKey>& aLerpKey, ulong uRow, ulong uCol, bool bNotChangeBoundVertex = true);
			// fractal
			static bool sFractal(TDArray<Vector> &aPos, TDArray<Vector>* pTangentArray, const TArray<LerpKey>& aLerpKey, ulong uRow, ulong uCol, bool bNotChangeBoundVertex = true);
			// fractal
			static bool sFractal(TDArray<Vector>* pPosArray, TDArray<Vector>* pTangentArray, TArray<LerpKey>* pLerpKey, ulong uFromRowIndex, ulong uFromColIndex, ulong uSpan, uint uDepth, float scaleMax, bool bNotChangeBoundVertex = true);
			// smooth
			static void sSmooth(TDArray<Vector>* pPosArray, const TArray<LerpKey>& aLerpKey);

			// @vHeight: input/output height value. It is a key value if the default value is in [0.f, 1.f]
			// @uGridPower: input grid param, grid = 2^uGridPower
			// @uSmoothTimes: smooth times
			static bool fractal(TDArray<float>* vHeight, uint uGridPower, uint uSmoothTimes = 1, bool bKeepBoundLeft = false, bool bKeepBoundRight = false, bool bKeepBoundBottom = false, bool bKeepBoundTop = false);
			static void smooth(TDArray<float>* vHeight, bool bKeepBoundLeft = false, bool bKeepBoundRight = false, bool bKeepBoundBottom = false, bool bKeepBoundTop = false);
		private:
			static bool fractal(TDArray<float>* vHeight, const Point2D& pitFrom, const Point2D& pitTo, uint uDepth);

		private:
			static bool sTwoPointLerp(TArray<Vector> &aVector, const LerpKey& v1, const LerpKey& v2, const EAlongWith& eFlag = AlongWith_X);
			static bool sTwoPointLerp(TArray<LerpKey> &aKeyOut, const LerpKey& v1, const LerpKey& v2, const EAlongWith& eFlag = AlongWith_X);
			// lerp along with X and Y for a crosspoint.
			static bool sCrossLerp(TDArray<Vector> &aVector, TArray<LerpKey>& aLerpKey, ulong uX, ulong uY, TArrayBool &bHasDone, ulong uRow, ulong uCol);
			// fractal once
			// @aOutPos: center,left,right,bottom,top.only center when bNotChangeBoundPos = true.
			// @aInPos: LT,LB,RT,RB.
			// @aKeyPoint[i]: .x() = 0,1,2,3,4 [center,left,right,bottom,top], .y() = key value.
			static bool sFractalOnce(TArray<float> &aOutPos, const TArray<float>& aInPos, const TArray<FVector2>& aKeyPoint, uint uDepth, float scaleMax = 1.f, bool bNotChangeBoundPos = true);

		};

		///*-----------------------------------------------------------
		//class Maths
		//------------------------------------------------------------*/
		//class Maths : public IRoot
		//{
		//public:
		//	Maths();
		//	virtual ~Maths();

		//private:
		//	void copyOther(const Maths& other);
		//	virtual bool doCreate(void* pData = nullptr);
		//	virtual void doRelease();

		//};


	}
}
