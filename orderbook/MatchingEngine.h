#pragma once
#include "LimitOrderBook.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>

class MatchingEngine {
private:
    LimitOrderBook orderBook;
    
    // The concurrent order queue
    std::queue<Order> incomingOrders; 
    
    // Synchronization primitives mentioned on your resume
    std::mutex mtx;
    std::condition_variable cv;
    
    std::atomic<bool> isRunning;
    std::thread workerThread;

    // The infinite loop running on the worker thread
    void processQueue();

public:
    MatchingEngine();
    ~MatchingEngine();

    // Thread-safe entry point used by external components to submit orders
    void submitOrder(const Order& order);
    
    void start();
    void stop();
};
