/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <directxmath.h>
using namespace DirectX;
#include "base.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		enum EnumOrientationAxis
		------------------------------------------------------------*/
		enum EnumOrientationAxis
		{
			Orientation_Axis_PX,
			Orientation_Axis_PY,
			Orientation_Axis_PZ,
			Orientation_Axis_NX,
			Orientation_Axis_NY,
			Orientation_Axis_NZ,
			Orientation_Axis_O,
			Orientation_Axis_Octant_1,
			Orientation_Axis_Octant_2,
			Orientation_Axis_Octant_3,
			Orientation_Axis_Octant_4,
			Orientation_Axis_Octant_5,
			Orientation_Axis_Octant_6,
			Orientation_Axis_Octant_7,
			Orientation_Axis_Octant_8,
			Orientation_Axis_PX_Oblique_Up,
			Orientation_Axis_PX_Oblique_Down,
			//Orientation_Axis_PY_Oblique_Up,
			//Orientation_Axis_PY_Oblique_Down,
			Orientation_Axis_PZ_Oblique_Up,
			Orientation_Axis_PZ_Oblique_Down,
			Orientation_Axis_NX_Oblique_Up,
			Orientation_Axis_NX_Oblique_Down,
			//Orientation_Axis_NY_Oblique_Up,
			//Orientation_Axis_NY_Oblique_Down,
			Orientation_Axis_NZ_Oblique_Up,
			Orientation_Axis_NZ_Oblique_Down,
			Orientation_Axis_Default,
			Orientation_Axis_Max
		};

		/*-----------------------------------------------------------
		enum EnumOrientation2D
		------------------------------------------------------------*/
		enum EnumOrientation2D
		{
			Orientation_2D_Left,
			Orientation_2D_Right,
			Orientation_2D_Bottom,
			Orientation_2D_Top,
			Orientation_2D_LeftTop,
			Orientation_2D_RightTop,
			Orientation_2D_LeftBottom,
			Orientation_2D_RightBottom,
			Orientation_2D_Center,
			Orientation_2D_Full,
			Orientation_2D_MAX
		};

		/*-----------------------------------------------------------
		enum EnumCoordinatePlane
		------------------------------------------------------------*/
		enum EnumCoordinatePlane
		{
			Coordinate_Plane_XOZ,
			Coordinate_Plane_XOY,
			Coordinate_Plane_YOZ,
			Coordinate_Plane_UI,
			Coordinate_Plane_Max,
		};

		/*-----------------------------------------------------------
		enum EnumOrientation3D
		------------------------------------------------------------*/
		enum EnumOrientation3D
		{
			Orientation_3D_Left,
			Orientation_3D_Right,
			Orientation_3D_Bottom,
			Orientation_3D_Top,
			Orientation_3D_Back, // near
			Orientation_3D_Front,// far
			Orientation_3D_BackLeftTop,
			Orientation_3D_BackRightTop,
			Orientation_3D_BackLeftBottom,
			Orientation_3D_BackRightBottom,
			Orientation_3D_FrontLeftTop,
			Orientation_3D_FrontRightTop,
			Orientation_3D_FrontLeftBottom,
			Orientation_3D_FrontRightBottom,
			Orientation_3D_Center,
			Orientation_3D_MAX
		};

		//////////////////
		enum EBaryCentricType
		{
			BaryCentric_Inside,
			BaryCentric_OnV1V3,
			BaryCentric_OnV1V2,
			BaryCentric_OnV2V3,
			BaryCentric_MAX
		};

		enum ECatmullRomType
		{
			CatmullRom_BetweenV2V3,
			CatmullRom_JoiningV1V3,
			CatmullRom_JoiningV2V4,
			CatmullRom_Max
		};

		enum EHermiteType
		{
			Hermite_Max
		};

		struct Point2D
		{
			uint x;
			uint y;
			Point2D(uint ux, uint uy) :x(ux), y(uy) {}
		};
		struct Point
		{
			uint x;
			uint y;
			uint z;
			Point(uint ux, uint uy, uint uz) :x(ux), y(uy), z(uz) {}
		};

		/*-----------------------------------------------------------
		class FVector2
		------------------------------------------------------------*/
		class FVector2 : public IRoot
		{
		public:
			FVector2();
			virtual ~FVector2();
			FVector2(float x, float y);
			FVector2(const FVector2& other);
			FVector2& operator = (const FVector2& other);
			FVector2 operator + (const FVector2& other) const;
			FVector2 operator - (const FVector2& other) const;
			FVector2 operator * (float scale) const;
			const FVector2& operator += (const FVector2& other);
			const FVector2& operator -= (const FVector2& other);
			bool operator == (const FVector2& other) const;
			bool operator != (const FVector2& other) const;

			virtual bool IsZero() const;
			virtual bool IsNearZero() const;
			bool IsAllVectorPositive() const;
			bool IsAllVectorNegative() const;
			//
			float getLength() const;
			float getLengthSquare() const;
			void scale(float scale);
			//
			void SetX(float x);
			void SetY(float y);
			void SetXY(float x, float y);
			float X() const;
			float Y() const;
			void  XY(float& x, float& y) const;
			String toString(bool bActualValue = true) const;

		public:
			static FVector2 sFromString(const String& strVector2);

		public:
			static const FVector2 PXAxis;
			static const FVector2 PYAxis;
			static const FVector2 NXAxis;
			static const FVector2 NYAxis;
			static const FVector2 Origin;

		private:
			float	mx;
			float	my;
		};

		/*-----------------------------------------------------------
		class FPoint2
		------------------------------------------------------------*/
		class FPoint2 : public FVector2
		{
		public:
			//FPoint2();
			//FPoint2(float x, float y);
		};

		/*-----------------------------------------------------------
		class Rect
		------------------------------------------------------------*/
		class Rect : public IRoot
		{
		public:
			Rect();
			virtual ~Rect();
			Rect(const Rect& other);
			Rect(float fLeft, float fTop, float fWidth, float fHeight);
			Rect& operator = (const Rect& other);
			Rect operator + (const Rect& other) const;
			Rect& operator += (const Rect& other);
			bool operator == (const Rect& other) const;
			bool operator != (const Rect& other) const;
			void offset(float dx, float dy);
			void offsetLeft(float fMultiple = 1);
			void offsetRight(float fMultiple = 1);
			void offsetUp(float fMultiple = 1);
			void offsetDown(float fMultiple = 1);
			void resize(float dxSize, float dySize, bool bOffset = true);
			void scale(float dx, float dy, const EnumOrientation2D& eOriente = Orientation_2D_Center);
			float getSquare() const;// Square,Volume,circumference,Mass
			float getCircumference() const;
			bool isZeroSquare() const;
			bool isZeroCircumference() const;
			bool isContain(const FPoint2& point) const;
			bool isContain(const Rect& other) const;
			void setBound(float fLeft, float fTop, float fRight, float fBottom);
			void getBound(float &fLeft, float &fTop, float &fRight, float &fBottom) const;
			void setLeftTop(float fLeft, float fTop);
			void setRightBottom(float fRight, float fBottom);
			void getLeftTop(float &fLeft, float &fTop) const;
			void getRightBottom(float &fRight, float &fBottom) const;
			void setLeft(float fLeft);
			void setTop(float fTop);
			void setRight(float fRight);
			void setBottom(float fBottom);
			void reset(float x, float y, float width, float height);
			float getLeft() const;
			float getTop() const;
			float getRight() const;
			float getBottom() const;
			FVector2 getCenter() const;
			void getUIViewportCoord(FVector2 &leftBottom, FVector2 &leftTop, FVector2 &rightTop, FVector2 &rightBottom, uint uWidth, uint uHeight, bool bAutoAdjust = false) const;
			void getUIViewportCoord(FVector2* leftBottom, FVector2* leftTop, FVector2* rightTop, FVector2* rightBottom, uint uWidth, uint uHeight, bool bAutoAdjust = false) const;
			void setPos(const FVector2& vPos);
			//const FVector2& getPos() const;
			//void setSize();
			void setWidthHeight(float fWidth, float fHeight, const EnumOrientation2D& orientation = Orientation_2D_LeftTop);
			void getWidthHeight(float &fWidth, float &fHeight) const;
			float getWidth() const;
			float getHeight() const;
			String toString() const;

		public:
			static Rect sCalculateDockRect(const Rect& parentRect, const Rect& subRect, const EnumOrientation2D& eDockType = Orientation_2D_Center, const FVector2& offsetMultiple = FVector2(0, 0));
			static Rect sCalculateSubRect(const Rect& rcParent, const Rect& rcRelativeSubRect);
			static Rect sFromString(const String& strRect);

		private:
			virtual bool doCreate(void* pInitData = nullptr) override;
			virtual void doDestroy() override;
			void copyOther(const Rect& other);

		private:
			FVector2	mvLeftTop;
			FVector2	mvRightBottom;
		};


	}
}
