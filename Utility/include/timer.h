/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include "base.h"
#include <chrono>

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class Timer
		------------------------------------------------------------*/
		class ITimer : public IRoot
		{
		public:
			virtual float tick() = 0;
			virtual float delta() const = 0;
			virtual float elapse() const = 0;
			virtual float fps() const = 0;
		};

		/*-----------------------------------------------------------
		class Timer
		------------------------------------------------------------*/
		class Timer : public ITimer
		{
		public:
			Timer();
			virtual ~Timer();

			float tick();
			float delta() const;
			float elapse() const;
			float fps() const;

			void reset();
			uint64 elapsedMilli() const;
			uint64 elapsedMicro() const;
			uint64 elapsedNano() const;
			uint64 elapsedSecond() const;
			uint64 elapsedMinute() const;
			uint64 elapsedHour() const;

		public:
			static Timer* globalTimer();
			static String systemTime(const String strDelimit = ",", bool bAddDayOfWeek = false, dword* dwDayOfWeek = nullptr);
			static String elapseTime(bool bHourMod24 = true);
			static String timestamp();

		private:
			void copyOther(const Timer& other);
			bool doCreate(void* pData = nullptr) override;
			void doDestroy() override;

		private:
			std::chrono::time_point<std::chrono::high_resolution_clock>	mBegin;
			std::chrono::time_point<std::chrono::high_resolution_clock>	mTick;
			uint64	muDeltaMilli;

		};


	}
}
