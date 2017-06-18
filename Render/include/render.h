/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "pch.h"

namespace fisp
{
	namespace render
	{
		/*-----------------------------------------------------------
		class Render
		------------------------------------------------------------*/
		class Render : public IRender
		{
		public:
			Render();
			virtual ~Render();

			void update(float delta) override;
			void render(float delta) override;

			//virtual void fullscreen(bool bFullscreen) = 0;
			//virtual void dbPath(IDBPath* pDBPath) = 0;
			//virtual void eventPreRender(IDelegate* pEvent) = 0;
			//virtual void eventPostRender(IDelegate* pEvent) = 0;
			//virtual bool createPipelineState(ShaderState* pState) = 0;
			void buildScene() override;
			ICamera* camera() override;
			const ICamera* camera() const override;
			//void scene(IScene* pScene) override;
			IScene* scene() override;
			const IScene* scene() const override;

		public:
			void dbPath(IDBPath* pDBPath);
			void timer(ITimer* pTimer);

		private:
			IDevice*	mpDevice;
			ICamera*	mpCamera;
			IScene*		mpScene;
			//
			IDBPath*			mpDBPath;
			ITimer*				mpTimer;
		};


	}
}