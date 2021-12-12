//
// Created by roman on 11.12.2021.
//

#ifndef ABC5_CANNIBAL_H
#define ABC5_CANNIBAL_H

#include "jar.h"
#include "chef.h"
#include "utils.h"

class Cannibal {
public:
private:
    static const int kSatisfactionMaxLevel = 100;
    static const int kSatisfyDecreaseStep = 20;
    int satisfaction_;
    int tries_do_die_;
    Jar *jar_;
    Chef *chef_;
    int id_;

    void eat();

    void decreaseSatisfaction();

    Semaphore *semaphore;
public:
    explicit Cannibal(const Jar *jar, const Chef *chef, int id);

    ~Cannibal();

    void startLifecycle();
};


#endif //ABC5_CANNIBAL_H
