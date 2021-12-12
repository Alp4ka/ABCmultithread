//
// Created by roman on 10.12.2021.
//

#ifndef ABC5_SEMAPHORE_H
#define ABC5_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    std::condition_variable condition_;
    std::mutex mutex_;
    int count_;

public:
    Semaphore(int count = 1);

    void acquire();

    bool tryAcquire();

    void release();

};


#endif //ABC5_SEMAPHORE_H
