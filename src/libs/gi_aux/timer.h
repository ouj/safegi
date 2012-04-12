// 
// Class Timer 
//

#ifndef _TIMER_H_
#define _TIMER_H_

// Include ---------------------------------------------------------------
#include <string>
using std::string;

// Use to enable high performance counting throught MS counters.
#ifdef WIN32
#define MS_TIMER
#include <winsock.h>
// #include <windows.h>
#include "MMSystem.h"
inline int gettimeofday(struct timeval* tp, void* tzp) {
    DWORD t;
    t = timeGetTime();
    tp->tv_sec = t / 1000;
    tp->tv_usec = (t % 1000) * 1000;
    return 0;
}
#else
#include <sys/time.h>
#endif

// Declaration -----------------------------------------------------------

class Timer {

// Static data ------------------------------------------------------

// Data -------------------------------------------------------------
private:
#ifdef MS_TIMER
    LARGE_INTEGER           _counterFrequency;
#endif

    double  _timeStart;
    double	_timeElapsed;	// total time spent in all the call start/stop
	int	    _count;			// Number of times stopped

// Public methods ---------------------------------------------------
public:
	Timer();		// Creates an empty timer

    void Reset() {	// Reset the timer
        _timeStart = 0;
        _timeElapsed = 0;
        _count = 0;
    }
    void Start() {	// Start the timer
        _timeStart = _GetTime();
    }
    void Stop() {	// Stop the timer and add the time to elapsedTime
        _timeElapsed += _GetTime() - _timeStart;
        _count ++;
    }

    double GetElapsedTime() { return _timeElapsed; }
    int GetCount() { return _count; }

// Private methods --------------------------------------------------
private:
    double _GetTime();
};

// Inline functions ------------------------------------------------------
inline Timer::Timer() {
	Reset();
#ifdef MS_TIMER
    QueryPerformanceFrequency(&_counterFrequency);
#endif
}

inline double Timer::_GetTime() {
#ifdef MS_TIMER
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);
  return (double)t.QuadPart / (double)_counterFrequency.QuadPart;
#else
    timeval t;
    gettimeofday(&t,0);
    return (double)t.tv_sec + (double)t.tv_usec / 1000000.0;
#endif
}

#endif // _TIMER_H_
