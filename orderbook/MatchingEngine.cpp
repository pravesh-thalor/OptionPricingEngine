#include "MatchingEngine.h"
#include <iostream>

// Constructor initializes the running state to false
MatchingEngine::MatchingEngine() : isRunning(false) {}

// Destructor ensures the worker thread is cleanly shut down
MatchingEngine::~MatchingEngine() {
    stop();
}

void MatchingEngine::start() {
    if (!isRunning) {
        isRunning = true;
        // Spawn the worker thread to run the processQueue loop
        workerThread = std::thread(&MatchingEngine::processQueue, this);
    }
}

void MatchingEngine::stop() {
    if (isRunning) {
        isRunning = false;
        // Wake up the worker thread in case it is sleeping/waiting
        cv.notify_all(); 
        
        // Wait for the worker thread to finish its current execution before destroying
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }
}

void MatchingEngine::submitOrder(const Order& order) {
    // 1. Lock the mutex to ensure exclusive access to the queue
    {
        std::lock_guard<std::mutex> lock(mtx);
        incomingOrders.push(order);
    } // Mutex is automatically released when lock_guard goes out of scope

    // 2. Ping the condition variable to wake up the worker thread
    cv.notify_one(); 
}

void MatchingEngine::processQueue() {
    while (isRunning) {
        Order currentOrder(0, OrderType::Market, Side::Buy, 0.0, 0); 
        bool hasOrder = false;

        // Use a unique_lock which can be locked and unlocked dynamically by the condition_variable
        {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Put the thread to sleep until the queue is not empty OR the engine is stopped.
            // This prevents the thread from burning CPU cycles in a busy-wait loop.
            cv.wait(lock, [this] { return !incomingOrders.empty() || !isRunning; });

            // If the engine was stopped and all orders are processed, exit the loop
            if (!isRunning && incomingOrders.empty()) {
                break;
            }

            // Safely pop the next order off the queue
            if (!incomingOrders.empty()) {
                currentOrder = incomingOrders.front();
                incomingOrders.pop();
                hasOrder = true;
            }
        } // IMPORTANT: The mutex unlocks here BEFORE processing the order. 
          // This allows new orders to be submitted to the queue while the current one is being matched.

        if (hasOrder) {
            // Route the order based on its specific execution type
            if (currentOrder.type == OrderType::FOK) {
                orderBook.processFillOrKill(currentOrder);
            } else if (currentOrder.type == OrderType::IOC) {
                orderBook.processImmediateOrCancel(currentOrder);
            } else {
                orderBook.addOrder(currentOrder);
            }
            
            // Attempt to cross the spread and generate trades
            orderBook.matchOrders();
        }
    }
}
