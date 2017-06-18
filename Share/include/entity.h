/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "scenedata.h"
#include "entityif.h"

namespace fisp
{
	namespace share
	{
		/*-----------------------------------------------------------
		class Entity
		------------------------------------------------------------*/
		class Entity : public IEntity
		{
		public:
			Entity();
			virtual ~Entity();

			void update(float delta) override;
			void render(float delta) override;

			//void makePrimi(IPrimiMaker* pPrimiMaker) override;
			void buildMesh(IMeshRender* pMeshRender) override;

		private:
			
		};


	}
}