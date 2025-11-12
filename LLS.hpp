#pragma once

#include <stdlib.h>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"

template <typename T>
class LLS : public StackInterface<T> {
   private:
    LinkedList<T> list;

   public:
    // Insertion
    void push(const T& item) override { list.addHead(item); }

    // Deletion
    T pop() override {
        T data;

        if (list.getHead()) {
            data = list.getHead()->data;
        }

        if (!list.removeHead()) {
            throw std::runtime_error("LLS pop(): no element to remove");
        }

        return data;
    }

    // Access
    T peek() const override { return list.getTail()->data; }

    // Getters
    std::size_t getSize() const noexcept override { return list.getCount(); }
};
