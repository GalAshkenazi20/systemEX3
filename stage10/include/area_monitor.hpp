#ifndef AREA_MONITOR_HPP
#define AREA_MONITOR_HPP

#include <pthread.h>
#include <atomic>

class AreaMonitor {
private:
    static pthread_t monitor_thread;
    static pthread_cond_t area_condition;
    static pthread_mutex_t area_mutex;
    static std::atomic<double> current_area;
    static std::atomic<bool> is_monitoring;
    static std::atomic<bool> has_100_units;
    
    static void* monitorAreaThread(void* arg);
    
public:
    static void startMonitoring();
    static void stopMonitoring();
    static void updateArea(double new_area);
    static void signalAreaChange();
};

#endif // AREA_MONITOR_HPP
