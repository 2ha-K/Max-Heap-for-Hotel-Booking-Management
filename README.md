# Max Heap for Hotel Booking Management

## Overview  
This project implements a **Max Heap** to manage hotel bookings efficiently.  
It supports **insertion, deletion, searching, heap sorting, and priority-based retrieval**  
while maintaining the **heap property** through **heapify and dynamic resizing**.

## Features  
- **Max Heap Implementation**:
  - Stores **Hotel Booking records** in an array-based **binary heap**.
  - Ensures the **highest confirmation number** remains at the root.
  - Supports **dynamic resizing** when capacity is reached.

- **Heap Operations**:
  - `heapInsert` – Insert a new booking while maintaining heap order.
  - `extractHeapMax` – Remove the booking with the highest confirmation number.
  - `heapIncrease` – Increase a confirmation number and adjust heap order.
  - `heapSort` – Sort bookings by confirmation number in **ascending order**.
  - `isFound` – Check if a booking exists in the heap.

- **Interactive Menu**:
  - Create, delete, print, find, insert, sort, and manipulate heap contents dynamically.

## Files  
- `Assignment3.cpp` – Main program that handles user input and executes heap operations.  
- `MaxHeap.h` – Implements the **Max Heap structure and its operations**.

## Compilation & Execution  
### **1. Compile the program:**  
```bash
g++ Assignment3.cpp -o Assignment3
