/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/maths2d.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class FVector2
		------------------------------------------------------------*/
		const FVector2 FVector2::PXAxis = FVector2(1.f, 0.f);
		const FVector2 FVector2::PYAxis = FVector2(0.f, 1.f);
		const FVector2 FVector2::NXAxis = FVector2(-1.f, 0.f);
		const FVector2 FVector2::NYAxis = FVector2(0.f, -1.f);
		const FVector2 FVector2::Origin = FVector2(0.f, 0.f);

		FVector2::FVector2()
			:mx(0.f)
			, my(0.f)
		{
		}

		FVector2::~FVector2()
		{
			mx = my = 0.f;
		}

		FVector2::FVector2(float x, float y)
		{
			mx = x;
			my = y;
		}

		FVector2::FVector2(const FVector2& other)
		{
			mx = other.mx;
			my = other.my;
		}

		FVector2& FVector2::operator = (const FVector2& other)
		{
			mx = other.X();
			my = other.Y();
			return *this;
		}

		FVector2 FVector2::operator + (const FVector2& other) const
		{
			return FVector2(mx + other.mx, my + other.my);
		}

		FVector2 FVector2::operator - (const FVector2& other) const
		{
			return FVector2(mx - other.mx, my - other.my);
		}

		FVector2 FVector2::operator * (float scale) const
		{
			return FVector2(scale * mx, scale * my);
		}

		const FVector2& FVector2::operator += (const FVector2& other)
		{
			mx += other.mx;
			my += other.my;
			return *this;
		}

		const FVector2& FVector2::operator -= (const FVector2& other)
		{
			mx -= other.mx;
			my -= other.my;
			return *this;
		}

		bool FVector2::operator == (const FVector2& other) const
		{
			//return (mx == other.mx && my == other.my);
			return (Maths::isNear(mx, other.mx) && Maths::isNear(my, other.my));
		}

		bool FVector2::operator != (const FVector2& other) const
		{
			return !(*this == other);
		}

		float FVector2::getLength() const
		{
			return sqrt(mx * mx + my * my);
		}

		float FVector2::getLengthSquare() const
		{
			return (mx * mx + my * my);
		}

		bool FVector2::IsZero() const
		{
			float magnitude = getLength();
			return Maths::isZero(magnitude);
		}
		bool FVector2::IsNearZero() const
		{
			float magnitude = getLength();
			return  Maths::isNearZero(magnitude);
		}

		bool FVector2::IsAllVectorPositive() const
		{
			return (mx > Maths::tolerance() && my > Maths::tolerance());
		}

		bool FVector2::IsAllVectorNegative() const
		{
			return (mx < Maths::tolerance() && my < Maths::tolerance());
		}

		void FVector2::scale(float scale)
		{
			mx *= scale;
			my *= scale;
		}

		void FVector2::SetX(float x)
		{
			mx = x;
		}

		void FVector2::SetY(float y)
		{
			my = y;
		}

		void FVector2::SetXY(float x, float y)
		{
			mx = x;
			my = y;
		}

		float FVector2::X() const
		{
			return mx;
		}

		float FVector2::Y() const
		{
			return my;
		}

		void  FVector2::XY(float& x, float& y) const
		{
			x = mx;
			y = my;
		}

		String FVector2::toString(bool bActualValue /* = true */) const
		{
			float x = mx;
			float y = my;
			if (bActualValue)
			{
				x = FUnit::getActualValue(x);
				y = FUnit::getActualValue(y);
			}

			String strRe;// ("%.4f,%.4f", x, y);
			return strRe;
		}

		FVector2 FVector2::sFromString(const String& strVector2)
		{
			FVector2 vec2;
			if (strVector2.compareIgnoreCase("PXAxis"))
			{
				vec2 = FVector2::PXAxis;
			}
			else if (strVector2.compareIgnoreCase("PYAxis"))
			{
				vec2 = FVector2::PYAxis;
			}
			else if (strVector2.compareIgnoreCase("NXAxis"))
			{
				vec2 = FVector2::NXAxis;
			}
			else if (strVector2.compareIgnoreCase("NYAxis"))
			{
				vec2 = FVector2::NYAxis;
			}
			else if (strVector2.compareIgnoreCase("Origin"))
			{
				vec2 = FVector2::Origin;
			}
			else
			{
				TArray<String> strArray;
				strArray = strVector2.split(",");
				uint uSum = strArray.size();
				//FASSERT(uSum >= 3);
				float fVal[2] = { 0.f, 0.f };
				for (uint i = 0; i<uSum && i<2; i++)
				{
					if (!strArray[i].isDigital(fVal[i]))
					{
						fVal[i] = 0.f;
					}
				}
				vec2.SetXY(fVal[0], fVal[1]);
			}
			return vec2;
		}

		/*-----------------------------------------------------------
		class Rect
		------------------------------------------------------------*/
		Rect::Rect()
			: mvLeftTop(0, 0)
			, mvRightBottom(0, 0)
		{
		}

		Rect::~Rect()
		{
		}

		Rect::Rect(const Rect& other)
		{
			copyOther(other);
		}

		Rect::Rect(float fLeft, float fTop, float fWidth, float fHeight)
		{
			setLeftTop(fLeft, fTop);
			setWidthHeight(fWidth, fHeight, Orientation_2D_LeftTop);
		}

		Rect& Rect::operator = (const Rect& other)
		{
			copyOther(other);
			return *this;
		}

		Rect Rect::operator + (const Rect& other) const
		{
			Rect rc(*this);
			rc += other;
			return rc;
		}

		Rect& Rect::operator += (const Rect& other)
		{
			float dx, dy;
			other.getWidthHeight(dx, dy);
			dx += mvRightBottom.X();
			dy += mvRightBottom.Y();
			mvRightBottom.SetXY(dx, dy);
			return *this;
		}

		bool Rect::operator == (const Rect& other) const
		{
			return (mvLeftTop == other.mvLeftTop	\
				&& mvRightBottom == other.mvRightBottom);
		}

		bool Rect::operator != (const Rect& other) const
		{
			return !(*this == other);
		}

		void Rect::copyOther(const Rect& other)
		{
			IRoot::operator = (other);
			float l, t, r, b;
			other.getBound(l, t, r, b);
			setBound(l, t, r, b);
		}

		bool Rect::doCreate(void* pInitData /* = nullptr */)
		{
			mvLeftTop.SetXY(0.f, 0.f);
			mvRightBottom.SetXY(0.f, 0.f);
			return true;
		}

		void Rect::doDestroy()
		{
			mvLeftTop.SetXY(0.f, 0.f);
			mvRightBottom.SetXY(0.f, 0.f);
		}

		void Rect::offset(float dx, float dy)
		{
			float x = 0.f, y = 0.f;
			x = mvLeftTop.X();
			y = mvLeftTop.Y();
			mvLeftTop.SetXY(x + dx, y + dy);
			x = mvRightBottom.X();
			y = mvRightBottom.Y();
			mvRightBottom.SetXY(x + dx, y + dy);
		}

		void Rect::offsetLeft(float fMultiple /* = 1 */)
		{
			FASSERT(fMultiple > 0.f);
			float dx, dy;
			getWidthHeight(dx, dy);
			dx *= -fMultiple;
			dy = 0.f;
			offset(dx, dy);
		}

		void Rect::offsetRight(float fMultiple /* = 1 */)
		{
			FASSERT(fMultiple > 0.f);
			float dx, dy;
			getWidthHeight(dx, dy);
			dx *= fMultiple;
			dy = 0.f;
			offset(dx, dy);
		}

		void Rect::offsetUp(float fMultiple /* = 1 */)
		{
			FASSERT(fMultiple > 0.f);
			float dx, dy;
			getWidthHeight(dx, dy);
			dx = 0.f;
			dy *= -fMultiple;
			offset(dx, dy);
		}

		void Rect::offsetDown(float fMultiple /* = 1 */)
		{
			FASSERT(fMultiple > 0.f);
			float dx, dy;
			getWidthHeight(dx, dy);
			dx = 0.f;
			dy *= fMultiple;
			offset(dx, dy);
		}

		void Rect::resize(float dxSize, float dySize, bool bOffset /* = true */)
		{
			if (bOffset)
			{
				dxSize += mvRightBottom.X();
				dySize += mvRightBottom.Y();
			}
			else
			{
				dxSize += mvLeftTop.X();
				dySize += mvLeftTop.Y();
			}
			mvRightBottom.SetXY(dxSize, dySize);
		}

		void Rect::scale(float dx, float dy, const EnumOrientation2D& eOriente /* = Orientation_2D_Center */)
		{
			;
		}

		float Rect::getSquare() const
		{
			float cx = 0, cy = 0;
			getWidthHeight(cx, cy);
			CHECK_EXP(cx >= 0 && cy >= 0, -1.f);
			return cx * cy;
		}

		float Rect::getCircumference() const
		{
			float cx = 0, cy = 0;
			getWidthHeight(cx, cy);
			CHECK_EXP(cx >= 0 && cy >= 0, -1.f);
			return 2 * (cx + cy);
		}

		bool Rect::isZeroSquare() const
		{
			return getSquare() == 0;
		}

		bool Rect::isZeroCircumference() const
		{
			return getCircumference() == 0;
		}

		bool Rect::isContain(const FPoint2& point) const
		{
			float l, t, r, b;
			getBound(l, t, r, b);
			return (point.X() >= l && point.X() <= r && point.Y() >= t && point.Y() <= b);
		}

		bool Rect::isContain(const Rect& other) const
		{
			float l, t, r, b;
			float subL, subT, subR, subB;
			getBound(l, t, r, b);
			other.getBound(subL, subT, subR, subB);
			return (*this == other)	\
				|| (l <= subL && t <= subT && r >= subR && b >= subB);
		}

		void Rect::setBound(float fLeft, float fTop, float fRight, float fBottom)
		{
			mvLeftTop.SetXY(fLeft, fTop);
			mvRightBottom.SetXY(fRight, fBottom);
		}

		void Rect::getBound(float &fLeft, float &fTop, float &fRight, float &fBottom) const
		{
			mvLeftTop.XY(fLeft, fTop);
			mvRightBottom.XY(fRight, fBottom);
		}

		void Rect::setLeftTop(float fLeft, float fTop)
		{
			mvLeftTop.SetXY(fLeft, fTop);
		}

		void Rect::setRightBottom(float fRight, float fBottom)
		{
			mvRightBottom.SetXY(fRight, fBottom);
		}

		void Rect::getLeftTop(float &fLeft, float &fTop) const
		{
			mvLeftTop.XY(fLeft, fTop);
		}

		void Rect::getRightBottom(float &fRight, float &fBottom) const
		{
			mvRightBottom.XY(fRight, fBottom);
		}

		void Rect::setLeft(float fLeft)
		{
			mvLeftTop.SetX(fLeft);
		}

		void Rect::setTop(float fTop)
		{
			mvLeftTop.SetY(fTop);
		}

		void Rect::setRight(float fRight)
		{
			mvRightBottom.SetX(fRight);
		}

		void Rect::setBottom(float fBottom)
		{
			mvRightBottom.SetY(fBottom);
		}

		void Rect::reset(float x, float y, float width, float height)
		{
			if (width >= 0 && height >= 0)
			{
				mvLeftTop.SetXY(x, y);
				mvRightBottom.SetXY(x + width, y + height);
			}
		}

		float Rect::getLeft() const
		{
			return mvLeftTop.X();
		}

		float Rect::getTop() const
		{
			return mvLeftTop.Y();
		}

		float Rect::getRight() const
		{
			return mvRightBottom.X();
		}

		float Rect::getBottom() const
		{
			return mvRightBottom.Y();
		}

		FVector2 Rect::getCenter() const
		{
			float l, t, r, b;
			getBound(l, t, r, b);
			return FVector2(l + (r - l) / 2.f, t + (b - t) / 2.f);
		}

		void Rect::getUIViewportCoord(FVector2 &leftBottom, FVector2 &leftTop, FVector2 &rightTop, FVector2 &rightBottom, uint uWidth, uint uHeight, bool bAutoAdjust /* = false */) const
		{
			getUIViewportCoord(&leftBottom, &leftTop, &rightTop, &rightBottom, uWidth, uHeight, bAutoAdjust);
		}

		void Rect::getUIViewportCoord(FVector2* leftBottom, FVector2* leftTop, FVector2* rightTop, FVector2* rightBottom, uint uWidth, uint uHeight, bool bAutoAdjust /* = false */) const
		{
			float l, t, r, b;
			getBound(l, t, r, b);
			if (bAutoAdjust)
			{
				if (l < 0.f)
					l = 0.f;
				if (t < 0.f)
					t = 0.f;
				if (r >(float)uWidth)
					r = (float)uWidth;
				if (b >(float)uHeight)
					b = (float)uHeight;
			}
			//
			l = -1.f + 2.f * l / (float)uWidth;
			r = -1.f + 2.f * r / (float)uWidth;
			t = 1.f - 2.f * t / (float)uHeight;
			b = 1.f - 2.f * b / (float)uHeight;
			//
			if (NULL != leftBottom)
			{
				leftBottom->SetXY(l, b);
			}
			if (NULL != leftTop)
			{
				leftTop->SetXY(l, t);
			}
			if (NULL != rightTop)
			{
				rightTop->SetXY(r, t);
			}
			if (NULL != rightBottom)
			{
				rightBottom->SetXY(r, b);
			}
		}

		void Rect::setPos(const FVector2& vPos)
		{
			float dx = vPos.X() - mvLeftTop.X();
			float dy = vPos.Y() - mvLeftTop.Y();
			offset(dx, dy);
		}

		void Rect::setWidthHeight(float fWidth, float fHeight, const EnumOrientation2D& orientation /* = Orientation_2D_LeftTop */)
		{
			if (Maths::isNearZero(fWidth) || Maths::isNearZero(fHeight))
				return;
			switch (orientation)
			{
			case Orientation_2D_LeftTop:
				mvRightBottom.SetXY(mvLeftTop.X() + fWidth, mvLeftTop.Y() + fHeight);
				break;
			default:
				break;
			}
		}

		void Rect::getWidthHeight(float &fWidth, float &fHeight) const
		{
			fWidth = getWidth();
			fHeight = getHeight();
		}

		float Rect::getWidth() const
		{
			return mvRightBottom.X() - mvLeftTop.X();
		}

		float Rect::getHeight() const
		{
			return mvRightBottom.Y() - mvLeftTop.Y();
		}

		String Rect::toString() const
		{
			String strRect(String((int)getLeft()));
			strRect += String(",") + String((int)getTop());
			strRect += String(",") + String((int)getWidth());
			strRect += String(",") + String((int)getHeight());
			return strRect;
		}

		Rect Rect::sCalculateDockRect(const Rect& parentRect, const Rect& subRect, const EnumOrientation2D& eDockType /* = Orientation_2D_Center */, const FVector2& offsetMultiple /* = FVector2(0,0) */)
		{
			FASSERT(!parentRect.isZeroSquare() && !parentRect.isZeroCircumference());
			// full type
			if (Orientation_2D_Full == eDockType)
				return parentRect;

			// set to center
			FVector2 vParent = parentRect.getCenter();
			FVector2 vSub = subRect.getCenter();
			FVector2 vOff = vParent - vSub;
			Rect rc(subRect);
			rc.offset(vOff.X(), vOff.Y());

			float l, t, r, b;
			float subL, subT, subR, subB;
			parentRect.getBound(l, t, r, b);
			rc.getBound(subL, subT, subR, subB);
			bool bReset = false;
			if (subL < l)
			{
				subL = l;
				bReset = true;
			}
			if (subT < t)
			{
				subT = t;
				bReset = true;
			}
			if (subR > r)
			{
				subR = r;
				bReset = true;
			}
			if (subB > b)
			{
				subB = b;
				bReset = true;
			}
			if (bReset)
			{
				rc.setBound(subL, subT, subR, subB);
			}
			// center type
			if (eDockType == Orientation_2D_Center)
			{
				return rc;
			}
			// others
			float dx = 0, dy = 0;
			if (eDockType == Orientation_2D_Left
				|| eDockType == Orientation_2D_LeftTop
				|| eDockType == Orientation_2D_LeftBottom)
			{
				dx = parentRect.getLeft() - rc.getLeft();
			}
			else if (eDockType == Orientation_2D_Right
				|| eDockType == Orientation_2D_RightTop
				|| eDockType == Orientation_2D_RightBottom)
			{
				dx = parentRect.getRight() - rc.getRight();
			}
			if (eDockType == Orientation_2D_Bottom
				|| eDockType == Orientation_2D_LeftBottom
				|| eDockType == Orientation_2D_RightBottom)
			{
				dy = parentRect.getBottom() - rc.getBottom();
			}
			else if (eDockType == Orientation_2D_Top
				|| eDockType == Orientation_2D_LeftTop
				|| eDockType == Orientation_2D_RightTop)
			{
				dy = parentRect.getTop() - rc.getTop();
			}

			rc.offset(dx, dy);

			// offset
			dx = offsetMultiple.X();
			dy = offsetMultiple.Y();
			if (!Maths::isZero(dx) || !Maths::isZero(dy))
			{
				float dxWidth, dyHeight;
				rc.getWidthHeight(dxWidth, dyHeight);
				dx *= dxWidth;
				dy *= dyHeight;
				rc.offset(dx, dy);
			}

			FASSERT(!rc.isZeroSquare() && !rc.isZeroCircumference());
			return rc;
		}

		Rect Rect::sCalculateSubRect(const Rect& rcParent, const Rect& rcRelativeSubRect)
		{
			float rcL, rcT, rcR, rcB;
			rcParent.getBound(rcL, rcT, rcR, rcB);
			float l = rcL + rcRelativeSubRect.getLeft();
			float t = rcT + rcRelativeSubRect.getTop();
			float r = l + rcRelativeSubRect.getWidth();
			float b = t + rcRelativeSubRect.getHeight();

			l = Maths::saturate<float>(l, rcL, rcR, true);
			t = Maths::saturate<float>(t, rcT, rcB, true);
			r = Maths::saturate<float>(r, rcL, rcR, false);
			b = Maths::saturate<float>(b, rcT, rcB, false);
			return Rect(l, t, r - l, b - t);
		}

		Rect Rect::sFromString(const String& strRect)
		{
			TArray<String> strArray;
			strArray = strRect.split(",");
			FASSERT(strArray.size() >= 4U);
			Rect rc(strArray[0].toInt(), strArray[1].toInt(), strArray[2].toInt(), strArray[3].toInt());
			return rc;
		}


	}
}