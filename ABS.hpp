#pragma once

#include <cstddef>
#include <stdexcept>

#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABS : public StackInterface<T> {
   public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity)
        : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];

        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABS& operator=(const ABS& other) {
        if (this == &other) {
            return *this;
        }

        delete[] array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];

        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }

        return *this;
    }

    ABS(ABS&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }

    ABS& operator=(ABS&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;

        return *this;
    }

    ~ABS() noexcept {
        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
            T* new_array = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                new_array[i] = array_[i];
            }

            delete[] array_;
            array_ = new_array;
        }

        array_[curr_size_++] = data;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("ABS peek(): no elements to peek");
        }

        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("ABS pop(): no elements to pop");
        }

        T el = array_[--curr_size_];
        // if (curr_size_ == capacity_ / scale_factor_) {
        //     capacity_ /= scale_factor_;
        //     T* temp = new T[capacity_];
        //
        //     for (std::size_t i = 0; i < curr_size_; i++) {
        //         temp[i] = array_[i];
        //     }
        //
        //     delete[] array_;
        //     array_ = temp;
        // }

        return el;
    }

   private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
