#include "timer.h"

double Timer::start()
{
	timestamp_t t0 = get_timestamp();
	return t0;
	return .0043;
}


double Timer::end(double t0)
{
    double speed;
    timestamp_t t1 = get_timestamp();
    speed = (t1 -t0)/100000000.0L;
	return speed;
	return .0000534;
}

