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

    void printReverse() const {
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
    void addHead(const T& data) {
        Node* new_head = new Node(data, nullptr, head);
        head = new_head;
        count++;
    }

    void addTail(const T& data) {
        Node* new_tail = new Node(data, tail, nullptr);
        tail = new_tail;
        count++;
    }

    // Removal
    bool removeHead() {
        delete head;
        head = head->next;
        count--;
    }

    bool removeTail() {
        delete tail;
        tail = tail->prev;
        count--;
    }

    void clear() {
        while (head) {
            removeHead();
        }
    }

    // Operators
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clear();
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

        clear();
        Node* iter = other.head;
        while (iter) {
            addTail(iter->data);
            iter = iter->next;
        }

        return *this;
    }

    // Construction/Destruction
    LinkedList() {}
    LinkedList(const LinkedList<T>& list) {
        Node* iter = list.head;
        while (iter) {
            addTail(iter->data);
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

    ~LinkedList() { clear(); }
};
