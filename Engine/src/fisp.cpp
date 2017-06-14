/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include "../include/fisp.h"
#include "../private/mainsm.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class Fisp
		------------------------------------------------------------*/
		Fisp::Fisp()
			: mpMainSM(nullptr)
			, mpAppDefault(nullptr)
			, mpWnd(nullptr)
		{
			// create static
			MainSM::createStatic();
			//
			mpMainSM = MainSM::createMem<MainSM>();
		}

		Fisp::~Fisp()
		{
			MainSM::destroyMem<IMainSM>(mpMainSM);
			Frame::destroyMem<IFrame>(mpAppDefault);
			mpWnd = nullptr;
			// destroy static
			MainSM::destroyStatic();
		}

		Fisp::Fisp(const Fisp& o)
			: mpMainSM(nullptr)
			, mpAppDefault(nullptr)
			, mpWnd(nullptr)
		{

		}

		Fisp* Fisp::root()
		{
			static Fisp gFisp;
			return &gFisp;
		}

		void Fisp::appFrame(IFrame* pApp)
		{
			if (nullptr == pApp)
			{
				if (nullptr == mpAppDefault)
					mpAppDefault = Frame::createMem<Frame>();
				pApp = mpAppDefault;
			}
			mpMainSM->appFrame(pApp);
		}

		void Fisp::run(IWnd* pWnd)
		{
			if (nullptr == pWnd)
				return;
			mpWnd = pWnd;
			mpMainSM->dbPath()->exePath(pWnd->exePath());
			mpMainSM->dbPath()->dataPath(0);
			if (!mpMainSM->setup())
				return;
			//
			IRender::InitParam* pInitParam = mpMainSM->appFrame()->initParamRnd();
			pWnd->create(pInitParam);
			pWnd->mainSM(mpMainSM);
			pWnd->show(true);
			if (pWnd->isUWP())
			{
				pWnd->runLoop();
			}
			else
			{
				mpMainSM->startup();
				pWnd->runLoop();
				mpMainSM->cleanup();
			}
			IWnd::destroyMem<IWnd>(pWnd);
		}

		IMainSM* Fisp::mainSM()
		{
			return mpMainSM;
		}

		const IMainSM* Fisp::mainSM() const
		{
			return mpMainSM;
		}

		/*-----------------------------------------------------------
		Global Function
		------------------------------------------------------------*/
		void RunApp(IFrame* pApp, IWnd* pWnd)
		{
			Fisp::root()->appFrame(pApp);
			Fisp::root()->run(pWnd);
		}



	}
}