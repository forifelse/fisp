/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "inShare.h"
#include "entityif.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class IScene
		------------------------------------------------------------*/
		class IScene : public IRoot
		{
		public:
			virtual void clear() = 0;
			virtual void build() = 0;
			virtual void update(float delta) = 0;
			virtual void render(float delta) = 0;
			virtual void onSize() = 0;
		};

		/*-----------------------------------------------------------
		class IWorld
		------------------------------------------------------------*/
		class IWorld : public IRoot
		{
		public:
		};


	}
}