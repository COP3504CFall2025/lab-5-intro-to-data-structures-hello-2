#ifdef MAIN

#include <iostream>

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include "LinkedList.hpp"

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH
   GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration
   in CLion, or through your own command line compilation. Make sure to add flag
   "-DMAIN" to your compilation so this main function can compile.

*/

int main() {
    // ABDQ<int> test;
    // test.pushFront(1);
    // test.pushFront(2);
    // test.pushFront(3);
    // test.pushFront(4);
    // test.pushFront(5);
    // test.pushBack(6);
    // test.pushBack(7);
    // test.pushBack(8);
    // test.pushBack(9);
    // test.pushBack(10);
    // std::cout << test.front() << std::endl;  // 5
    // std::cout << test.back() << std::endl;   // 10
    //
    // ABDQ<int> test2 = ABDQ<int>(4);
    // std::cout << test2.capacity_ << std::endl;  // 4
    // test = ABDQ<int>(4);

    LinkedList<int> list;
    list.addHead(1);
    list.removeHead();
    std::cout << list.getTail() << std::endl;
    std::cout << list.getHead() << std::endl;
    // list.addHead(2);
    // list.addHead(3);
    // list.addHead(4);
    // list.addHead(5);
    // list.addTail(6);
    // list.addTail(7);
    // list.addTail(8);
    // list.addTail(9);
    // list.addTail(10);

    LLQ<int> llq;
    llq.enqueue(1);
    llq.enqueue(2);
    llq.enqueue(3);
    llq.enqueue(4);
    llq.enqueue(5);
    llq.enqueue(6);
    llq.enqueue(7);
    llq.enqueue(8);

    ABQ<int> abq;
    abq.enqueue(1);
    abq.enqueue(2);
    abq.enqueue(3);
    abq.enqueue(4);
    abq.enqueue(5);

    return 0;
}

#endif
