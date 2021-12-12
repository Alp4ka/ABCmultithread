//
// Created by roman on 11.12.2021.
//

#include "cannibal.h"

Cannibal::Cannibal(const Jar *jar, const Chef *chef, int id) {
    id_ = id;
    jar_ = const_cast<Jar *>(jar);
    chef_ = const_cast<Chef *>(chef);
    tries_do_die_ = randInt(10, 20);
    satisfaction_ = randInt(0, kSatisfactionMaxLevel);
}

Cannibal::~Cannibal() {
}

/*
 * Main cycle of cannibal.
 */
void Cannibal::startLifecycle() {
    while (true) {
        if (!tries_do_die_) {
            printf("Cannibal#%d got poisoned 0_o!\n", id_);
            return;
        }
        if (satisfaction_ == 0) {
            printf("Cannibal#%d wants to eat!\n", id_);
            if (jar_->tryBlock()) {
                eat();
                jar_->unblock();
                --tries_do_die_;
            }
        }
        decreaseSatisfaction();
        std::chrono::seconds time_sleep(1);
        std::this_thread::sleep_for(time_sleep);
    }
}

/*
 * Call cannibal to go for dinner.
 */
void Cannibal::eat() {
    if (jar_->getMeatQuantity() == 0) {
        // There is no reason to wake up a chef if he is already working.
        if (chef_->getState() == Chef::ChefState::AWAKEN) {
            while (chef_->getState() != Chef::ChefState::SLEEPING) {
                // Keep waiting until the chef finishes his work.
            }
        } else {
            printf("Cannibal#%d noticed the jar is empty!\n", id_);
            printf("Cannibal#%d calls chef!\n", id_);
            chef_->wakeUp();
            while (!jar_->isFull()) {
            }
        }
    }
    printf("Cannibal#%d is going to eat!\n", id_);
    jar_->decreaseMeatQuantity();
    satisfaction_ = kSatisfactionMaxLevel;
    printf("Cannibal#%d is satisfied!\n", id_);
}

/*
 * Decrease level of satisfaction by one.
 */
void Cannibal::decreaseSatisfaction() {
    satisfaction_ -= kSatisfyDecreaseStep;
    if (satisfaction_ < 0) {
        satisfaction_ = 0;
    }
}
