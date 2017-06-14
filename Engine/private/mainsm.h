/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "../include/frame.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class MainStateMachine
		------------------------------------------------------------*/
		class MainSM : public IMainSM
		{
		public:
			// setup
			virtual bool setup() override;

			// This function can be used to initialize application state and will run after essential
			// hardware resources are allocated.  Some state that does not depend on these resources
			// should still be initialized in the constructor such as pointers and flags.
			virtual bool startup() override;
			virtual void cleanup() override;

			//// The update method will be invoked once per frame.  Both state updating and scene
			//// rendering should be handled by this method.
			//virtual void update(float delta) = 0;

			// The render method will be invoked once per frame.
			virtual void render() override;

			//// Optional UI (overlay) rendering pass.  This is LDR.  The buffer is already cleared.
			//virtual void renderUI(class GraphicsContext& Context) {};

			//// Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
			//virtual bool isQuit() override;
			//virtual bool* isRunning() override;
			//virtual IFrame* appFrame() override;
			//virtual const IFrame* appFrame() const override;
			virtual void appFrame(IFrame* pAppFrame) override;
			//virtual IDBPath* dbPath() override;
			//virtual const IDBPath* dbPath() const override;

		public:
			MainSM();
			virtual ~MainSM();

		private:
			IFrame* mpAppFrame;
		};


	}
}