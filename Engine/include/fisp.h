/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "frame.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class Fisp
		------------------------------------------------------------*/
		class Fisp : public IRoot
		{
		public:
			virtual ~Fisp();
			static Fisp* root();
			void init(IFrame* pAppRef, IWnd* pWndRef);
			void run();

			IMainSM* mainSM();
			const IMainSM* mainSM() const;
			IWnd* wnd();
			const IWnd* wnd() const;

		private:
			Fisp();
			Fisp(const Fisp& other);

		private:
			IMainSM*	mpMainSM;
			IFrame*		mpAppDefault;
			IWnd*		mpWnd;
			
		};

		/*-----------------------------------------------------------
		Global Function
		------------------------------------------------------------*/
		void RunApp(IFrame* pApp, IWnd* pWnd);


	}
}

/*-----------------------------------------------------------
Entry
------------------------------------------------------------*/
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define MAIN_FUNCTION()  int wmain(int argc, wchar_t** argv)
#else
#define MAIN_FUNCTION()  [Platform::MTAThread] int main(Platform::Array<Platform::String^>^)
#endif

#define CREATE_APPLICATION( app_class ) \
MAIN_FUNCTION() \
{ \
	diff::engine::runApplication( app_class(), L#app_class ); \
	return 0; \
}

#define FISP_RUN( AppClass, WndClass ) \
MAIN_FUNCTION() \
{ \
	IAppFrame* pApp = AppClass::createMem<AppClass>(); \
	IWnd* pWnd      = WndClass::createMem<WndClass>(); \
	fisp::engine::RunApp( pApp, pWnd ); \
	return 0; \
}