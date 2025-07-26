#include "area_monitor.hpp"
#include <iostream>
#include <unistd.h>

// Static member definitions
pthread_t AreaMonitor::monitor_thread;
pthread_cond_t AreaMonitor::area_condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t AreaMonitor::area_mutex = PTHREAD_MUTEX_INITIALIZER;
std::atomic<double> AreaMonitor::current_area{0.0};
std::atomic<bool> AreaMonitor::is_monitoring{false};
std::atomic<bool> AreaMonitor::has_100_units{false};

void* AreaMonitor::monitorAreaThread(void* arg) {
    (void)arg; // Suppress unused parameter warning
    
    std::cout << "Area Monitor Thread Started - waiting for area >= 100 units" << std::endl;
    
    while (is_monitoring.load()) {
        pthread_mutex_lock(&area_mutex);
        
        // Wait for area change signal
        pthread_cond_wait(&area_condition, &area_mutex);
        
        if (!is_monitoring.load()) {
            pthread_mutex_unlock(&area_mutex);
            break;
        }
        
        double area = current_area.load();
        bool currently_has_100 = has_100_units.load();
        
        if (area >= 100.0 && !currently_has_100) {
            // Area reached 100+ units
            std::cout << "At Least 100 units belongs to CH" << std::endl;
            has_100_units.store(true);
        } else if (area < 100.0 && currently_has_100) {
            // Area dropped below 100 units
            std::cout << "At Least 100 units no longer belongs to CH" << std::endl;
            has_100_units.store(false);
        }
        
        pthread_mutex_unlock(&area_mutex);
    }
    
    std::cout << "Area Monitor Thread Stopped" << std::endl;
    return nullptr;
}

void AreaMonitor::startMonitoring() {
    if (is_monitoring.load()) {
        return; // Already monitoring
    }
    
    is_monitoring.store(true);
    int result = pthread_create(&monitor_thread, nullptr, monitorAreaThread, nullptr);
    if (result != 0) {
        std::cerr << "Failed to create area monitor thread" << std::endl;
        is_monitoring.store(false);
    }
}

void AreaMonitor::stopMonitoring() {
    if (!is_monitoring.load()) {
        return; // Not monitoring
    }
    
    is_monitoring.store(false);
    signalAreaChange(); // Wake up the waiting thread
    pthread_join(monitor_thread, nullptr);
}

void AreaMonitor::updateArea(double new_area) {
    current_area.store(new_area);
    signalAreaChange();
}

void AreaMonitor::signalAreaChange() {
    pthread_mutex_lock(&area_mutex);
    pthread_cond_signal(&area_condition);
    pthread_mutex_unlock(&area_mutex);
}
