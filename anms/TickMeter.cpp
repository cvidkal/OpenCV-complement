#include "TickMeter.h"

TickMeter::TickMeter() { reset(); }
__int64 TickMeter::getTimeTicks() const { return sumTime; }
double TickMeter::getTimeMicro() const { return (double)getTimeTicks() / cvGetTickFrequency(); }
double TickMeter::getTimeMilli() const { return getTimeMicro()*1e-3; }
double TickMeter::getTimeSec()   const { return getTimeMilli()*1e-3; }
__int64 TickMeter::getCounter() const { return counter; }
void  TickMeter::reset() { startTime = 0; sumTime = 0; counter = 0; }

void TickMeter::start(){ startTime = cvGetTickCount(); }
void TickMeter::stop()
{
	__int64 time = cvGetTickCount();
	if (startTime == 0)
		return;

	++counter;

	sumTime += (time - startTime);
	startTime = 0;
}