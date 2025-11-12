#pragma once

#include <cstddef>
#include <stdexcept>

#include "Interfaces.hpp"

template <typename T>
class ABQ : public QueueInterface<T> {
    std::size_t first_idx_;
    std::size_t last_idx_;
    std::size_t capacity_;
    std::size_t curr_size_;
    T* array_;
    static constexpr std::size_t scale_factor_ = 2;

   public:
    // Constructors + Big 5
    ABQ()
        : first_idx_(0),
          last_idx_(0),
          capacity_(1),
          curr_size_(0),
          array_(new T[1]) {}
    explicit ABQ(const std::size_t capacity)
        : first_idx_(0),
          last_idx_(0),
          capacity_(capacity),
          curr_size_(0),
          array_(new T[capacity]) {}

    ABQ(const ABQ& other) {
        first_idx_ = other.first_idx_;
        last_idx_ = other.last_idx_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];

        for (std::size_t i = first_idx_; i <= last_idx_; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }

        first_idx_ = rhs.first_idx_;
        last_idx_ = rhs.last_idx_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];

        for (std::size_t i = first_idx_; i <= last_idx_; i++) {
            array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABQ(ABQ&& other) noexcept {
        first_idx_ = other.first_idx_;
        last_idx_ = other.last_idx_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.first_idx_ = 0;
        other.last_idx_ = 0;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        first_idx_ = rhs.first_idx_;
        last_idx_ = rhs.last_idx_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.first_idx_ = 0;
        rhs.last_idx_ = 0;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }

    ~ABQ() noexcept {
        delete[] array_;
        first_idx_ = 0;
        last_idx_ = 0;
        capacity_ = 0;
        curr_size_ = 0;
        array_ = nullptr;
    }

    // Getters
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return curr_size_;
    }

    [[nodiscard]] std::size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
            T* temp = new T[capacity_];

            for (std::size_t i = first_idx_; i <= last_idx_; i++) {
                temp[i] = array_[i];
            }

            delete[] array_;
            array_ = temp;
        }

        array_[++last_idx_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("ABQ peek(): no elements to peek");
        }

        return array_[first_idx_];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("ABQ dequeue(): no elements to dequeue");
        }

        return array_[first_idx_++];
        curr_size_--;
    }
};
