//
// Created by roman on 11.12.2021.
//

#ifndef ABC5_JAR_H
#define ABC5_JAR_H

#include "semaphore.h"
#include <thread>
#include <iostream>

class Jar {
private:
    int max_capacity_;
    int meat_quantity_;
    Semaphore *semaphore_;
    bool is_blocked_;
public:
    Jar();

    Jar(int jar_max_capacity);

    ~Jar();

    bool decreaseMeatQuantity();

    bool increaseMeatQuantity();

    int getMeatQuantity();

    void setMeatQuantity(int quantity);

    bool isFull();

    int getMaxCapacity();

    bool isBlocked();

    void block();

    void unblock();

    bool tryBlock();
};


#endif //ABC5_JAR_H
