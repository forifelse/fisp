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

			ICamera* camera() override;
			const ICamera* camera() const override;
			//void scene(IScene* pScene) override;
			IScene* scene() override;
			const IScene* scene() const override;

		private:
			IDevice*	mpDevice;
			ICamera*	mpCamera;
			IScene*		mpScene;
		};


	}
}