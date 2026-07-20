#pragma once
#include "Order.h"
#include <map>
#include <deque>

class LimitOrderBook {
private:
    // Bids (Buy orders) sorted descending (highest price first)
    std::map<double, std::deque<Order>, std::greater<double>> bids;
    
    // Asks (Sell orders) sorted ascending (lowest price first)
    std::map<double, std::deque<Order>> asks;

public:
    // Core book operations
    void addOrder(const Order& order);
    void cancelOrder(uint64_t orderId);
    
    // Crosses the spread to generate trades
    void matchOrders(); 
    
    // Automatic pruning for Good-For-Day (GFD) orders
    void pruneExpiredOrders(); 

    // Specific logic for complex execution types
    bool processFillOrKill(const Order& order);
    void processImmediateOrCancel(const Order& order);
};
