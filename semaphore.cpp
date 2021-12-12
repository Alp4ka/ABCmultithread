//
// Created by roman on 10.12.2021.
//

#include "semaphore.h"

// Acquire semaphore.
void Semaphore::acquire() {
    std::unique_lock<decltype(mutex_)> lock(mutex_);
    while (count_ == 0) {
        condition_.wait(lock);
    }
    --count_;
}

Semaphore::Semaphore(int count) {
    count_ = count;
}

bool Semaphore::tryAcquire() {
    std::lock_guard<decltype(mutex_)> lock(mutex_);
    if (count_ > 0) {
        --count_;
        return true;
    }
    return false;
    // unlocks.
}

/*
 * Release semaphore.
 */
void Semaphore::release() {
    std::lock_guard<decltype(mutex_)> lock(mutex_);
    ++count_;
    condition_.notify_one();
    // unlocks.
}
