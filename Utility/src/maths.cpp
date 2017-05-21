/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/maths.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class Color
		------------------------------------------------------------*/
		const Color Color::Red = Color(1.f, 0.f, 0.f, 1.f);
		const Color Color::Green = Color(0.f, 1.f, 0.f, 1.f);
		const Color Color::Blue = Color(0.f, 0.f, 1.f, 1.f);
		const Color Color::White = Color(1.f, 1.f, 1.f, 1.f);
		const Color Color::Black = Color(0.f, 0.f, 0.f, 1.f);
		const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.f);
		const Color Color::Gold = Color(1.f, 0.75f, 0.f, 1.f);
		const Color Color::Silver = Color(0.75f, 0.75f, 0.75f, 1.f);
		const Color Color::Orange = Color(1.0f, 0.5f, 0.f, 1.f);
		const Color Color::Yellow = Color(1.f, 1.f, 0.f, 1.f);
		const Color Color::Pink = Color(1.f, 0.f, 1.f, 1.f);
		const Color Color::Cyan = Color(0.f, 1.f, 1.f, 1.f);
		const Color Color::Vermilion = Color(0.64f, 0.024f, 0.024f, 1.f);
		const Color Color::RoyalBlue = Color(0.5f, 0.5f, 1.f, 1.f);
		const Color Color::Azury = Color(0.5f, 0.5f, 1.f, 1.f);
		const Color Color::Aquamarine4 = Color(69U, 139U, 116U, 255U);

		Color::Color()
			:mdwColor(0xffffffff)
		{
		}

		Color::~Color()
		{
		}

		Color::Color(float r, float g, float b, float a)
			:mdwColor(0)
		{
			valid(r);
			valid(g);
			valid(b);
			valid(a);
			uint ur = uint(r * 255.f);
			uint ug = uint(g * 255.f);
			uint ub = uint(b * 255.f);
			uint ua = uint(a * 255.f);
			setRGBA(ur, ug, ub, ua);
		}

		Color::Color(uint R, uint G, uint B, uint A)
			:mdwColor(0)
		{
			setRGBA(R, G, B, A);
		}

		Color::Color(byte R, byte G, byte B, byte A)
			: mdwColor(0)
		{
			setRGBA((uint)R, (uint)G, (uint)B, (uint)A);
		}

		Color::Color(dword dwColor)
			: mdwColor(dwColor)
		{
		}

		Color::Color(const Color& other)
			: mdwColor(0)
		{
			copyOther(other);
		}

		bool Color::operator < (const Color& other) const
		{
			return mdwColor < other.toDWord();
		}

		Color& Color::operator = (const Color& other)
		{
			copyOther(other);
			return *this;
		}

		Color Color::operator * (float fScale) const
		{
			Color clr(*this);
			clr *= fScale;
			return clr;
		}

		//operator Color * (float fScale) const;

		void Color::operator *= (float fScale)
		{
			float clr;
			clr = r() * fScale;
			setR(clr);
			clr = g() * fScale;
			setG(clr);
			clr = b() * fScale;
			setB(clr);
			clr = a() * fScale;
			setA(clr);
		}

		Color Color::operator + (const Color& other) const
		{
			Color clr(*this);
			clr += other;
			return clr;
		}

		void Color::operator += (const Color& other)
		{
			float clr;
			clr = r() + other.r();
			setR(clr);
			clr = g() + other.g();
			setG(clr);
			clr = b() + other.b();
			setB(clr);
			clr = a() + other.a();
			setA(clr);
		}

		bool Color::operator == (const Color& other) const
		{
			return mdwColor == other.toDWord();
		}

		bool Color::operator != (const Color& other) const
		{
			return !(*this == other);
		}

		void Color::copyOther(const Color& other)
		{
			mdwColor = other.toDWord();
		}

		void Color::valid(uint &C)
		{
			//C = (C > 255)? 255:C;
			//C = (C < 0  )? 0  :C;
			if (C > 255)
			{
				C = 255;
			}
			else if (C < 0)
			{
				C = 0;
			}
		}

		void Color::valid(float &c)
		{
			//c = (c > 1.0)? 1.0f:c;
			//c = (c < 0.0)? 0.0f:c;
			if (c > 1.f)
			{
				c = 1.f;
			}
			else if (c < 0.f)
			{
				c = 0.f;
			}
		}

		void Color::setA(uint A)
		{
			valid(A);
			A <<= 24;
			mdwColor &= 0x00ffffff;
			mdwColor |= A;
		}

		void Color::setR(uint R)
		{
			valid(R);
			R <<= 16;
			mdwColor &= 0xff00ffff;
			mdwColor |= R;
		}

		void Color::setG(uint G)
		{
			valid(G);
			G <<= 8;
			mdwColor &= 0xffff00ff;
			mdwColor |= G;
		}

		void Color::setB(uint B)
		{
			valid(B);
			//B <<= 0;
			mdwColor &= 0xffffff00;
			mdwColor |= B;
		}

		void Color::setRGBA(uint R, uint G, uint B, uint A /* = 255 */)
		{
			valid(R);
			valid(G);
			valid(B);
			valid(A);
			//
			mdwColor = 0;
			A <<= 24;
			mdwColor |= A;

			R <<= 16;
			mdwColor |= R;

			G <<= 8;
			mdwColor |= G;

			//B <<= 0;
			mdwColor |= B;
		}

		const Color& Color::FromDWord(Color& clr, dword dwColor)
		{
			const dword temp = dwColor;
			dword val;
			float a, r, g, b;

			dwColor = temp;
			val = dwColor & 0xff000000;
			val >>= 24;
			a = (float)val / 255.f;

			dwColor = temp;
			val = dwColor & 0x00ff0000;
			val >>= 16;
			r = (float)val / 255.f;

			dwColor = temp;
			val = dwColor & 0x0000ff00;
			val >>= 8;
			g = (float)val / 255.f;

			dwColor = temp;
			val = dwColor & 0x000000ff;
			val >>= 0;
			b = (float)val / 255.f;

			clr = Color(r, g, b, a);
			return clr;
		}

		dword Color::ToDWord(dword& dwClr, const Color& clr)
		{
			dwClr = clr.toDWord();
			return dwClr;
		}

		const Color& Color::sRandom(uint uLoop /* = 3 */, bool bReverse /* = true */)
		{
			static Color sClr(0.f, 0.f, 0.f, 0.f);
			float a, r, g, b;
			uint sr = (uint)(time(nullptr));
			srand(sr);
			for (uint i = 0; i<uLoop; i++)
			{
				a = (rand() % 1000)*0.001f;
				if (a != sClr.a())
					break;
			}
			for (uint i = 0; i<uLoop; i++)
			{
				r = (rand() % 1000)*0.001f;
				if (r != sClr.r())
					break;
			}
			for (uint i = 0; i<uLoop; i++)
			{
				g = (rand() % 1000)*0.001f;
				if (g != sClr.g())
					break;
			}
			for (uint i = 0; i<uLoop; i++)
			{
				b = (rand() % 1000)*0.001f;
				if (b != sClr.b())
					break;
			}

			FASSERT(Color(a, r, g, b) != sClr);
			sClr = Color(r, g, b, a);
			if (bReverse)
			{
				sClr.reverse();
			}
			return sClr;
		}

		void Color::reverse()
		{
			mdwColor = ~mdwColor;
		}

		void Color::gradient(float delta, float speed /* = 1.f */)
		{
		}

		void Color::setColor(float fColor)
		{
			dword dw = Maths::FloatToDW(fColor);
			setColor(dw);
		}

		void Color::setColor(dword dwColor)
		{
			mdwColor = dwColor;
		}

		void Color::setColor(const Color& clr)
		{
			*this = clr;
		}

		void Color::fromDWord(dword dwColor)
		{
			mdwColor = dwColor;
		}

		void Color::fromFloat(float fColor)
		{
			dword dwClr = *((dword*)(&fColor));
			fromDWord(dwClr);
		}

		float Color::toFloat() const
		{
			dword dwClr = toDWord();
			float fClr = *((float*)(&dwClr));
			return fClr;
		}

		dword Color::toDWord() const
		{
			return mdwColor;
		}

		void Color::setA(float a, bool percent /*= true*/)
		{
			uint ua = 0;
			if (percent)
			{
				valid(a);
				ua = (uint)(a * 255);
			}
			else
			{
				ua = (uint)a;
			}
			setA(ua);
		}

		void Color::setR(float r, bool percent /*= true*/)
		{
			uint ur = 0;
			if (percent)
			{
				valid(r);
				ur = (uint)(r * 255);
			}
			else
			{
				ur = (uint)r;
			}
			setR(ur);
		}

		void Color::setG(float g, bool percent /*= true*/)
		{
			uint ug = 0;
			if (percent)
			{
				valid(g);
				ug = (uint)(g * 255);
			}
			else
			{
				ug = (uint)g;
			}
			setG(ug);
		}

		void Color::setB(float b, bool percent /*= true*/)
		{
			uint ub = 0;
			if (percent)
			{
				valid(b);
				ub = (uint)(b * 255);
			}
			else
			{
				ub = (uint)b;
			}
			setB(ub);
		}

		void Color::setRGBA(float r, float g, float b, float a /* = 1.f */, bool percent /* = true */)
		{
			valid(r);
			valid(g);
			valid(b);
			valid(a);
			uint R = (uint)(r * 255);
			uint G = (uint)(g * 255);
			uint B = (uint)(b * 255);
			uint A = (uint)(a * 255);
			setRGBA(R, G, B, A);
		}

		uint Color::A() const
		{
			uint A = (mdwColor & 0xff000000);
			A >>= 24;
			return A;
		}

		uint Color::R() const
		{
			uint R = (mdwColor & 0x00ff0000);
			R >>= 16;
			return R;
		}

		uint Color::G() const
		{
			uint G = (mdwColor & 0x0000ff00);
			G >>= 8;
			return G;
		}

		uint Color::B() const
		{
			uint B = (mdwColor & 0x000000ff);
			//G >>= 0;
			return B;
		}

		float Color::a() const
		{
			return (float)(A() / 255.f);
		}

		float Color::r() const
		{
			return (float)(R() / 255.f);
		}

		float Color::g() const
		{
			return (float)(G() / 255.f);
		}

		float Color::b() const
		{
			return (float)(B() / 255.f);
		}

		String Color::toString() const
		{
			String strColor(R());
			strColor += String(",") + String(G());
			strColor += String(",") + String(B());
			strColor += String(",") + String(A());
			return strColor;
		}

		Color Color::sLerp(const Color& clrA, const Color& clrB, float s)
		{
			const float r = clrA.r() + s * (clrB.r() - clrA.r());
			const float g = clrA.g() + s * (clrB.g() - clrA.g());
			const float b = clrA.b() + s * (clrB.b() - clrA.b());
			const float a = clrA.a() + s * (clrB.a() - clrA.a());
			Color clr(r, g, b, a);
			//clr.setRGBA(r,g,b,a);
			return clr;
		}

		Color Color::sFromString(const String& strColor)
		{
			TArray<String> strArray;
			strArray = strColor.split(":");
			const String strRGBA = (strArray.size() >= 1) ? strArray[0] : "";
			const String strAlpha = (strArray.size() >= 2) ? strArray[1] : "";
			Color clr;
			if (strRGBA.compareIgnoreCase("red"))
			{
				clr = Color::Red;
			}
			else if (strRGBA.compareIgnoreCase("green"))
			{
				clr = Color::Green;
			}
			else if (strRGBA.compareIgnoreCase("blue"))
			{
				clr = Color::Blue;
			}
			else if (strRGBA.compareIgnoreCase("white"))
			{
				clr = Color::White;
			}
			else if (strRGBA.compareIgnoreCase("black"))
			{
				clr = Color::Black;
			}
			else if (strRGBA.compareIgnoreCase("gray"))
			{
				clr = Color::Gray;
			}
			else if (strRGBA.compareIgnoreCase("Gold"))
			{
				clr = Color::Gold;
			}
			else if (strRGBA.compareIgnoreCase("silver"))
			{
				clr = Color::Silver;
			}
			else if (strRGBA.compareIgnoreCase("orange"))
			{
				clr = Color::Orange;
			}
			else if (strRGBA.compareIgnoreCase("yellow"))
			{
				clr = Color::Yellow;
			}
			else if (strRGBA.compareIgnoreCase("pink"))
			{
				clr = Color::Pink;
			}
			else if (strRGBA.compareIgnoreCase("cyan"))
			{
				clr = Color::Cyan;
			}
			else if (strRGBA.compareIgnoreCase("vermilion"))
			{
				clr = Color::Vermilion;
			}
			else if (strRGBA.compareIgnoreCase("royalblue"))
			{
				clr = Color::RoyalBlue;
			}
			else if (strRGBA.compareIgnoreCase("aquamarine4"))
			{
				clr = Color::Aquamarine4;
			}
			else
			{
				TArray<String> strArray;
				strArray = strRGBA.split(",");
				uint uSum = strArray.size();
				FASSERT(uSum >= 3);
				int uVal[4] = { 255, 255, 255, 255 };
				for (uint i = 0; i<uSum && i<4; i++)
				{
					if (!String::sToValue(uVal[i], strArray[i]))
					{
						uVal[i] = 255;
					}
				}
				FASSERT(uVal[0] >= 0 && uVal[0] <= 255 && uVal[1] >= 0 && uVal[1] <= 255 && uVal[2] >= 0 && uVal[2] <= 255 && uVal[3] >= 0 && uVal[3] <= 255);
				clr.setRGBA((uint)uVal[0], (uint)uVal[1], (uint)uVal[2], (uint)uVal[3]);
			}
			if (!strAlpha.isEmpty())
			{
				clr.setA(strAlpha.toFloat());
			}
			return clr;
		}

		/*-----------------------------------------------------------
		class Vector
		------------------------------------------------------------*/
		const Vector Vector::PXAxis = Vector(1.f, 0.f, 0.f, 0.f);
		const Vector Vector::PYAxis = Vector(0.f, 1.f, 0.f, 0.f);
		const Vector Vector::PZAxis = Vector(0.f, 0.f, 1.f, 0.f);
		const Vector Vector::NXAxis = Vector(-1.f, 0.f, 0.f, 0.f);
		const Vector Vector::NYAxis = Vector(0.f, -1.f, 0.f, 0.f);
		const Vector Vector::NZAxis = Vector(0.f, 0.f, -1.f, 0.f);
		const Vector Vector::Origin = Vector(0.f, 0.f, 0.f, 0.f);

		Vector::Vector()
			: mx(0.f)
			, my(0.f)
			, mz(0.f)
			, mw(1.f)
		{
		}

		Vector::~Vector()
		{
		}

		Vector::Vector(float x, float y, float z, float w /* = 1.f */)
			: mx(x)
			, my(y)
			, mz(z)
			, mw(w)
		{
		}

		Vector::Vector(const Vector& other)
			: mx(other.mx)
			, my(other.my)
			, mz(other.mz)
			, mw(other.mw)
		{
			//copyOther(other);
		}

		bool Vector::operator == (const Vector& other) const
		{
			return (mx == other.mx && my == other.my && mz == other.mz && mw == other.mw);
		}

		bool Vector::operator != (const Vector& other) const
		{
			return !(this->operator==(other));
		}

		bool Vector::operator < (const Vector& other) const
		{
			return false;
		}

		Vector& Vector::operator = (const Vector& other)
		{
			copyOther(other);
			return *this;
		}

		Vector Vector::operator + (const Vector& other) const
		{
			Vector v(mx + other.mx, my + other.my, mz + other.mz, mw);
			return v;
		}

		Vector Vector::operator - (const Vector& other) const
		{
			Vector v(mx - other.mx, my - other.my, mz - other.mz, mw);
			return v;
		}

		Vector Vector::operator * (const Vector& other) const
		{
			Vector vRe = cross(other);
			return vRe;
		}

		//Vector Vector::operator / (const Vector& other) const;

		Vector Vector::operator * (float scale) const
		{
			Vector v(mx * scale, my * scale, mz * scale, mw);
			return v;
		}

		Vector& Vector::operator *= (float scale)
		{
			mx *= scale;
			my *= scale;
			mz *= scale;
			return *this;
		}

		Vector& Vector::operator += (const Vector& other)
		{
			mx += other.mx;
			my += other.my;
			mz += other.mz;
			return *this;
		}

		Vector& Vector::operator -= (const Vector& other)
		{
			mx -= other.mx;
			my -= other.my;
			mz -= other.mz;
			return *this;
		}

		//Vector& Vector::operator *= (const Vector& other);
		//Vector& Vector::operator /= (const Vector& other);

		Vector operator * (float scale, const Vector& v)
		{
			Vector vRe(v.mx * scale, v.my * scale, v.mz * scale, v.mw);
			return vRe;
		}

		void Vector::copyOther(const Vector& other)
		{
			mx = other.mx;
			my = other.my;
			mz = other.mz;
			mw = other.mw;
		}

		void Vector::x(float x)
		{
			mx = x;
		}

		void Vector::y(float y)
		{
			my = y;
		}

		void Vector::z(float z)
		{
			mz = z;
		}

		void Vector::w(float w)
		{
			mw = w;
		}

		void Vector::xyzw(float x, float y, float z, float w /* = 1.f */)
		{
			mx = x;
			my = y;
			mz = z;
			mw = w;
		}

		float Vector::x() const
		{
			return mx;
		}

		float Vector::y() const
		{
			return my;
		}

		float Vector::z() const
		{
			return mz;
		}

		float Vector::w() const
		{
			return mw;
		}

		void Vector::normalize()
		{
			XMFLOAT3 temp(mx, my, mz);
			XMVECTOR vec = XMLoadFloat3(&temp);
			vec = XMVector3Normalize(vec);
			XMStoreFloat3(&temp, vec);
			mx = temp.x;
			my = temp.y;
			mz = temp.z;
			// keep mw = mw as point or vector
		}

		void Vector::orthoAxisWith(Vector &vAxisY, Vector &vAxisX)
		{
			normalize();
			vAxisY.normalize();
			float len = dot(vAxisY);
			Vector v(*this);
			v *= len;
			vAxisY -= v;
			vAxisY.normalize();
			vAxisX = vAxisY.cross(*this);
			vAxisX.normalize();
		}

		float Vector::dot(const Vector& v) const
		{
			float dt = mx * v.mx + my * v.my + mz * v.mz;
			return dt;
		}

		Vector Vector::cross(const Vector& v) const
		{
			XMFLOAT3 v1(mx, my, mz);
			XMVECTOR xv1 = XMLoadFloat3(&v1);
			XMFLOAT3 v2(v.mx, v.my, v.mz);
			XMVECTOR xv2 = XMLoadFloat3(&v2);
			XMVECTOR xv = XMVector3Cross(xv1, xv2);
			XMStoreFloat3(&v1, xv);
			Vector vRe(v1.x, v1.y, v1.z, 0.f);
			return vRe;
		}

		bool Vector::isParallel(const Vector& v) const
		{
			Vector vThis(*this), vOther(v);
			vThis.asVector();
			vOther.asVector();
			vThis.normalize();
			vOther.normalize();
			float dotVal = vThis.dot(vOther);
			bool bOk = fabs(dotVal - 1.f) < 0.0001f;
			return bOk;
		}

		float Vector::length() const
		{
			XMFLOAT3 temp(mx, my, mz);
			XMVECTOR vec = XMLoadFloat3(&temp);
			vec = XMVector3Length(vec);
			XMStoreFloat3(&temp, vec);
			return temp.x;
		}

		bool Vector::intersect(float &distance, const Vector& vDir, const Vector& v0, const Vector& v1, const Vector& v2, float* pU /* = nullptr */, float* pV /* = nullptr */) const
		{
			const Vector& vPos = *this;
			float u = 0.f, v = 0.f;

			Vector edge1 = v1 - v0;
			Vector edge2 = v2 - v0;
			//FASSERT(!edge1.isOrigin() && !edge2.isOrigin() && !edge1.isParallel(edge2));
			if (edge1.isZero() || edge2.isZero() || edge1.isParallel(edge2))
				return false;
			Vector pvec = vDir * edge2;
			float det = edge1.dot(pvec);
			Vector tvec;
			if (det > 0)
			{
				tvec = vPos - v0;
			}
			else
			{
				tvec = v0 - vPos;
				det = -det;
			}

			if (fabs(det) < 0.00001f)
				//if (Maths::PFIsNearZero(det))
			{
				return false;
			}

			u = tvec.dot(pvec);
			if (u < 0.0f || u > det)
			{
				return false;
			}

			Vector qvec;
			qvec = tvec * edge1;
			v = vDir.dot(qvec);
			if (v < 0.0f || u + v > det)
			{
				return false;
			}

			distance = edge2.dot(qvec);
			float fInvDet = 1.0f / det;
			distance *= fInvDet;
			u *= fInvDet;
			v *= fInvDet;
			if (nullptr != pU)
			{
				*pU = u;
			}
			if (nullptr != pV)
			{
				*pV = v;
			}

			return true;
		}

		void Vector::hermite(const Vector& v1, const Vector& t1, const Vector& v2, const Vector& t2, float s, Vector* vTangent /* = NULL */)
		{
			/*
			A = 2v1 - 2v2 + t2 + t1
			B = 3v2 - 3v1 - 2t1 - t2
			C = t1
			D = v1
			=>
			Q(s) = As3 + Bs2 + Cs + D (and therefore, Q'(s) = 3As2 + 2Bs + C)
			so:
			a) Q(0) = v1, so Q'(0) = t1
			b) Q(1) = v2, so Q'(1) = t2
			=>
			Q(s) = (2v1 - 2v2 + t2 + t1)s3 + (3v2 - 3v1 - 2t1 - t2)s2 + t1s + v1
			=>
			Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2
			*/

			Vector vTemp;
			vTemp = (2.f*s*s*s - 3.f*s*s + 1.f) * v1;
			vTemp += (-2.f*s*s*s + 3.f*s*s) * v2;
			vTemp += (s*s*s - 2.f*s*s + s) * t1;
			vTemp += (s*s*s - s*s) * t2;
			*this = vTemp;
			if (NULL != vTangent)
			{
				vTemp = 2.f * v1;
				vTemp -= 2.f * v2;
				vTemp += t2;
				vTemp += t1;
				*vTangent = (3.f*s*s) * vTemp;
				vTemp = 3.f * v2;
				vTemp -= 3.f * v1;
				vTemp -= 2.f * t1;
				vTemp -= t2;
				*vTangent += (2.f*s) * vTemp;
				*vTangent += t1;
			}
		}

		void Vector::asVector()
		{
			mw = 0.f;
		}

		bool Vector::isVector() const
		{
			return (0.f == mw);
		}

		void Vector::asPoint()
		{
			mw = 1.f;
		}

		bool Vector::isPoint() const
		{
			return (1.f == mw);
		}

		bool Vector::isZero() const
		{
			return (0.f == mx && 0.f == my && 0.f == mz);
		}

		Vector Vector::fromString(const String& strVector)
		{
			Vector vec;
			if (strVector.compareIgnoreCase("PXAxis"))
			{
				vec = Vector::PXAxis;
			}
			else if (strVector.compareIgnoreCase("PYAxis"))
			{
				vec = Vector::PYAxis;
			}
			else if (strVector.compareIgnoreCase("PZAxis"))
			{
				vec = Vector::PZAxis;
			}
			else if (strVector.compareIgnoreCase("NXAxis"))
			{
				vec = Vector::NXAxis;
			}
			else if (strVector.compareIgnoreCase("NYAxis"))
			{
				vec = Vector::NYAxis;
			}
			else if (strVector.compareIgnoreCase("NZAxis"))
			{
				vec = Vector::NZAxis;
			}
			else if (strVector.compareIgnoreCase("Origin"))
			{
				vec = Vector::Origin;
			}
			else
			{
				TArray<String> strArray;
				strArray = strVector.split(",");
				uint uSum = strArray.size();
				//FASSERT(uSum >= 3);
				float fVal[3] = { 0, 0, 0 };
				for (uint i = 0; i<uSum && i<3; i++)
				{
					if (!strArray[i].isDigital(fVal[i]))
					{
						fVal[i] = 0;
					}
				}
				vec.xyzw(fVal[0], fVal[1], fVal[2]);
			}
			return vec;
		}

		/*-----------------------------------------------------------
		class Matrix
		------------------------------------------------------------*/
		Matrix::Matrix()
		{
			identity();
		}

		Matrix::Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		Matrix::Matrix(float val[4][4])
		{
			setData(val);
		}

		Matrix::~Matrix()
		{
			identity();
		}

		Matrix::Matrix(const Matrix& other)
		{
			copyOther(other);
		}

		Matrix& Matrix::operator = (const Matrix& other)
		{
			copyOther(other);
			return *this;
		}

		Matrix Matrix::operator * (const Matrix& other) const
		{
			XMMATRIX xmat = toXMMATRIX() * other.toXMMATRIX();
			Matrix mat;
			mat.fromXMATRIX(xmat);
			return mat;
		}

		Matrix& Matrix::operator *= (const Matrix& other)
		{
			XMMATRIX xmat = toXMMATRIX() * other.toXMMATRIX();
			fromXMATRIX(xmat);
			return *this;
		}

		void Matrix::copyOther(const Matrix& other)
		{
			memcpy(m, other.m, sizeof(m));
		}

		void Matrix::setData(float val[4][4])
		{
			memcpy(m, val, 16);
			memcpy(m + 1, val + 1, 16);
			memcpy(m + 2, val + 2, 16);
			memcpy(m + 3, val + 3, 16);
		}

		bool Matrix::setData(float* pData, uint uSize, bool bRowOrder /* = false */)
		{
			if (NULL == pData || uSize < 16)
				return false;
			if (bRowOrder)
			{
				//memcpy(m, pData, 16);
				//memcpy(m + 1, pData + 4, 16);
				//memcpy(m + 2, pData + 8, 16);
				//memcpy(m + 3, pData + 12, 16);
				for (int i = 0; i < 4; i++)
				{
					m[i][0] = pData[i * 4 + 0];
					m[i][1] = pData[i * 4 + 1];
					m[i][2] = pData[i * 4 + 2];
					m[i][3] = pData[i * 4 + 3];
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					m[0][i] = pData[i * 4 + 0];
					m[1][i] = pData[i * 4 + 1];
					m[2][i] = pData[i * 4 + 2];
					m[3][i] = pData[i * 4 + 3];
				}
			}
		}

		bool Matrix::getData(float* pData, uint uSize, bool bRowOrder /* = false */) const
		{
			if (NULL == pData || uSize < 16)
				return false;
			if (bRowOrder)
			{
				for (int i = 0; i < 4; i++)
				{
					pData[i * 4 + 0] = m[i][0];
					pData[i * 4 + 1] = m[i][1];
					pData[i * 4 + 2] = m[i][2];
					pData[i * 4 + 3] = m[i][3];
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					pData[i * 4 + 0] = m[0][i];
					pData[i * 4 + 1] = m[1][i];
					pData[i * 4 + 2] = m[2][i];
					pData[i * 4 + 3] = m[3][i];
				}
			}
			return true;
		}

		void Matrix::identity()
		{
			memset(m, 0, sizeof(m));
			m[0][0] = 1.f;
			m[1][1] = 1.f;
			m[2][2] = 1.f;
			m[3][3] = 1.f;
		}

		Matrix Matrix::inverse() const
		{
			XMMATRIX xmat = toXMMATRIX();
			XMVECTOR xvec;
			XMMATRIX xmatinv = XMMatrixInverse(&xvec, xmat);
			Matrix mat;
			mat.fromXMATRIX(xmatinv);
			return mat;
		}

		void Matrix::translate(float x, float y, float z, bool bOffset /* = true */)
		{
			if (bOffset)
			{
				m[3][0] += x;
				m[3][1] += y;
				m[3][2] += z;
			}
			else
			{
				m[3][0] = x;
				m[3][1] = y;
				m[3][2] = z;
			}
		}

		void Matrix::rotate(float x, float y, float z, bool bOffset /* = true */)
		{
			XMFLOAT4X4 temp;
			XMMATRIX mat = XMMatrixRotationRollPitchYaw(x, y, z);
			if (bOffset)
			{
				memcpy(temp.m, m, sizeof(m));
				XMMATRIX ori = XMLoadFloat4x4(&temp);
				mat = ori * mat;
			}
			else
			{
			}
			XMStoreFloat4x4(&temp, mat);
			memcpy(m, temp.m, sizeof(m));
		}

		void Matrix::rotate(const Vector& vAxis, float radianRot)
		{
			XMFLOAT3 temp(vAxis.x(), vAxis.y(), vAxis.z());
			XMVECTOR xv = XMLoadFloat3(&temp);
			XMMATRIX xmat = XMMatrixRotationAxis(xv, radianRot);
			XMFLOAT4X4 mat;
			XMStoreFloat4x4(&mat, xmat);
			memcpy(m, mat.m, sizeof(m));
		}

		void Matrix::rotate(const Vector& vAxisX, float radianRotX, const Vector& vAxisY, float radianRotY, const Vector& vAxisZ, float radianRotZ)
		{
			XMFLOAT3 vf3(vAxisX.x(), vAxisX.y(), vAxisX.z());
			XMVECTOR xv = XMLoadFloat3(&vf3);
			XMMATRIX xmat = XMMatrixRotationAxis(xv, radianRotX);

			vf3.x = vAxisY.x(); vf3.y = vAxisY.y(); vf3.z = vAxisY.z();
			xv = XMLoadFloat3(&vf3);
			xmat *= XMMatrixRotationAxis(xv, radianRotY);

			vf3.x = vAxisZ.x(); vf3.y = vAxisZ.y(); vf3.z = vAxisZ.z();
			xv = XMLoadFloat3(&vf3);
			xmat *= XMMatrixRotationAxis(xv, radianRotZ);

			XMFLOAT4X4 mat;
			XMStoreFloat4x4(&mat, xmat);
			memcpy(m, mat.m, sizeof(m));
		}

		void Matrix::scale(float x, float y, float z, bool bOffset /* = true */)
		{
			if (bOffset)
			{
				m[0][0] *= x;
				m[1][1] *= y;
				m[2][2] *= z;
			}
			else
			{
				m[0][0] = x;
				m[1][1] = y;
				m[2][2] = z;
			}
		}

		void Matrix::fromXMATRIX(const XMMATRIX& xmat)
		{
			XMFLOAT4X4 temp;
			XMStoreFloat4x4(&temp, xmat);
			memcpy(m, temp.m, sizeof(m));
		}

		XMMATRIX Matrix::toXMMATRIX() const
		{
			XMFLOAT4X4 temp;
			memcpy(temp.m, m, sizeof(m));
			XMMATRIX mat = XMLoadFloat4x4(&temp);
			return mat;
		}

		XMFLOAT4X4 Matrix::toXMFLOAT4X4() const
		{
			XMFLOAT4X4 mat;
			memcpy(mat.m, m, sizeof(m));
			return mat;
		}

		/*-----------------------------------------------------------
		class HitInfo
		------------------------------------------------------------*/
		HitInfo::HitInfo()
			: mbHit(false)
			, mfDistance(1.7976931348623158e+38f)// max float
			, mU(0.f)
			, mV(0.f)
			, mW(0.f)
			, muFace(0)
			, muSubID(0)
			, mbSaveAllHits(false)
			, mpAllHits(nullptr)
		{
			mIndex[0] = 0;
			mIndex[1] = 0;
			mIndex[2] = 0;
		}

		HitInfo::~HitInfo()
		{
			clear();
		}

		HitInfo::HitInfo(const HitInfo& other)
		{
			copyOther(other);
		}

		void HitInfo::copyOther(const HitInfo& other)
		{
			mbHit = other.mbHit;
			mfDistance = other.mfDistance;
			mU = other.mU;
			mV = other.mV;
			mW = other.mW;
			muFace = other.muFace;
			mIndex[0] = other.mIndex[0];
			mIndex[1] = other.mIndex[1];
			mIndex[2] = other.mIndex[2];
			mvPos[0] = other.mvPos[0];
			mvPos[1] = other.mvPos[1];
			mvPos[2] = other.mvPos[2];
			mvPick = other.mvPick;
			muSubID = other.muSubID;
			mbSaveAllHits = other.mbSaveAllHits;
			//FDeepCopy(TArray<HitInfo>, mpAllHits, other.mpAllHits);
		}

		bool HitInfo::operator < (const HitInfo& other)
		{
			if (mbHit && !other.mbHit)
				return true;
			else if (!mbHit && other.mbHit)
				return false;
			return mfDistance < other.mfDistance;
		}

		HitInfo& HitInfo::operator = (const HitInfo& other)
		{
			copyOther(other);
			return *this;
		}

		bool HitInfo::operator == (const HitInfo& other) const
		{
			return (mbHit == other.mbHit
				&&	mfDistance == other.mfDistance
				&&	mU == other.mU
				&&	mV == other.mV
				&&	mW == other.mW
				&&	muFace == other.muFace
				&&	mIndex[0] == other.mIndex[0]
				&& mIndex[1] == other.mIndex[1]
				&& mIndex[2] == other.mIndex[2]
				&& mvPos[0] == other.mvPos[0]
				&& mvPos[1] == other.mvPos[1]
				&& mvPos[2] == other.mvPos[2]
				&& mvPick == other.mvPick
				&&	muSubID == other.muSubID
				&&	mbSaveAllHits == other.mbSaveAllHits);
			//&&	IRoot::sEquate<TArray<HitInfo>>(mpAllHits, other.mpAllHits));
		}

		float HitInfo::computerClosestPos(dword &dwIndex, Vector &vPos)
		{
			float dis[3];
			dis[0] = (mvPick - mvPos[0]).length();
			dis[1] = (mvPick - mvPos[1]).length();
			dis[2] = (mvPick - mvPos[2]).length();
			uint i = (dis[0] < dis[1]) ? ((dis[0] < dis[2]) ? 0 : 2) : ((dis[1] < dis[2]) ? 1 : 2);
			dwIndex = mIndex[i];
			vPos = mvPos[i];
			return dis[i];
		}

		void HitInfo::clear()
		{
			mbHit = false;
			mfDistance = 1.7976931348623158e+38f;
			mU = 0;
			mV = 0;
			mW = 0;
			muFace = 0;
			mIndex[0] = 0;
			mIndex[1] = 0;
			mIndex[2] = 0;
			muSubID = 0;
			mbSaveAllHits = false;
			TArray<HitInfo>::destroyMem<TArray<HitInfo>>(mpAllHits);
		}

		/*-----------------------------------------------------------
		class Ray
		------------------------------------------------------------*/
		Ray::Ray()
			:mvStartPoint(0, 0, 0)
			, mvDirection(0, 0, 0)
		{
		}

		Ray::~Ray()
		{

		}

		Ray::Ray(const Vector& vStartPoint, const Vector& vDirection)
		{
			setRay(vStartPoint, vDirection);
		}

		Ray::Ray(const Ray& other)
		{
			copyOther(other);
		}

		Ray& Ray::operator = (const Ray& other)
		{
			copyOther(other);
			return *this;
		}

		void Ray::copyOther(const Ray& other)
		{
			IRoot::operator = (other);
			mvStartPoint = other.mvStartPoint;
			mvDirection = other.mvDirection;
		}

		void Ray::startPoint(const Vector& vStartPoint)
		{
			mvStartPoint = vStartPoint;
		}

		const Vector& Ray::startPoint() const
		{
			return mvStartPoint;
		}

		void Ray::direction(const Vector& vDirection)
		{
			mvDirection = vDirection;
		}

		const Vector& Ray::direction() const
		{
			return mvDirection;
		}

		void Ray::setRay(const Vector& vStartPoint, const Vector& vDirection)
		{
			mvStartPoint = vStartPoint;
			mvDirection = vDirection;
		}

		bool Ray::intersect(float &distance, const Vector& v0, const Vector& v1, const Vector& v2, float* pU /* = nullptr */, float* pV /* = nullptr */) const
		{
			bool bOk = mvStartPoint.intersect(distance, mvDirection, v0, v1, v2, pU, pV);
			return bOk;
		}

		/*-----------------------------------------------------------
		class LerpKey
		------------------------------------------------------------*/
		LerpKey::LerpKey()
			: mvPos(Vector(0, 0, 0))
			, mvStepFlag(FVector2(0, 0))
		{
			maTangent.resize(AlongWith_Max);
			maTangent[0] = Vector(1, 0, 0);
			maTangent[1] = Vector(0, 1, 0);
			maTangent[2] = Vector(0, 0, 1);
		}

		LerpKey::~LerpKey()
		{

		}

		LerpKey::LerpKey(const LerpKey& other)
			:mvPos(Vector(0, 0, 0))
			, mvStepFlag(FVector2(0, 0))
		{
			maTangent.resize(AlongWith_Max);
			maTangent[0] = Vector(1, 0, 0);
			maTangent[1] = Vector(0, 1, 0);
			maTangent[2] = Vector(0, 0, 1);
			copyOther(other);
		}

		LerpKey& LerpKey::operator = (const LerpKey& other)
		{
			copyOther(other);
			return *this;
		}

		bool LerpKey::operator < (const LerpKey& other)
		{
			FVector2 step = other.getStepFlag();
			bool b1 = ((mvStepFlag.X() < step.X()) && mvStepFlag.Y() < step.Y());
			bool b2 = ((mvStepFlag.X() == step.X()) && mvStepFlag.Y() < step.Y());
			bool b3 = ((mvStepFlag.X() < step.X()) && mvStepFlag.Y() == step.Y());
			return (b1 || b2 || b3);
		}

		bool LerpKey::operator == (const LerpKey& other)
		{
			//bool b1 = (mvPos == other.getPos());
			bool b2 = (mvStepFlag == other.getStepFlag());
			//bool b3 = (maTangent == other.getTangent());
			return b2;//(b1 && b2 && b3);
		}

		bool LerpKey::operator != (const LerpKey& other)
		{
			return !(*this == other);
		}

		void LerpKey::setLerpKey(const Vector& vPos, const FVector2& vStepFlag, const Vector& tangent, const EAlongWith& eFlag /* = AlongWith_X */)
		{
			mvPos = vPos;
			mvStepFlag = vStepFlag;
			setTangent(eFlag, tangent);
		}

		void LerpKey::setLerpKey(const Vector& vPos, const FVector2& vStepFlag, const TArray<Vector>& aTangent)
		{
			mvPos = vPos;
			mvStepFlag = vStepFlag;
			maTangent = aTangent;
		}

		void LerpKey::getLerpKey(Vector& vPos, FVector2& vStepFlag, TArray<Vector>& aTangent) const
		{
			vPos = mvPos;
			vStepFlag = mvStepFlag;
			aTangent = maTangent;
		}

		void LerpKey::setPos(const Vector& vPos)
		{
			mvPos = vPos;
		}

		const Vector& LerpKey::getPos() const
		{
			return mvPos;
		}

		void LerpKey::setStepFlag(const FVector2& vStepFlag)
		{
			mvStepFlag = vStepFlag;
		}

		const FVector2& LerpKey::getStepFlag() const
		{
			return mvStepFlag;
		}

		void LerpKey::setTangent(const EAlongWith& eFlag, const Vector& vTan)
		{
			FASSERT(eFlag >= 0 && eFlag < AlongWith_Max);
			maTangent[eFlag] = vTan;
			maTangent[eFlag].normalize();
			switch (eFlag)
			{
			case AlongWith_X:
			case AlongWith_Z:
				maTangent[AlongWith_Y] = maTangent[AlongWith_Z] * maTangent[AlongWith_X];
				maTangent[AlongWith_Y].normalize();
				break;
			case AlongWith_Y:
				break;
			}
		}

		const Vector& LerpKey::getTangent(const EAlongWith& eFlag) const
		{
			FASSERT(eFlag >= 0 && eFlag < AlongWith_Max);
			return maTangent[eFlag];
		}

		const TArray<Vector>& LerpKey::getTangent() const
		{
			return maTangent;
		}

		void LerpKey::copyOther(const LerpKey& other)
		{
			IRoot::operator = (other);
			mvPos = other.mvPos;
			mvStepFlag = other.mvStepFlag;
			maTangent = other.maTangent;
		}

		LerpKey LerpKey::sLoadLerpKeyFromString(const String& strLerpKey, float xRowStepFlag, float zColStepFlag)
		{
			LerpKey key;
			Vector vPos(0, 0, 0);
			TArray<Vector> aTangent(3);
			aTangent[0] = Vector::PXAxis;
			aTangent[1] = Vector::PYAxis;
			aTangent[2] = Vector::PZAxis;
			if (strLerpKey.isEmpty())
			{
				key.setLerpKey(vPos, FVector2(xRowStepFlag, zColStepFlag), aTangent);
				return key;
			}
			//
			TArray<String> strArray;
			strArray = strLerpKey.split("|");
			uint uSize = strArray.size();
			for (uint i = 0; i<uSize; i++)
			{
				if (0 == i)
				{
					vPos = Vector::fromString(strArray[i]);
				}
				else if (i >= 1 && i <= 3)
				{
					aTangent[i - 1] = Vector::fromString(strArray[i]);
				}
			}
			key.setLerpKey(vPos, FVector2(xRowStepFlag, zColStepFlag), aTangent);
			return key;
		}

		/*-----------------------------------------------------------
		class Lerp
		------------------------------------------------------------*/
		bool Lerp::sLerp(TArray<Vector> &aVector, const TArray<LerpKey>& aLerpKey, const EAlongWith& eFlag /* = AlongWith_X */, bool bNotChangeBoundVertex /* = true */)
		{
			aVector.clear();
			ulong uKeyNum = aLerpKey.size();
			FASSERT(uKeyNum > 1);
			FASSERT((eFlag == AlongWith_X) ? (aLerpKey[0].getStepFlag().X() < aLerpKey[uKeyNum - 1].getStepFlag().X()) : \
				(aLerpKey[0].getStepFlag().Y() < aLerpKey[uKeyNum - 1].getStepFlag().Y()));

			TArray<Vector> aTemp;
			ulong i = 0;
			for (i = 0; i<uKeyNum - 1; i++)
			{
				sTwoPointLerp(aTemp, aLerpKey[i], aLerpKey[i + 1], eFlag);
				aTemp.pop();
				aVector.add(aTemp);
			}
			aVector.addNotRepeat(aLerpKey[i].getPos());
			return true;
		}

		bool Lerp::sLerp(TArray<LerpKey> &aKeyOut, const TArray<LerpKey>& aLerpKey, const EAlongWith& eFlag /* = AlongWith_X */, bool bNotChangeBoundVertex /* = true */)
		{
			aKeyOut.clear();
			ulong uKeyNum = aLerpKey.size();
			FASSERT(uKeyNum > 1);
			FASSERT((eFlag == AlongWith_X) ? (aLerpKey[0].getStepFlag().X() < aLerpKey[uKeyNum - 1].getStepFlag().X()) : \
				(aLerpKey[0].getStepFlag().Y() < aLerpKey[uKeyNum - 1].getStepFlag().Y()));

			TArray<LerpKey> aTemp;
			ulong i = 0;
			for (i = 0; i<uKeyNum - 1; i++)
			{
				sTwoPointLerp(aTemp, aLerpKey[i], aLerpKey[i + 1], eFlag);
				aTemp.pop();
				aKeyOut.add(aTemp);
			}
			aKeyOut.addNotRepeat(aLerpKey[i]);
			return true;
		}

		bool Lerp::sTwoPointLerp(TArray<Vector> &aVector, const LerpKey& v1, const LerpKey& v2, const EAlongWith& eFlag /* = AlongWith_X */)
		{
			aVector.clear();
			float fStepFlag = 0;
			fStepFlag = (eFlag == AlongWith_X) ? (v2.getStepFlag().X() - v1.getStepFlag().X()) : \
				(v2.getStepFlag().Y() - v1.getStepFlag().Y());
			ulong uStep = (ulong)fStepFlag;
			FASSERT(uStep > 0);

			Vector v;
			Vector v_1 = v1.getPos();
			Vector t_1 = v1.getTangent(eFlag);
			Vector v_2 = v2.getPos();
			Vector t_2 = v2.getTangent(eFlag);
			float s = 0.f;
			aVector.addNotRepeat(v_1);
			for (ulong i = 1; i<uStep; i++)
			{
				s = ((float)i) / fStepFlag;
				v.hermite(v_1, t_1, v_2, t_2, s);
				aVector.addNotRepeat(v);
			}
			aVector.addNotRepeat(v_2);
			return true;
		}

		bool Lerp::sTwoPointLerp(TArray<LerpKey> &aKeyOut, const LerpKey& v1, const LerpKey& v2, const EAlongWith& eFlag /* = AlongWith_X */)
		{
			aKeyOut.clear();
			float fStepX = v1.getStepFlag().X();
			float fStepY = v1.getStepFlag().Y();
			float fStepFlag = 0;
			fStepFlag = (eFlag == AlongWith_X) ? (v2.getStepFlag().X() - v1.getStepFlag().X()) : \
				(v2.getStepFlag().Y() - v1.getStepFlag().Y());
			ulong uStep = (ulong)fStepFlag;
			FASSERT(uStep > 0);

			LerpKey vKey;
			Vector vPos, vTan;
			FVector2 vStep;
			Vector v_1 = v1.getPos();
			Vector t_1 = v1.getTangent(eFlag);
			Vector v_2 = v2.getPos();
			Vector t_2 = v2.getTangent(eFlag);
			float s = 0.f;
			aKeyOut.addNotRepeat(v1);
			for (ulong i = 1; i<uStep; i++)
			{
				s = ((float)i) / fStepFlag;
				vPos.hermite(v_1, t_1, v_2, t_2, s, &vTan);
				//vStep = (eFlag == AlongWith_X)? (FVector2(i,fStepY)) : (FVector2(fStepX,i));
				vStep = (eFlag == AlongWith_X) ? (FVector2(i + fStepX, fStepY)) : (FVector2(fStepX, i + fStepY));
				vKey.setLerpKey(vPos, vStep, vTan, eFlag);
				aKeyOut.addNotRepeat(vKey);
			}
			aKeyOut.addNotRepeat(v2);
			return true;
		}

		bool Lerp::sLerp(TDArray<Vector> &aPos, TDArray<Vector>* pTangentArray, const TArray<LerpKey>& aLerpKey, ulong uRow, ulong uCol, bool bNotChangeBoundVertex /* = true */)
		{
			aPos.clear();
			FASSERT(aLerpKey.size() >= 4);
			aPos.grow(uRow, uCol);

			FVector2 vStepFlag;
			ulong uX, uY;

			//ulong uFlagNum = uRow;//(uRow > uCol)? uCol : uRow;
			TArrayBool bHasDone(uRow);
			for (ulong uDone = 0; uDone<uRow; uDone++)
			{
				bHasDone[uDone] = false;
			}
			TArray<LerpKey> lerpKey = aLerpKey;
			lerpKey.sort();
			sCrossLerp(aPos, lerpKey, 0, 0, bHasDone, uRow, uCol);
			sCrossLerp(aPos, lerpKey, uRow - 1, uCol - 1, bHasDone, uRow, uCol);
			ulong uLerpKeySize = lerpKey.size();
			for (ulong i = 0; i<uLerpKeySize; i++)
			{
				FASSERT(lerpKey[i].getTangent().size() >= 3);
				vStepFlag = lerpKey[i].getStepFlag();
				uX = (ulong)vStepFlag.X();
				uY = (ulong)vStepFlag.Y();
				// cross lerp
				if ((uX == 0 || uY == uCol || uX == uRow || uY == 0))
					continue;
				sCrossLerp(aPos, lerpKey, uX, uY, bHasDone, uRow, uCol);
			}
			// finish lerp
			for (ulong uDone = 0; uDone<uRow; uDone++)
			{
				if (!bHasDone[uDone] && uDone <= uCol)
				{
					sCrossLerp(aPos, lerpKey, uDone, uDone, bHasDone, uRow, uCol);
				}
			}
			if (NULL != pTangentArray)
			{
				FASSERT(lerpKey.size() >= uRow * uCol);
				pTangentArray->grow(uRow * uCol, 3);
				for (ulong i = 0; i<lerpKey.size(); i++)
				{
					FASSERT(lerpKey[i].getTangent().size() >= 3);
					vStepFlag = lerpKey[i].getStepFlag();
					uX = (ulong)vStepFlag.X();
					uY = (ulong)vStepFlag.Y();
					(*pTangentArray)[uX * uRow + uY][AlongWith_X] = lerpKey[i].getTangent(AlongWith_X);
					(*pTangentArray)[uX * uRow + uY][AlongWith_Y] = lerpKey[i].getTangent(AlongWith_Y);
					(*pTangentArray)[uX * uRow + uY][AlongWith_Z] = lerpKey[i].getTangent(AlongWith_Z);
				}
			}
			//// save normal
			//if(NULL != pNormal)
			//{
			//	FASSERT(lerpKey.size() >= uRow * uCol);
			//	pNormal->grow(uRow,uCol);
			//	for(ulong i=0; i<lerpKey.size(); i++)
			//	{
			//		FASSERT(lerpKey[i].getTangent().size() >= 3);
			//		vStepFlag = lerpKey[i].getStepFlag();
			//		uX = (ulong)vStepFlag.X();
			//		uY = (ulong)vStepFlag.Y();
			//		(*pNormal)[uX][uY] = lerpKey[i].getTangent(AlongWith_Y);
			//	}
			//}
			return true;
		}

		bool Lerp::sFractal(TDArray<Vector> &aPos, TDArray<Vector>* pTangentArray, const TArray<LerpKey>& aLerpKey, ulong uRow, ulong uCol, bool bNotChangeBoundVertex /* = true */)
		{
			FASSERT(uRow >= 3 && (uRow % 2 == 1) && uRow == uCol);
			FASSERT(aLerpKey.size() >= 4);
			if (aPos.getRow() != uRow || aPos.getCol() != uCol)
			{
				aPos.grow(uRow, uCol);
			}
			TArray<LerpKey> lerpKey = aLerpKey;
			lerpKey.sort();
			uint uDepth = 0;
			float scaleMax = 10.0;

			sFractal(&aPos, pTangentArray, &lerpKey, 0, 0, uRow - 1, uDepth, scaleMax, bNotChangeBoundVertex);
			const uint uSmoothCnt = 2;
			for (uint i = 0; i<uSmoothCnt; i++)
			{
				sSmooth(&aPos, aLerpKey);
			}

			if (NULL != pTangentArray)
			{
				pTangentArray->grow(uRow * uCol, 3);
				for (ulong i = 0; i<aPos.getRow(); i++)
				{
					for (ulong j = 0; j<aPos.getCol(); j++)
					{
						(*pTangentArray)[i * uCol + j][AlongWith_X] = Vector::PXAxis;	// bi-Normal
						(*pTangentArray)[i * uCol + j][AlongWith_Y] = Vector::PYAxis;	// Normal
						(*pTangentArray)[i * uCol + j][AlongWith_Z] = Vector::PZAxis;	// Tangent
					}
				}
			}
			return true;
		}

		bool Lerp::sFractal(TDArray<Vector>* pPosArray, TDArray<Vector>* pTangentArray, TArray<LerpKey>* pLerpKey, ulong uFromRowIndex, ulong uFromColIndex, ulong uSpan, uint uDepth, float scaleMax, bool bNotChangeBoundVertex /* = true */)
		{
			FCHECK(uSpan >= 2 && (uSpan % 2 == 0), false);
			FASSERT(NULL != pPosArray && uFromRowIndex >= 0 && uFromRowIndex + uSpan < pPosArray->getRow() && uFromColIndex >= 0 && uFromColIndex + uSpan < pPosArray->getCol());

			TArray<float> aOutPos(5), aInPos(4);
			TArray<FVector2> aKeyPoint;
			aInPos[0] = pPosArray->getAt(uFromRowIndex, uFromColIndex).y();
			aInPos[1] = pPosArray->getAt(uFromRowIndex, uFromColIndex + uSpan).y();
			aInPos[2] = pPosArray->getAt(uFromRowIndex + uSpan, uFromColIndex).y();
			aInPos[3] = pPosArray->getAt(uFromRowIndex + uSpan, uFromColIndex + uSpan).y();
			LerpKey lk;
			FVector2 kp;
			for (ulong i = 0; i<pLerpKey->size(); i++)
			{
				lk = (*pLerpKey)[i];
				if (lk.getStepFlag().X() == uFromRowIndex + uSpan / 2 && lk.getStepFlag().Y() == uFromColIndex + uSpan / 2)
				{
					kp.SetXY(0, lk.getPos().y());
					aKeyPoint.add(kp);
					pLerpKey->remove(lk);
				}
				else if (lk.getStepFlag().X() == uFromRowIndex && lk.getStepFlag().Y() == uFromColIndex + uSpan / 2)
				{
					kp.SetXY(1, lk.getPos().y());
					aKeyPoint.add(kp);
					pLerpKey->remove(lk);
				}
				else if (lk.getStepFlag().X() == uFromRowIndex + uSpan && lk.getStepFlag().Y() == uFromColIndex + uSpan / 2)
				{
					kp.SetXY(2, lk.getPos().y());
					aKeyPoint.add(kp);
					pLerpKey->remove(lk);
				}
				else if (lk.getStepFlag().X() == uFromRowIndex + uSpan / 2 && lk.getStepFlag().Y() == uFromColIndex + uSpan)
				{
					kp.SetXY(3, lk.getPos().y());
					aKeyPoint.add(kp);
					pLerpKey->remove(lk);
				}
				else if (lk.getStepFlag().X() == uFromRowIndex + uSpan / 2 && lk.getStepFlag().Y() == uFromColIndex)
				{
					kp.SetXY(4, lk.getPos().y());
					aKeyPoint.add(kp);
					pLerpKey->remove(lk);
				}
			}
			sFractalOnce(aOutPos, aInPos, aKeyPoint, uDepth, scaleMax, bNotChangeBoundVertex);
			Vector vPos;
			// center
			vPos = pPosArray->getAt(uFromRowIndex + uSpan / 2, uFromColIndex + uSpan / 2);
			vPos.y(aOutPos[0]);
			pPosArray->setAt(uFromRowIndex + uSpan / 2, uFromColIndex + uSpan / 2, vPos);
			if (!bNotChangeBoundVertex)
			{
				// left
				vPos = pPosArray->getAt(uFromRowIndex, uFromColIndex + uSpan / 2);
				vPos.y(aOutPos[1]);
				pPosArray->setAt(uFromRowIndex, uFromColIndex + uSpan / 2, vPos);
				// right
				vPos = pPosArray->getAt(uFromRowIndex + uSpan, uFromColIndex + uSpan / 2);
				vPos.y(aOutPos[1]);
				pPosArray->setAt(uFromRowIndex + uSpan, uFromColIndex + uSpan / 2, vPos);
				// bottom
				vPos = pPosArray->getAt(uFromRowIndex + uSpan / 2, uFromColIndex + uSpan);
				vPos.y(aOutPos[1]);
				pPosArray->setAt(uFromRowIndex + uSpan / 2, uFromColIndex + uSpan, vPos);
				//
				vPos = pPosArray->getAt(uFromRowIndex + uSpan / 2, uFromColIndex);
				vPos.y(aOutPos[1]);
				pPosArray->setAt(uFromRowIndex + uSpan / 2, uFromColIndex, vPos);
			}
			//
			uSpan *= 0.5f;//uSpan /= 2;
			uDepth++;
			sFractal(pPosArray, pTangentArray, pLerpKey, uFromRowIndex, uFromColIndex, uSpan, uDepth, scaleMax, bNotChangeBoundVertex);
			sFractal(pPosArray, pTangentArray, pLerpKey, uFromRowIndex + uSpan, uFromColIndex, uSpan, uDepth, scaleMax, bNotChangeBoundVertex);
			sFractal(pPosArray, pTangentArray, pLerpKey, uFromRowIndex, uFromColIndex + uSpan, uSpan, uDepth, scaleMax, bNotChangeBoundVertex);
			sFractal(pPosArray, pTangentArray, pLerpKey, uFromRowIndex + uSpan, uFromColIndex + uSpan, uSpan, uDepth, scaleMax, bNotChangeBoundVertex);
			//
			return true;
		}

		void Lerp::sSmooth(TDArray<Vector>* pPosArray, const TArray<LerpKey>& aLerpKey)
		{
			FASSERT(NULL != pPosArray && pPosArray->getRow() > 0 && pPosArray->getCol() > 0);
			TArray<LerpKey> lerpKey(aLerpKey);
			Vector vPos;
			float val;
			bool bKeyPoint = false;
			const ulong uRow = pPosArray->getRow();
			const ulong uCol = pPosArray->getCol();
			for (ulong i = 1; i<uRow - 1; i++)
			{
				for (ulong j = 1; j<uCol - 1; j++)
				{
					val = pPosArray->getAt(i - 1, j - 1).y() + pPosArray->getAt(i, j - 1).y() + pPosArray->getAt(i + 1, j - 1).y()
						+ pPosArray->getAt(i - 1, j).y() + pPosArray->getAt(i, j).y() + pPosArray->getAt(i + 1, j).y()
						+ pPosArray->getAt(i - 1, j + 1).y() + pPosArray->getAt(i, j + 1).y() + pPosArray->getAt(i + 1, j + 1).y();
					val /= 9.0;

					vPos = pPosArray->getAt(i, j);
					vPos.y(val);
					pPosArray->setAt(i, j, vPos);
				}
			}
		}

		bool Lerp::sCrossLerp(TDArray<Vector> &aVector, TArray<LerpKey>& aLerpKey, ulong uX, ulong uY, TArrayBool &bHasDone, ulong uRow, ulong uCol)
		{
			FASSERT(uX < aVector.getRow() && uY < aVector.getCol());

			FVector2 vCrossStep;
			ulong uCrossX, uCrossY;
			TArray<LerpKey> keyXAxis, keyYAxis;
			ulong uFlagNum = uRow;//(uRow > uCol)? uCol : uRow;

								   // cross lerp
			keyXAxis.clear();
			keyYAxis.clear();
			for (ulong j = 0; j<aLerpKey.size(); j++)
			{
				vCrossStep = aLerpKey[j].getStepFlag();
				uCrossX = (ulong)vCrossStep.X();
				uCrossY = (ulong)vCrossStep.Y();
				if (uCrossX == uX)
				{
					keyYAxis.addNotRepeat(aLerpKey[j]);
				}
				if (uCrossY == uY)
				{
					keyXAxis.addNotRepeat(aLerpKey[j]);
				}
			}
			// sort
			keyXAxis.sort();
			keyYAxis.sort();
			// lerp with X-Axis
			TArray<LerpKey> crossKey;
			Lerp::sLerp(crossKey, keyXAxis, AlongWith_X);
			for (ulong j = 0; j<crossKey.size(); j++)
			{
				aVector[j][uY] = crossKey[j].getPos();
				aLerpKey.addNotRepeat(crossKey[j]);
			}
			// lerp with Y-Axis
			Lerp::sLerp(crossKey, keyYAxis, AlongWith_Z);
			for (ulong j = 0; j<crossKey.size(); j++)
			{
				//if(j != uCrossY)
				aVector[uX][j] = crossKey[j].getPos();
				aLerpKey.addNotRepeat(crossKey[j]);
			}
			bHasDone[uX] = true;

			return true;
		}

		bool Lerp::sFractalOnce(TArray<float> &aOutPos, const TArray<float>& aInPos, const TArray<FVector2>& aKeyPoint, uint uDepth, float scaleMax /* = 1.f */, bool bNotChangeBoundPos /* = true */)
		{
			FCHECK(aInPos.size() >= 4 && uDepth >= 0 && scaleMax >= 0.f, false);
			if (aOutPos.size() < 4)
			{
				aOutPos.resize(4);
			}
			const uint uNone = 5;
			// 0,1,2,3,4 [center,left,right,bottom,top]
			uint uKey[5] = { uNone, uNone, uNone, uNone, uNone };
			uint uX = uNone;
			for (uint i = 0; i<aKeyPoint.size(); i++)
			{
				uX = aKeyPoint[i].X();
				if (uX >= 0 && uX < 5)
				{
					uKey[uX] = i;
				}
			}
			float fFactor = 1.f / pow(2.f, (float)uDepth);
			fFactor *= scaleMax;
			float fDelta = 1.f;
			// center
			if (uKey[0] >= 0 && uKey[0] < uNone)
			{
				aOutPos[0] = aKeyPoint[uKey[0]].Y();
			}
			else
			{
				fDelta = (rand() % 2 == 0) ? 1.f : -1.f;
				fDelta *= 0.001f * (rand() % 1000) * fFactor;
				aOutPos[0] = (aInPos[0] + aInPos[1] + aInPos[2] + aInPos[3]) / 4.f + fDelta;
			}
			if (bNotChangeBoundPos)
			{
				aOutPos[1] = aOutPos[2] = aOutPos[3] = Maths::maxSizeFloat();
				return true;
			}

			// left
			if (uKey[1] >= 0 && uKey[1] < uNone)
			{
				aOutPos[1] = aKeyPoint[uKey[1]].Y();
			}
			else
			{
				fDelta = (rand() % 2 == 0) ? 1.f : -1.f;
				fDelta *= 0.001f * (rand() % 1000) * fFactor;
				aOutPos[1] = (aInPos[0] + aInPos[1] + aOutPos[0] + aInPos[0]) / 4.f + fDelta;
			}
			// right
			if (uKey[2] >= 0 && uKey[2] < uNone)
			{
				aOutPos[2] = aKeyPoint[uKey[2]].Y();
			}
			else
			{
				fDelta = (rand() % 2 == 0) ? 1.f : -1.f;
				fDelta *= 0.001f * (rand() % 1000) * fFactor;
				aOutPos[2] = (aInPos[2] + aInPos[3] + aOutPos[0] + aInPos[0]) / 4.f + fDelta;
			}
			// bottom
			if (uKey[3] >= 0 && uKey[3] < uNone)
			{
				aOutPos[3] = aKeyPoint[uKey[3]].Y();
			}
			else
			{
				fDelta = (rand() % 2 == 0) ? 1.f : -1.f;
				fDelta *= 0.001f * (rand() % 1000) * fFactor;
				aOutPos[3] = (aInPos[1] + aInPos[3] + aOutPos[0] + aInPos[0]) / 4.f + fDelta;
			}
			// top
			if (uKey[4] >= 0 && uKey[4] < uNone)
			{
				aOutPos[4] = aKeyPoint[uKey[4]].Y();
			}
			else
			{
				fDelta = (rand() % 2 == 0) ? 1.f : -1.f;
				fDelta *= 0.001f * (rand() % 1000) * fFactor;
				aOutPos[4] = (aInPos[0] + aInPos[2] + aOutPos[0] + aInPos[0]) / 4.f + fDelta;
			}
			return true;
		}

		bool Lerp::fractal(TDArray<float>* vHeight, uint uGridPower, uint uSmoothTimes /* = 1 */, bool bKeepBoundLeft /* = false */, bool bKeepBoundRight /* = false */, bool bKeepBoundBottom /* = false */, bool bKeepBoundTop /* = false */)
		{
			if (nullptr == vHeight || uGridPower < 1)
				return false;
			const uint cx = pow(2, uGridPower);
			const uint cy = cx;
			if (vHeight->getRow() < cx + 1 || vHeight->getCol() < cy + 1)
				vHeight->grow(cx + 1, cy + 1);
			const float keyVal[4] = { vHeight->getAt(0, 0), vHeight->getAt(cx, 0), vHeight->getAt(0, cy), vHeight->getAt(cx, cy) };
			vHeight->setAt(0, 0, (keyVal[0] >= -1.0001f && keyVal[0] <= 1.0001f) ? keyVal[0] : 0.f);
			vHeight->setAt(cx, 0, (keyVal[1] >= -1.0001f && keyVal[1] <= 1.0001f) ? keyVal[1] : 0.f);
			vHeight->setAt(0, cy, (keyVal[2] >= -1.0001f && keyVal[2] <= 1.0001f) ? keyVal[2] : 0.f);
			vHeight->setAt(cx, cy, (keyVal[3] >= -1.0001f && keyVal[3] <= 1.0001f) ? keyVal[3] : 0.f);
			// fractal
			fractal(vHeight, Point2D(0, 0), Point2D(cx, cy), 0);
			// smooth
			for (uint i = 0; i < uSmoothTimes; i++)
				smooth(vHeight, bKeepBoundLeft, bKeepBoundRight, bKeepBoundBottom, bKeepBoundTop);
			return true;
		}

		bool Lerp::fractal(TDArray<float>* vHeight, const Point2D& pitFrom, const Point2D& pitTo, uint uDepth)
		{
			if (nullptr == vHeight || pitTo.x - pitFrom.x < 2 || pitTo.y - pitFrom.y < 2)
				return false;
			const Point2D center((pitTo.x + pitFrom.x) / 2, (pitTo.y + pitFrom.y) / 2);
			const Point2D left(pitFrom.x, center.y);
			const Point2D right(pitTo.x, center.y);
			const Point2D bottom(center.x, pitTo.y);
			const Point2D top(center.x, pitFrom.y);

			float factor = 1.f / pow(2.f, uDepth);
			//fFactor *= scaleMax;
			float delta = 1.f;

			const float vFr = vHeight->getAt(pitFrom.x, pitFrom.y);
			const float vTo = vHeight->getAt(pitTo.x, pitTo.y);
			const float vLB = vHeight->getAt(pitFrom.x, pitTo.y);
			const float vRT = vHeight->getAt(pitTo.x, pitFrom.y);

			float vC = 0.f;//delta + 0.25f * (vFr + vTo + vLB + vRT);

			float keyVal = 0.f;
			keyVal = vHeight->getAt(center.x, center.y);
			if (keyVal < -1.f || keyVal > 1.f)
			{
				delta = (rand() % 2 == 0) ? 1.f : -1.f;
				delta *= 0.00002f * (rand() % 50000) * factor;
				vC = delta + 0.25f * (vFr + vTo + vLB + vRT);
				vHeight->setAt(center.x, center.y, vC);
			}
			else
			{
				vC = keyVal;
			}

			keyVal = vHeight->getAt(left.x, left.y);
			if (keyVal < -1.f || keyVal > 1.f)
			{
				delta = (rand() % 2 == 0) ? 1.f : -1.f;
				delta *= 0.00002f * (rand() % 50000) * factor;
				vHeight->setAt(left.x, left.y, delta + 0.25f * (vC + vC + vFr + vLB));
			}

			keyVal = vHeight->getAt(right.x, right.y);
			if (keyVal < -1.f || keyVal > 1.f)
			{
				delta = (rand() % 2 == 0) ? 1.f : -1.f;
				delta *= 0.00002f * (rand() % 50000) * factor;
				vHeight->setAt(right.x, right.y, delta + 0.25f * (vC + vC + vTo + vRT));
			}

			keyVal = vHeight->getAt(bottom.x, bottom.y);
			if (keyVal < -1.f || keyVal > 1.f)
			{
				delta = (rand() % 2 == 0) ? 1.f : -1.f;
				delta *= 0.00002f * (rand() % 50000) * factor;
				vHeight->setAt(bottom.x, bottom.y, delta + 0.25f * (vC + vC + vTo + vLB));
			}

			keyVal = vHeight->getAt(top.x, top.y);
			if (keyVal < -1.f || keyVal > 1.f)
			{
				delta = (rand() % 2 == 0) ? 1.f : -1.f;
				delta *= 0.00002f * (rand() % 50000) * factor;
				vHeight->setAt(top.x, top.y, delta + 0.25f * (vC + vC + vFr + vRT));
			}

			// recursion
			uDepth++;
			fractal(vHeight, pitFrom, center, uDepth);
			fractal(vHeight, top, right, uDepth);
			fractal(vHeight, left, bottom, uDepth);
			fractal(vHeight, center, pitTo, uDepth);

			return true;
		}

		void Lerp::smooth(TDArray<float>* vHeight, bool bKeepBoundLeft /* = false */, bool bKeepBoundRight /* = false */, bool bKeepBoundBottom /* = false */, bool bKeepBoundTop /* = false */)
		{
			if (nullptr == vHeight || vHeight->getRow() < 3 || vHeight->getCol() < 3)
				return;
			const ulong uRow = vHeight->getRow();
			const ulong uCol = vHeight->getCol();
			const ulong uRowFr = (bKeepBoundLeft) ? 1 : 0;
			const ulong uRowTo = (bKeepBoundRight) ? uRow - 1 : uRow;
			const ulong uColFr = (bKeepBoundBottom) ? 1 : 0;
			const ulong uColTo = (bKeepBoundTop) ? uCol - 1 : uCol;
			float val = 0.f;
			for (ulong i = uRowFr; i < uRowTo; i++)
			{
				for (ulong j = uColFr; j < uColTo; j++)
				{
					if (i == 0 && j == 0)
					{
						val = vHeight->getAt(0, 0) + vHeight->getAt(0, 1) + vHeight->getAt(1, 0) + vHeight->getAt(1, 1);
						val *= 0.25f;// /= 4.f;
					}
					else if (i == 0 && j == uCol - 1)
					{
						val = vHeight->getAt(0, j) + vHeight->getAt(0, j - 1) + vHeight->getAt(1, j) + vHeight->getAt(1, j - 1);
						val *= 0.25f;// /= 4.f;
					}
					else if (i == uRow - 1 && j == 0)
					{
						val = vHeight->getAt(i, 0) + vHeight->getAt(i - 1, 0) + vHeight->getAt(i, 1) + vHeight->getAt(i - 1, 1);
						val *= 0.25f;// /= 4.f;
					}
					else if (i == uRow - 1 && j == uCol - 1)
					{
						val = vHeight->getAt(i, j) + vHeight->getAt(i, j - 1) + vHeight->getAt(i - 1, j) + vHeight->getAt(i - 1, j - 1);
						val *= 0.25f;// /= 4.f;
					}
					else if (i == 0)
					{
						val = vHeight->getAt(0, j) + vHeight->getAt(0, j - 1) + vHeight->getAt(0, j + 1) + vHeight->getAt(1, j) + vHeight->getAt(1, j - 1) + vHeight->getAt(1, j + 1);
						val /= 6.f;
					}
					else if (j == 0)
					{
						val = vHeight->getAt(i, 0) + vHeight->getAt(i - 1, 0) + vHeight->getAt(i + 1, 0) + vHeight->getAt(i, 1) + vHeight->getAt(i - 1, 1) + vHeight->getAt(i + 1, 1);
						val /= 6.f;
					}
					else if (i == uRow - 1)
					{
						val = vHeight->getAt(i, j) + vHeight->getAt(i, j - 1) + vHeight->getAt(i, j + 1) + vHeight->getAt(i - 1, j) + vHeight->getAt(i - 1, j - 1) + vHeight->getAt(i - 1, j + 1);
						val /= 6.f;
					}
					else if (j == uCol - 1)
					{
						val = vHeight->getAt(i, j) + vHeight->getAt(i - 1, j) + vHeight->getAt(i + 1, j) + vHeight->getAt(i, j - 1) + vHeight->getAt(i - 1, j - 1) + vHeight->getAt(i + 1, j - 1);
						val /= 6.f;
					}
					else //if
					{
						val = vHeight->getAt(i - 1, j - 1) + vHeight->getAt(i, j - 1) + vHeight->getAt(i + 1, j - 1)
							+ vHeight->getAt(i - 1, j) + vHeight->getAt(i, j) + vHeight->getAt(i + 1, j)
							+ vHeight->getAt(i - 1, j + 1) + vHeight->getAt(i, j + 1) + vHeight->getAt(i + 1, j + 1);
						val /= 9.f;
					}
					//
					Maths::saturate<float>(val, -1.f, 1.f);
					vHeight->setAt(i, j, val);
				}
			}
		}

		///*-----------------------------------------------------------
		//class Maths
		//------------------------------------------------------------*/
		//Maths::Maths()
		//{
		//}

		//Maths::~Maths()
		//{
		//}

		//void Maths::copyOther(const Maths& other)
		//{

		//}

		//bool Maths::doCreate(void* pData /* = nullptr */)
		//{

		//}

		//void Maths::doRelease()
		//{

		//}


	}
}