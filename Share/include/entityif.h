/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "scenedata.h"
#include "hwif.h"

namespace fisp
{
	namespace share
	{
		class IMeshRender;
		/*-----------------------------------------------------------
		class IEntity
		------------------------------------------------------------*/
		class IEntity : public IRoot
		{
		public:
			virtual void update(float delta) = 0;
			virtual void render(float delta) = 0;

			//virtual void makePrimi(IPrimiMaker* pPrimiMaker) = 0;
			virtual void buildMesh(IMeshRender* pMeshRender) = 0;
		};

		/*-----------------------------------------------------------
		class IMeshRender
		------------------------------------------------------------*/
		class IMeshRender : public IRoot
		{
		public:
			virtual void device(IDevice* pDevice) = 0;
			virtual void build(IEntity*	pEntity) = 0;
			virtual void update(float delta) = 0;
			virtual void render(float delta) = 0;
		};


	}
}