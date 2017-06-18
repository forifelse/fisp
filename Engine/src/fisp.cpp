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

		void Fisp::init(IFrame* pAppRef, IWnd* pWndRef)
		{
			if (nullptr == pAppRef)
			{
				if (nullptr == mpAppDefault)
					mpAppDefault = Frame::createMem<Frame>();
				pAppRef = mpAppDefault;
			}
			mpMainSM->appFrame(pAppRef);
			mpWnd = pWndRef;
		}

		void Fisp::run()
		{
			if (nullptr == mpWnd)
				return;
			mpMainSM->dbPath()->exePath(mpWnd->exePath());
			mpMainSM->dbPath()->dataPath(0);
			if (!mpMainSM->setup())
				return;
			//
			IRender::InitParam* pInitParam = mpMainSM->appFrame()->initParamRnd();
			mpWnd->create(pInitParam);
			mpWnd->mainSM(mpMainSM);
			mpWnd->show(true);
			if (mpWnd->isUWP())
			{
				mpWnd->run();
			}
			else
			{
				mpMainSM->startup();
				mpWnd->run();
				mpMainSM->cleanup();
			}
			//IWnd::destroyMem<IWnd>(mpWnd);
			mpWnd = nullptr;
		}

		IMainSM* Fisp::mainSM()
		{
			return mpMainSM;
		}

		const IMainSM* Fisp::mainSM() const
		{
			return mpMainSM;
		}

		IWnd* Fisp::wnd()
		{
			return mpWnd;
		}

		const IWnd* Fisp::wnd() const
		{
			return mpWnd;
		}

		/*-----------------------------------------------------------
		Global Function
		------------------------------------------------------------*/
		void RunApp(IFrame* pApp, IWnd* pWnd)
		{
			Fisp::root()->init(pApp, pWnd);
			Fisp::root()->run();
		}



	}
}