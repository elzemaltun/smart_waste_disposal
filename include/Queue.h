#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

template <typename T>
class Queue {
private:
    static const int MAX_SIZE = 10; // Adjust size as needed
    T buffer[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    Queue() : front(0), rear(0), count(0) {}

    // Add an item to the queue
    bool enqueue(const T& item) {
        if (isFull()) {
            return false; // Queue is full
        }
        buffer[rear] = item;
        rear = (rear + 1) % MAX_SIZE;
        count++;
        return true;
    }

    // Remove and return the front item
    T dequeue() {
        if (isEmpty()) {
            return T(); // Return default value if empty
        }
        T item = buffer[front];
        front = (front + 1) % MAX_SIZE;
        count--;
        return item;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Check if the queue is full
    bool isFull() const {
        return count == MAX_SIZE;
    }

    // Get the current size of the queue
    int size() const {
        return count;
    }
};

#endif // QUEUE_H
