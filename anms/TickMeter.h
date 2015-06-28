#ifndef _TICK_METER_H_
#define _TICK_METER_H_
#include <opencv2\opencv.hpp>


class TickMeter
{
public:
	TickMeter();
	void start();
	void stop();

	__int64 getTimeTicks() const;
	double getTimeMicro() const;
	double getTimeMilli() const;
	double getTimeSec()   const;
	__int64 getCounter() const;

	void reset();
private:
	__int64 counter;
	__int64 sumTime;
	__int64 startTime;
};



#endif