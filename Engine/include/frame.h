/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "world.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class IFrame
		------------------------------------------------------------*/
		class IFrame : public IRoot
		{
		public:
			
		};

		/*-----------------------------------------------------------
		class Frame
		------------------------------------------------------------*/
		class Frame : public IFrame
		{
		public:
			Frame();
			virtual ~Frame();

		private:

		};


	}
}