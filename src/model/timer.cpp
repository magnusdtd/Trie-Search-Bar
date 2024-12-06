#include <iostream>
#include <chrono>
#include <functional>

class Timer {
public:
    // Constructor starts the timer
    Timer() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    // Destructor stops the timer and prints the elapsed time
    ~Timer() {
        stop();
    }

    // Stops the timer and calculates elapsed time
    void stop() {
        if (!stopped) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

            elapsedTime = end - start;
            stopped = true;

            std::cout << "Elapsed Time: " << elapsedTime << " microseconds" << std::endl;
        }
    }

    // Getter for elapsed time (in microseconds)
    long long getElapsedTime() const {
        return elapsedTime;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    long long elapsedTime = 0;
    bool stopped = false;
};

// Function to measure execution time of another function
template <typename Func, typename... Args>
long long measureExecutionTime(Func&& func, Args&&... args) {
    Timer timer; // Timer will automatically start
    func(std::forward<Args>(args)...); // Execute the function
    return timer.getElapsedTime(); // Return elapsed time
}

// Example function to test timing
void exampleFunction() {
    for (volatile int i = 0; i < 1e6; ++i); // Some dummy workload
}

int main() {
    // Method 1: Directly use Timer
    {
        Timer timer; // Timer starts
        exampleFunction();
    } // Timer automatically stops when it goes out of scope

    // Method 2: Measure time with utility function
    long long timeTaken = measureExecutionTime(exampleFunction);
    std::cout << "Function executed in " << timeTaken << " microseconds using utility function.\n";

    return 0;
}
