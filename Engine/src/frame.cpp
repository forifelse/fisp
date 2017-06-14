/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/frame.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class Frame
		------------------------------------------------------------*/
		Frame::Frame()
		{
			mRndParam.deviceParam.hWnd = nullptr;
			mRndParam.deviceParam.width = 800;
			mRndParam.deviceParam.height = 600;
			mRndParam.deviceParam.fullscreen = true;
			mRndParam.strTitle = "Fisp Window";
			mRndParam.bBorder = false;
		}

		Frame::~Frame()
		{

		}

		void Frame::setup()
		{

		}

		void Frame::startup()
		{

		}

		void Frame::cleanup()
		{

		}

		void Frame::update(float delta)
		{

		}

		void Frame::render(float delta)
		{

		}

		Render::InitParam* Frame::initParamRnd()
		{
			return &mRndParam;
		}

		const Render::InitParam& Frame::initParamRnd() const
		{
			return mRndParam;
		}

		IScene* Frame::scene()
		{
			return mpSceneRef;
		}

		const IScene* Frame::scene() const
		{
			return mpSceneRef;
		}

		void Frame::scene(IScene* pScene)
		{
			mpSceneRef = pScene;
		}


	}
}