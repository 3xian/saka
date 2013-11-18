#pragma once

#include <sys/time.h>
#include <cstdlib>  // for NULL

namespace base {

class TimeUtil {
public:
    static long timeval2msec(const timeval& tv) {
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

    static timeval msec2timeval(long msec) {
        timeval tv;
        tv.tv_sec = msec / 1000;
        tv.tv_usec = msec % 1000 * 1000;
        return tv;
    }
};

class Time {
public:
    Time() {
        start();
    }

    void start() {
        timeval start_timeval;
        gettimeofday(&start_timeval, NULL);
        start_time_ = TimeUtil::timeval2msec(start_timeval);
    }

    long get_time_passed() const {
        timeval current_timeval;
        gettimeofday(&current_timeval, NULL);
        return TimeUtil::timeval2msec(current_timeval) - start_time_;
    }

private:
    long start_time_;
};

}  // namespace base
