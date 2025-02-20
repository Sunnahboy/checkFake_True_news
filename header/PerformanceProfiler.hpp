#ifndef PERFORMANCE_PROFILER_HPP
#define PERFORMANCE_PROFILER_HPP


#include <iostream>
#include <chrono>
#include <string>

#ifdef _WIN32
  #include <windows.h>
  #ifdef byte
    #undef byte  // Undefine 'byte' to avoid conflict with std::byte
  #endif
  #include <psapi.h>
#elif defined(__APPLE__)
  #include <sys/resource.h>
#else
  #include <sys/resource.h>
#endif

// Function to get memory usage in kilobytes
inline long getMemoryUsageKB() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return static_cast<long>(pmc.WorkingSetSize / 1024);
    }
    return -1; // Error indicator.
#elif defined(__APPLE__)
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss / 1024; // Convert to kilobytes.
#else
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Already in kilobytes on Linux.
#endif
}

// Structure to hold performance metrics
struct PerformanceMetrics {
    double timeSeconds; // Elapsed time (seconds)
    long memoryKB;      // Memory change (in KB)
};

// Function to measure performance of a given function
template<typename Func, typename... Args>
PerformanceMetrics measurePerformance(Func func, Args... args) {
    long memBefore = getMemoryUsageKB();
    auto start = std::chrono::high_resolution_clock::now();

    func(args...); // Call the function with the provided arguments

    auto end = std::chrono::high_resolution_clock::now();
    long memAfter = getMemoryUsageKB();
    std::chrono::duration<double> elapsed = end - start;

    PerformanceMetrics metrics;
    metrics.timeSeconds = elapsed.count();
    metrics.memoryKB = memAfter - memBefore;
    return metrics;
}

// Overloaded measurePerformance for member functions
template<typename T, typename Func, typename... Args>
PerformanceMetrics measurePerformance(T* instance, Func func, Args... args) {
    long memBefore = getMemoryUsageKB();
    auto start = std::chrono::high_resolution_clock::now();

    (instance->*func)(args...); // Call the member function on the instance


    auto end = std::chrono::high_resolution_clock::now();
    long memAfter = getMemoryUsageKB();
    std::chrono::duration<double> elapsed = end - start;

    PerformanceMetrics metrics;
    metrics.timeSeconds = elapsed.count();
    metrics.memoryKB = memAfter - memBefore;
    return metrics; 
}

// Function to profile an algorithm
template<typename Func, typename... Args>
PerformanceMetrics profileAlgorithm(const std::string& algorithmName,
                                     const std::string& theoreticalTime,
                                     const std::string& theoreticalSpace,
                                     Func func, Args... args) {
    PerformanceMetrics metrics = measurePerformance(func, args...);

    

    std::cout << "Algorithm: " << algorithmName << "\n";
    std::cout << "  Theoretical Worse Case Time Complexity: " << theoreticalTime << "\n";
    std::cout << "  Theoretical Worse Case Space Complexity: " << theoreticalSpace << "\n";
    std::cout << "  Measured Time: " << metrics.timeSeconds << " seconds\n";
    std::cout << "  Measured Memory Change: " << metrics.memoryKB << " KB\n";
    std::cout << "--------------------------------------------\n";

    return metrics;
}

// Overloaded profileAlgorithm for member functions
template<typename T, typename Func, typename... Args>
PerformanceMetrics profileAlgorithm(T* instance, const std::string& algorithmName,
                                     const std::string& theoreticalTime,
                                     const std::string& theoreticalSpace,
                                     Func func, Args... args) {
    PerformanceMetrics metrics = measurePerformance(instance, func, args...);

    std::cout << "Algorithm: " << algorithmName << "\n";
    std::cout << "  Theoretical Time Complexity: " << theoreticalTime << "\n";
    std::cout << "  Theoretical Space Complexity: " << theoreticalSpace << "\n";
    std::cout << "  Measured Time: " << metrics.timeSeconds << " seconds\n";
    std::cout << "  Measured Memory Change: " << metrics.memoryKB << " KB\n";
    std::cout << "--------------------------------------------\n";

    return metrics;
}

#endif // PERFORMANCE_PROFILER_HPP
