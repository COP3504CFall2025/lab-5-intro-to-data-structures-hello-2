#pragma once

#include <cstddef>
#include <stdexcept>

#include "Interfaces.hpp"

template <typename T>
class ABDQ : public DequeInterface<T> {
   private:
    T* data_;               // underlying dynamic array
    std::size_t capacity_;  // total allocated capacity
    std::size_t size_;      // number of stored elements
    std::size_t front_;     // index of front element
    std::size_t back_;      // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

   public:
    // Big 5
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t capacity)
        : data_(new T[capacity]),
          capacity_(capacity),
          size_(0),
          front_(0),
          back_(0) {}

    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        for (std::size_t i = front_; i < back_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }

        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        for (std::size_t i = front_; i < back_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }

    ~ABDQ() noexcept {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("ABDQ popFront(): no elements to pop");
        }

        T el = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return el;
    }

    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("ABDQ popBack(): no elements to pop");
        }

        T el = data_[back_ - 1];
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        size_--;
        shrinkIfNeeded();
        return el;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("ABQ front(): no elements in deque");
        }

        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("ABQ front(): no elements in deque");
        }

        return data_[back_ - 1];
    }

    void ensureCapacity() {
        if (size_ == capacity_) {
            std::size_t new_capacity = capacity_ * SCALE_FACTOR;
            T* temp = new T[new_capacity];

            for (std::size_t i = front_, j = front_ + capacity_;
                 i < front_ + size_; i++, j++) {
                temp[j % new_capacity] = data_[i % capacity_];
            }

            delete[] data_;
            data_ = temp;
            front_ += capacity_;
            capacity_ = new_capacity;
        }
    }

    void shrinkIfNeeded() {
        if (size_ < capacity_ / (SCALE_FACTOR * SCALE_FACTOR)) {
            std::size_t new_capacity = capacity_ / SCALE_FACTOR;
            T* temp = new T[new_capacity];

            for (std::size_t i = front_, j = front_ - new_capacity;
                 i < front_ + size_; i++, j++) {
                temp[j % new_capacity] = data_[i % capacity_];
            }

            delete[] data_;
            data_ = temp;
            front_ -= new_capacity;
            capacity_ = new_capacity;
        }
    }

    // Getters
    std::size_t getSize() const noexcept override { return size_; }
};
