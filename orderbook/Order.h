#pragma once
#include <cstdint>
#include <chrono>

enum class OrderType { Market, Limit, FOK, IOC, GFD };
enum class Side { Buy, Sell };

struct Order {
    uint64_t orderId;
    OrderType type;
    Side side;
    double price;       // 0 for Market orders
    uint32_t quantity;
    uint64_t timestamp; // For Time priority

    Order(uint64_t id, OrderType t, Side s, double p, uint32_t q)
        : orderId(id), type(t), side(s), price(p), quantity(q) {
        // Automatically assign nanosecond timestamp upon creation
        timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    }
};
