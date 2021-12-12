//
// Created by roman on 11.12.2021.
//

#include "chef.h"
#include "utils.h"

Chef::Chef() {

}

Chef::Chef(const Jar *jar) {
    jar_ = const_cast<Jar *>(jar);
    semaphore_ = new Semaphore(2);
    state_ = ChefState::SLEEPING;
    is_alive_ = true;
}

Chef::~Chef() {
}

/*
 * Main cycle of Chef.
 */
void Chef::startLifecycle() {
    while (true) {
        semaphore_->acquire();
        if (!is_alive_) {
            printf("Chef is dying 0_o!\n");
            return;
        }
        semaphore_->release();
        std::chrono::seconds time_sleep(1);
        std::this_thread::sleep_for(time_sleep);
    }
}

void Chef::wakeUp() {
    if (!is_alive_) {
        printf("Nothing can wake up a dead man...\n");
        return;
    }
    semaphore_->acquire();
    std::cout << "Chef is waking up!\n";
    state_ = ChefState::AWAKEN;
    cook();
    semaphore_->release();
}

/*
 * Chef starts to cook meal. He may accidentally
 * commit suicide after he finishes his work.
 * There was no such a point in the task, but it's considered
 * Chef had some mental problems.
 */
void Chef::cook() {
    printf("Chef is cooking! \n");
    while (!jar_->isFull()) {
        std::chrono::seconds time_sleep(1);
        std::this_thread::sleep_for(time_sleep);
        jar_->increaseMeatQuantity();
        printf("Dinner progress: %d/%d!\n", jar_->getMeatQuantity(), jar_->getMaxCapacity());
    }
    printf("Dinner is done! Chef may go to sleep\n");
    printf("Chef is going to sleep!\n");
    state_ = ChefState::SLEEPING;
    bool suicide = (randInt(1, 20) == 1);
    if (suicide) {
        semaphore_->acquire();
        is_alive_ = false;
        semaphore_->release();
    }
}

/*
 * Get chef state.
 */
Chef::ChefState Chef::getState() {
    semaphore_->acquire();
    ChefState result = state_;
    semaphore_->release();
    return result;
}