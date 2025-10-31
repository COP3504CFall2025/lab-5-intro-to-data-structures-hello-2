#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABQ : public QueueInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

   public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABQ(const size_t capacity)
        : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABQ(ABQ&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }

    ~ABQ() noexcept override {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
        array_ = nullptr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;
};
