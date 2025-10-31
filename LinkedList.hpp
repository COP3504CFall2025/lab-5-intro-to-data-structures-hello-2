#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
   private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    // Stores pointers to first and last nodes and count
    Node* head = nullptr;
    Node* tail = nullptr;
    unsigned int count = 0;

   public:
    // Behaviors
    void printForward() const {
        Node* iter = head;

        std::cout << "{";
        while (iter) {
            std::cout << iter->data << iter->next ? ", " : "";
            iter = iter->next;
        }
        std::cout << "}" << std::endl;
    }

    void PrintReverse() const {
        Node* iter = tail;

        std::cout << "{";
        while (iter) {
            std::cout << iter->data << iter->prev ? ", " : "";
            iter = iter->prev;
        }
        std::cout << "}" << std::endl;
    }

    // Accessors
    [[nodiscard]] unsigned int getCount() const { return count; }
    Node* getHead() { return head; }
    const Node* getHead() const { return head; }
    Node* getTail() { return tail; }
    const Node* getTail() const { return tail; }

    // Insertion
    void AddHead(const T& data) {
        Node* new_head = new Node(data, nullptr, head);
        head = new_head;
        count++;
    }

    void AddTail(const T& data) {
        Node* new_tail = new Node(data, tail, nullptr);
        tail = new_tail;
        count++;
    }

    // Removal
    bool RemoveHead() {
        if (!head) {
            return false;
        }

        delete head;
        head = head->next;
        count--;
        return true;
    }

    bool RemoveTail() {
        if (!tail) {
            return false;
        }

        delete tail;
        tail = tail->prev;
        count--;
        return true;
    }

    void Clear() {
        while (head) {
            RemoveHead();
        }
    }

    // Operators
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Clear();
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

        return *this;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this == &other) {
            return *this;
        }

        Clear();
        Node* iter = other.head;
        while (iter) {
            AddTail(iter->data);
            iter = iter->next;
        }

        return *this;
    }

    // Construction/Destruction
    LinkedList() {}
    LinkedList(const LinkedList<T>& list) {
        Node* iter = list.head;
        while (iter) {
            AddTail(iter->data);
            iter = iter->next;
        }
    }

    LinkedList(LinkedList<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    ~LinkedList() { Clear(); }
};
