## Overview
This lab demonstrates how to build and traverse a circular linked list using C++ smart pointers:

1. Server side uses `shared_ptr` to create and print the list.  
2. Client side uses `weak_ptr` to traverse and detect when the list has been deleted.

## Prerequisites
- A C++17-compatible compiler (e.g. `g++` or `clang++`).
- No external libraries are required beyond the standard library.

## Files
- `Node.h`  
- `LinkedList.h`  
- `lab.cpp` (weak-pointer version + tests)  
- `main_shared.cpp` (shared-pointer only demo)  

## Build & Run

### 1. Weak-pointer version with tests
```bash
g++ -std=c++17 lab.cpp -o demo_weak
./demo_weak
```
You should see:
- Server (step 2): six nodes, printed with `use_count` and addresses  
- Client (step 3): same six nodes via `weak_ptr`  
- Server deletes the list  
- Client (step 5): detects no `shared_ptr` and prints “[Nothing]”

### 2. Shared-pointer only demo
```bash
g++ -std=c++17 main_shared.cpp -o demo_shared
./demo_shared
```
You’ll see the circular list printed, then the vector cleared, then the first node’s counts and next pointer.

## Expected Output
```
Server (step 2):
[zero] : use_count: 3 address: 0x... next (from shared_ptr): 0x...
...

Client (step 3):
[zero] : use_count: 3 address: 0x... next (from weak_ptr): 0x...
...

Server is deleting the shared_ptrs (step 4)

Client after linked list deleted (step 5):
[Nothing]
```

