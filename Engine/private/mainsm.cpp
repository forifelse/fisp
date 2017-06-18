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
			: mpRender(nullptr)
			, mpAppRef(nullptr)
			, mpTimer(nullptr)
			, mbRunning(false)
			, mpDBPath(nullptr)
		{
			mpDBPath = DBPath::createMem<DBPath>();
		}

		MainSM::~MainSM()
		{
			IDBPath::destroyMem<IDBPath>(mpDBPath);
			mpAppRef = nullptr;
		}

		void MainSM::doDestroy()
		{
			IRender::destroyMem<IRender>(mpRender);
		}

		bool MainSM::setup()
		{
			if (nullptr == mpAppRef)
				return false;
			Log::singleton()->setLogFilePath(mpDBPath->exePath());
			Log::singleton()->open();
			Log::singleton()->write(String("log start") + String::Enter, false, Log::ETimeType::Time_System);
			//
			mpAppRef->initParamRnd()->deviceParam.pDBPath = mpDBPath;
			mpAppRef->setup();
			return true;
		}

		bool MainSM::startup()
		{
			mpTimer = Timer::createMem<Timer>();
			mpRender = Render::createMem<Render>();
			mpRender->create(mpAppRef->initParamRnd());
			((Render*)mpRender)->dbPath(mpDBPath);
			//mpRender->scene(Scene::createMem<Scene>());
			((Render*)mpRender)->timer(mpTimer);
			mpTimer->create();
			//
			//((IFrame*)mpAppRef)->scene(mpRender->scene());
			mpAppRef->startup();
			//
			ready();
			mpRender->buildScene();
			mbRunning = true;
			return true;
		}

		void MainSM::cleanup()
		{
			mpAppRef->cleanup();
			gLog->write(String("run elapsed: ") + String(Timer::globalTimer()->elapseTime(false)) + String::Enter, false, Log::ETimeType::Time_System);
		}

		void MainSM::render()
		{
			float delta = mpTimer->tick();
			mpRender->update(delta);
			mpRender->render(delta);
		}

		bool MainSM::isQuit()
		{
			return !mbRunning;
		}

		bool* MainSM::isRunning()
		{
			return &mbRunning;
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
			Log::destroyStatic();
		}


	}
}