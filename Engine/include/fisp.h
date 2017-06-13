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
			void appFrame(IFrame* pApp);
			void run(IWnd* pWnd);

			IMainSM* mainSM();
			const IMainSM* mainSM() const;

		private:
			Fisp();
			Fisp(const Fisp& other);

		private:
			IMainSM*	mpMainSM;
			IFrame*		mpAppDefault;
			IWnd*		mpWnd;
			
		};


	}
}