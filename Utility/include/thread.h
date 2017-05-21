/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "base.h"
#include <thread>

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class IThread
		------------------------------------------------------------*/
		class Mutex : public IRoot
		{
		public:
			Mutex();
			virtual ~Mutex();
			

		private:
			std::mutex mMutex;
		};

		/*-----------------------------------------------------------
		class IThread
		------------------------------------------------------------*/
		class IThread : public IRoot
		{
		public:
		};

		/*-----------------------------------------------------------
		class Thread
		------------------------------------------------------------*/
		class Thread : public IThread
		{
		public:
			Thread();
			virtual ~Thread();

			template<class TFunc, class... TArgs>
			static void start(bool bAsyn = true);

			void stop();

		private:
			void copyOther(const Thread& other);
			bool doCreate(void* pInitData = nullptr) override;
			void doDestroy() override;

		};

		/*-----------------------------------------------------------
		class Thread
		------------------------------------------------------------*/
		template<class TFunc, class... TArgs>
		void Thread::start(bool bAsyn /* = true */)
		{
			std::thread th(TFunc, TArgs);
			if (bAsyn)
				th.detach();
			else
				th.join();
		}


	}
}
