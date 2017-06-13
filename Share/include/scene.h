/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "scenedata.h"
#include "renderif.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class Scene
		------------------------------------------------------------*/
		class Scene : public IScene
		{
		public:
			Scene();
			virtual ~Scene();

		public:
			static bool writeScene(const SDScene* pScene, const std::string& strPathFile);
			static bool readScene(SDScene* pScene, const std::string& strPathFile);

		private:
			
		};


	}
}