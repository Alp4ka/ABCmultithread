//
// Created by roman on 11.12.2021.
//


#include "jar.h"

Jar::Jar(int jar_max_capacity) {
    max_capacity_ = jar_max_capacity;
    meat_quantity_ = 0;
    semaphore_ = new Semaphore(1);
    is_blocked_ = false;
}

Jar::~Jar() {
    delete semaphore_;
    semaphore_ = nullptr;
}

/*
 * Decreases meat quantity.
 */
bool Jar::decreaseMeatQuantity() {
    bool result = true;
    semaphore_->acquire();
    if (meat_quantity_ > 0) {
        --meat_quantity_;
        printf("Meat quanity: %d/%d!\n", meat_quantity_, max_capacity_);
    } else {
        result = false;
    }
    semaphore_->release();
    return result;
}

/*
 * Increase meat quantity.
 */
bool Jar::increaseMeatQuantity() {
    bool result = true;
    semaphore_->acquire();
    if (meat_quantity_ < max_capacity_) {
        ++meat_quantity_;
        printf("Meat quanity: %d/%d!\n", meat_quantity_, max_capacity_);
    } else {
        result = false;
    }
    semaphore_->release();
    return result;
}

/*
 * Get meat quantity.
 */
int Jar::getMeatQuantity() {
    semaphore_->acquire();
    int meat_quantity = meat_quantity_;
    semaphore_->release();
    return meat_quantity;
}

/*
 * Set meat quantity.
 */
void Jar::setMeatQuantity(int quantity) {
    semaphore_->acquire();
    meat_quantity_ = quantity;
    semaphore_->release();
}

/*
 * Check whether the jar is full.
 * @return true whether thr jar is full, false - otherwise.
 */
bool Jar::isFull() {
    semaphore_->acquire();
    bool result = (meat_quantity_ == max_capacity_);
    semaphore_->release();
    return result;
}

/*
 * Get max jar capacity.
 */
int Jar::getMaxCapacity() {
    semaphore_->acquire();
    int result = max_capacity_;
    semaphore_->release();
    return result;
}

/*
 * Check whether the jar is blocked by another cannibal.
 * @return true whether the jar is blocked, false - otherwise.
 */
bool Jar::isBlocked() {
    semaphore_->acquire();
    int result = is_blocked_;
    semaphore_->release();
    return result;
}

/*
 * Block jar.
 */
void Jar::block() {
    semaphore_->acquire();
    is_blocked_ = true;
    semaphore_->release();
}

/*
 * Unblock jar.
 */
void Jar::unblock() {
    semaphore_->acquire();
    is_blocked_ = false;
    semaphore_->release();
}

/*
 * Try to block jar.
 * Returns true if it is possible, false - otherwise.
 */
bool Jar::tryBlock() {
    bool result;
    semaphore_->acquire();
    if (is_blocked_) {
        result = false;
    } else {
        is_blocked_ = true;
        result = true;
    }
    semaphore_->release();
    return result;
}