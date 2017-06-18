/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/render.h"

namespace fisp
{
	namespace render
	{
		/*-----------------------------------------------------------
		class Render
		------------------------------------------------------------*/
		Render::Render()
			: mpDevice(nullptr)
			, mpCamera(nullptr)
			, mpScene(nullptr)
		{
			mpScene = Scene::createMem<Scene>();
		}

		Render::~Render()
		{
			Scene::destroyMem<IScene>(mpScene);
		}

		void Render::update(float delta)
		{
			mpScene->update(delta);
		}

		void Render::render(float delta)
		{
			mpScene->render(delta);
		}

		ICamera* Render::camera()
		{
			return mpCamera;
		}

		const ICamera* Render::camera() const
		{
			return mpCamera;
		}

		//void Render::scene(IScene* pScene)
		//{
		//	mpScene = pScene;
		//}

		IScene* Render::scene()
		{
			return mpScene;
		}

		const IScene* Render::scene() const
		{
			return mpScene;
		}

	}
}