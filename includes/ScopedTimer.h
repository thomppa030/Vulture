#ifndef SCOPEDTIMER_H
#define SCOPEDTIMER_H

#include <iostream>
#include <chrono>

class ScopedTimer {
public:
    ScopedTimer(const char* func) : m_Name(func), m_Stopped(false) {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~ScopedTimer() {
        if (!m_Stopped)
            Stop();
    }

    void Stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();
        auto duration = end - start;
        double ms = duration * 0.001;
        std::cout << m_Name << ": " << duration << ms << " ms" << std::endl;
        m_Stopped = true;
    }

private:

    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#define SCOPED_TIMER ScopedTimer timer(__FUNCTION__);

#endif // SCOPEDTIMER_H