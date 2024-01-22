#ifndef CIRCULARBUFFER
#define CIRCULARBUFFER
#include <iostream>
#include "variant.hpp"
#include <array>

// Define a template variant type for different message types
template <typename... Types>
using Variant = mpark::variant<Types...>;

// Define the CircularBuffer class with std::array
template <std::size_t Capacity, typename... Types>
class CircularBuffer
{
private:
    std::array<Variant<Types...>, Capacity> buffer; // Array to store messages
    std::size_t size;                               // Current size of the buffer
    std::size_t front;                              // Index of the front element
    std::size_t rear;                               // Index of the rear element

public:
    CircularBuffer() : size(0), front(0), rear(0) {}

    // Function to add a message to the buffer
    template <typename MessageType>
    void enqueue(const MessageType &message)
    {
        if (isFull())
        {
            // Buffer is full, overwrite the oldest message
            front = (front + 1) % Capacity;
        }

        buffer[rear] = message;
        rear = (rear + 1) % Capacity;
        size = std::min(size + 1, Capacity); // Update size
    }
    Variant<Types...> dequeue()
    {
        if (isEmpty())
        {
            // Buffer is empty, return a default-constructed variant
            return {};
        }

        Variant<Types...> result = buffer[front];
        front = (front + 1) % Capacity;
        size = std::max(size - 1, static_cast<std::size_t>(0)); // Update size
        return result;
    }
    // Helper function to check if the buffer is empty
    bool isEmpty() const
    {
        return size == 0;
    }

    // Helper function to check if the buffer is full
    bool isFull() const
    {
        return size == Capacity;
    }

private:
};

#endif