//
// Created by roman on 11.12.2021.
//

#ifndef ABC5_CHEF_H
#define ABC5_CHEF_H


#include "jar.h"
#include <iostream>

class Chef {
public:
    enum ChefState {
        SLEEPING,
        AWAKEN
    };
private:
    ChefState state_;
    Jar *jar_;
    Semaphore *semaphore_;
    bool is_alive_;

    void cook();

public:
    Chef();

    explicit Chef(const Jar *jar);

    ~Chef();

    void startLifecycle();

    ChefState getState();

    void wakeUp();
};


#endif //ABC5_CHEF_H
