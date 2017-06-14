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
			: mpAppRef(nullptr)
		{
		}

		MainSM::~MainSM()
		{
			mpAppRef = nullptr;
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

		void MainSM::ready()
		{

		}

		IFrame* MainSM::appFrame()
		{
			return mpAppRef;
		}

		const IFrame* MainSM::appFrame() const
		{
			return mpAppRef;
		}

		void MainSM::appFrame(IFrame* pAppFrame)
		{
			mpAppRef = pAppFrame;
		}

		IDBPath* MainSM::dbPath()
		{
			return mpDBPath;
		}

		const IDBPath* MainSM::dbPath() const
		{
			return mpDBPath;
		}

		void MainSM::createStatic()
		{

		}

		void MainSM::destroyStatic()
		{

		}


	}
}