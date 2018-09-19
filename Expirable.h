#include<iostream>
#include<string>
#include<chrono>
#include<thread>

#include "TimeUtils.h"

#ifndef Expirable_H
#define Expirable_H

typedef std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long, std::ratio<1l, 1000000000l> > > TimePoint;

class Expirable
{
	private:
		TimePoint m_timePoint;
		long m_waitCount;

	public:
		Expirable(const long& waitQuantity, const TimeUnit& unit) : m_timePoint(std::chrono::high_resolution_clock::now()) 
		{ 
			m_waitCount = TimeUtils::waitDuration(waitQuantity, unit).count();
		}
	
		bool isExpired()
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-m_timePoint).count();
			if(duration>=m_waitCount)
				return(true);
			else
				return(false);	
		}
};

#endif
