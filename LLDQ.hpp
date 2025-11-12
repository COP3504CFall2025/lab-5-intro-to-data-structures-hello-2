#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "Interfaces.hpp"
#include "LinkedList.hpp"

template <typename T>
class LLDQ : public DequeInterface<T> {
   private:
    LinkedList<T> list;

   public:
    // Core Insertion Operations
    void pushFront(const T& item) override { list.addHead(item); }

    void pushBack(const T& item) override { list.addTail(item); }

    // Core Removal Operations
    T popFront() override {
        T data;

        if (list.getHead()) {
            data = list.getHead()->data;
        }

        if (!list.removeHead()) {
            throw std::runtime_error("LLDQ popFront(): no element to remove");
        }

        return data;
    }

    T popBack() override {
        T data;

        if (list.getTail()) {
            data = list.getTail()->data;
        }

        if (!list.removeTail()) {
            throw std::runtime_error("LLDQ popBack(): no element to remove");
        }

        return data;
    }

    // Element Accessors
    const T& front() const override { return list.getHead()->data; }

    const T& back() const override { return list.getTail()->data; }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }
};
