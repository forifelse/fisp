/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "world.h"

namespace fisp
{
	namespace engine
	{
		/*-----------------------------------------------------------
		class IFrame
		------------------------------------------------------------*/
		class IFrame : public IRoot
		{
		public:
			// setup
			virtual void setup() = 0;

			// This function can be used to initialize application state and will run after essential
			// hardware resources are allocated.  Some state that does not depend on these resources
			// should still be initialized in the constructor such as pointers and flags.
			virtual void startup() = 0;
			virtual void cleanup() = 0;

			// The update method will be invoked once per frame.  Both state updating and scene
			// rendering should be handled by this method.
			virtual void update(float delta) = 0;

			// Official rendering pass
			virtual void render(float delta) = 0;

			//// Optional UI (overlay) rendering pass.  This is LDR.  The buffer is already cleared.
			//virtual void renderUI(class GraphicsContext& Context) {};

			//// Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
			////virtual bool isDone();

			////virtual void viewport(uint cx, uint cy, bool bFullscreen) = 0;
			virtual Render::InitParam* initParamRnd() = 0;
			virtual const Render::InitParam& initParamRnd() const = 0;
			virtual IScene* scene() = 0;
			virtual const IScene* scene() const = 0;

		};

		/*-----------------------------------------------------------
		class IMainStateMachine
		------------------------------------------------------------*/
		class IMainSM : public IRoot
		{
		public:
			// setup
			virtual bool setup() = 0;

			// This function can be used to initialize application state and will run after essential
			// hardware resources are allocated.  Some state that does not depend on these resources
			// should still be initialized in the constructor such as pointers and flags.
			virtual bool startup() = 0;
			virtual void cleanup() = 0;

			//// The update method will be invoked once per frame.  Both state updating and scene
			//// rendering should be handled by this method.
			//virtual void update(float delta) = 0;

			// The render method will be invoked once per frame.
			virtual void render() = 0;

			//// Optional UI (overlay) rendering pass.  This is LDR.  The buffer is already cleared.
			//virtual void renderUI(class GraphicsContext& Context) {};
			//
			//// Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
			//virtual bool isQuit() = 0;
			//virtual bool* isRunning() = 0;
			virtual IFrame* appFrame() = 0;
			virtual const IFrame* appFrame() const = 0;
			virtual void appFrame(IFrame* pAppFrame) = 0;
			virtual IDBPath* dbPath() = 0;
			virtual const IDBPath* dbPath() const = 0;
		};

		/*-----------------------------------------------------------
		class IWnd
		------------------------------------------------------------*/
		class IWnd : public IRoot
		{
		public:
			virtual void mainSM(IMainSM* pMainSM) = 0;
			virtual void run() = 0;
			virtual void show(bool bShow) = 0;
			virtual String exePath() = 0;
			virtual bool isUWP() const = 0;
		};

		/*-----------------------------------------------------------
		class Frame
		------------------------------------------------------------*/
		class Frame : public IFrame
		{
		public:
			Frame();
			virtual ~Frame();

		public:
			void setup() override;
			void startup() override;
			void cleanup() override;
			void update(float delta) final;
			void render(float delta) final;

		public:
			// init param for render and window
			Render::InitParam* initParamRnd() override;
			// init param for render and window
			const Render::InitParam& initParamRnd() const override;
			IScene* scene() override;
			const IScene* scene() const override;

		public:
			void scene(IScene* pScene);

		private:


		protected:
			Render::InitParam	mRndParam;
			IScene*				mpSceneRef;

		};


	}
}