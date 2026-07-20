# High-Performance C++ Limit Order Book & Matching Engine

This module implements a thread-safe, low-latency limit order book (LOB) and matching engine in modern C++. It is designed to simulate high-frequency trading infrastructure by decoupling order submission from order execution using concurrent programming techniques.

## Key Features

* **Price-Time Priority:** Orders are matched strictly based on best price, followed by the earliest submission time.
* **Thread-Safe Architecture:** Utilizes `std::mutex` and `std::condition_variable` to safely manage concurrent order flows from multiple threads.
* **Low-Latency Processing:** The matching engine runs on a dedicated, asynchronous worker thread. It uses an event-driven sleep state (`cv.wait()`) to ensure 0% CPU consumption when idle, instantly waking upon order arrival.
* **Advanced Order Types:** Fully supports standard and complex execution instructions:
  * **Market & Limit** Orders
  * **FOK** (Fill or Kill)
  * **IOC** (Immediate or Cancel)
  * **GFD** (Good for Day) with automatic pruning of expired orders.

## System Architecture

The codebase is highly modular and strictly adheres to Object-Oriented Programming (OOP) principles.

* `Order.h`: Defines the core data payload, including automatic nanosecond-precision timestamping upon instantiation.
* `LimitOrderBook.h` / `.cpp`: The core execution logic. Uses a `std::map` (Red-Black Tree) for fast $O(\log N)$ price level lookups and a nested `std::deque` for $O(1)$ time-priority queuing. 
* `MatchingEngine.h` / `.cpp`: The concurrent wrapper around the LOB. Manages a synchronized `std::queue` to buffer incoming orders and dispatches them to the LOB without blocking the upstream systems.

## Getting Started

### Prerequisites
* A C++11 (or higher) compliant compiler (GCC, Clang, or MSVC)
* CMake (3.10+)

### Building the Project
Since this is integrated into the broader Option Pricing Engine, it is built via the root CMake configuration. You can compile it independently for testing:

```bash
mkdir build && cd build
cmake ..
make
