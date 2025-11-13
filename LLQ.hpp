#pragma once

#include <stdlib.h>

#include <stdexcept>

#include "Interfaces.hpp"
#include "LinkedList.hpp"

template <typename T>
class LLQ : public QueueInterface<T> {
   private:
    LinkedList<T> list;

   public:
    // Insertion
    void enqueue(const T& item) override { list.addTail(item); }

    // Deletion
    T dequeue() override {
        T data;

        if (list.getHead()) {
            data = list.getHead()->data;
        }

        if (!list.removeHead()) {
            throw std::runtime_error("LLQ dequeue(): no elements to dequeue");
        }

        return data;
    }

    // Access
    T peek() const override {
        if (!list.getHead()) {
            throw std::runtime_error("LLQ peek(): no elements to peek");
        }

        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }
};
