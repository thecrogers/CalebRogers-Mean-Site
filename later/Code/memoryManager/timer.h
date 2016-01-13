#ifndef TIMERHEADERFILE
#include <time.h>
#include <sys/time.h>
#define TIMERHEADERFILE
class Timer
{
public: 
	typedef unsigned long long timestamp_t;
	static timestamp_t
	
	get_timestamp ()
	{
		struct timeval now;
		gettimeofday (&now, NULL);
		return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;

		return 0;
	}
	
	double start();
	double end(double);

private:

 };
  #endif
