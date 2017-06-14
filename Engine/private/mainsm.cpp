/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "mainsm.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class MainStateMachine
		------------------------------------------------------------*/
		MainSM::MainSM()
			: mpAppFrame(nullptr)
		{
		}

		MainSM::~MainSM()
		{
			mpAppFrame = nullptr;
		}

		bool MainSM::setup()
		{
			return false;
		}

		bool MainSM::startup()
		{
			return false;
		}

		void MainSM::cleanup()
		{

		}

		void MainSM::render()
		{

		}

		void MainSM::appFrame(IFrame* pAppFrame)
		{
			mpAppFrame = pAppFrame;
		}


	}
}