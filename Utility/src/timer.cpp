/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#include <time.h>
#include "../include/timer.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class Timer
		------------------------------------------------------------*/
		Timer::Timer()
		{
			reset();
			mTick = mBegin;
		}

		Timer::~Timer()
		{
			reset();
		}

		void Timer::copyOther(const Timer& other)
		{

		}

		bool Timer::doCreate(void* pData /* = nullptr */)
		{
			reset();
			return true;
		}

		void Timer::doDestroy()
		{

		}

		float Timer::tick()
		{
			muDeltaMilli = chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mTick).count();
			mTick = std::chrono::high_resolution_clock::now();
			return (float)muDeltaMilli * 0.001f;
		}

		float Timer::delta() const
		{
			return (float)muDeltaMilli * 0.001f;
		}

		float Timer::elapse() const
		{
			return (float)elapsedMilli() * 0.001f;
		}

		float Timer::fps() const
		{
			return 1000.f / muDeltaMilli;
		}

		void Timer::reset()
		{
			mBegin = std::chrono::high_resolution_clock::now();
		}

		uint64 Timer::elapsedMilli() const
		{
			uint64 cnt = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}

		uint64 Timer::elapsedMicro() const
		{
			uint64 cnt = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}

		uint64 Timer::elapsedNano() const
		{
			uint64 cnt = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}

		uint64 Timer::elapsedSecond() const
		{
			uint64 cnt = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}

		uint64 Timer::elapsedMinute() const
		{
			uint64 cnt = chrono::duration_cast<chrono::minutes>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}
		uint64 Timer::elapsedHour() const
		{
			uint64 cnt = chrono::duration_cast<chrono::hours>(chrono::high_resolution_clock::now() - mBegin).count();
			return cnt;
		}

		Timer* Timer::globalTimer()
		{
			static Timer gTimer;
			return &gTimer;
		}

		String Timer::systemTime(const String strDelimit /* = "," */, bool bAddDayOfWeek /* = false */, dword* dwDayOfWeek /* = nullptr */)
		{
			Timer* pTimer = globalTimer();
			//time_t t = time(nullptr);
			auto t = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
			struct tm *tv = localtime(&t);
			char day[16] = { 0 }, time[16] = { 0 };
			sprintf(day,  "%04d-%02d-%02d", tv->tm_year + 1900, tv->tm_mon + 1, tv->tm_mday);
			sprintf(time, "%02d:%02d:%02d ", tv->tm_hour, tv->tm_min, tv->tm_sec);
			//sprintf(time, "%02d:%02d:%02d %03d ", tv->tm_hour, tv->tm_min, tv->tm_sec, pTimer->elapsedMilli() % 1000);
			String strTime(day);
			strTime += strDelimit;
			strTime += String(time);

			if (bAddDayOfWeek)
			{
				String dow;
				switch (tv->tm_wday)
				{
				case 0: dow = "Sunday";		break;
				case 1: dow = "Monday";		break;
				case 2: dow = "Tuesday";	break;
				case 3: dow = "Wednesday";	break;
				case 4: dow = "Thursday";	break;
				case 5: dow = "Friday";		break;
				case 6: dow = "Saturday";	break;
				default:
					dow = "";
					break;
				}
				strTime += dow;
			}
			if (nullptr != dwDayOfWeek)
			{
				*dwDayOfWeek = tv->tm_wday;
			}

			return strTime;
		}

		String Timer::elapseTime(bool bHourMod24 /* = true */)
		{
			Timer* pTimer = globalTimer();
			char time[32] = { 0 };
			if(bHourMod24)
				sprintf(time, "%02llu:%02llu:%02llu %03llu ", pTimer->elapsedHour() % 24, pTimer->elapsedMinute() % 60, pTimer->elapsedSecond() % 60, pTimer->elapsedMilli() % 1000);
			else
				sprintf(time, "%llu days %02llu:%02llu:%02llu %03llu ", pTimer->elapsedHour() / 24, pTimer->elapsedHour() % 24, pTimer->elapsedMinute() % 60, pTimer->elapsedSecond() % 60, pTimer->elapsedMilli() % 1000);
			String strTime(time);

			return strTime;
		}

		String Timer::timestamp()
		{
			Timer* pTimer = globalTimer();
			auto t = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
			struct tm *tv = localtime(&t);
			char day[16] = { 0 }, time[16] = { 0 };
			sprintf(day, "%04d%02d%02d", tv->tm_year + 1900, tv->tm_mon + 1, tv->tm_mday);
			sprintf(time, "%02d%02d%02d%03llu ", tv->tm_hour, tv->tm_min, tv->tm_sec, pTimer->elapsedMilli() % 1000);
			String strTime(day);
			strTime += String(time);
			return strTime;
		}



	}
}