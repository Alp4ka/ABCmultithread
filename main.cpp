#include <iostream>
#include <thread>
#include <chrono>
#include "cannibal.h"
#include "chef.h"
#include "jar.h"
#include <vector>

const std::string _WRONG_INPUT_ARGS = "Wrong input arguments. \n"
                                      "Run w.o. agrgs to generate random number of Cannibals.\n"
                                      "\n"
                                      "Specify the first argument as number of Cannibals.\n"
                                      "Specify the second argument as a max capacity of Jar\n\n"
                                      "Example:\n"
                                      ".program 12 30\n";
const std::string _RANDOMIZE_INPUT_MSG = "--RANDOM INPUT MODE--";
const std::string _STANDARD_INPUT_MSG = "--STANDARD INPUT MODE--";
const int _MIN_JAR_CAPACITY = 3;
const int _MAX_JAR_CAPACITY = 15;
const int _MIN_CANNIBALS_AMOUNT = 2;
const int _MAX_CANNIBALS_AMOUNT = 10;

std::vector<Cannibal> cannibals;
Chef chef;


int main(int argc, char *argv[]) {
    // Configuration.
    srand(time(NULL));
    int cannibals_amount;
    int jar_max_capacity;
    if (argc != 1 && argc != 3) {
        std::cout << _WRONG_INPUT_ARGS << "\n";
        return 1;
    }

    std::cout << "Program configuration:\n";

    // Handling args.
    if (argc == 1) {
        std::cout << _RANDOMIZE_INPUT_MSG << "\n";
        cannibals_amount = randInt(_MIN_CANNIBALS_AMOUNT, _MAX_CANNIBALS_AMOUNT);
        jar_max_capacity = randInt(_MIN_JAR_CAPACITY, _MAX_JAR_CAPACITY);
    } else {
        std::cout << _STANDARD_INPUT_MSG << "\n";
        cannibals_amount = std::stoi(argv[1]);
        if(cannibals_amount < 1){
            std::cout << "Wrong cannibals amount!\n";
            return 1;
        }
        jar_max_capacity = std::stoi(argv[2]);
        if(jar_max_capacity < 1){
            std::cout << "Wrong max capacity!\n";
            return 1;
        }
    }
    std::cout << "Cannibals amount: " << cannibals_amount << "\n";
    std::cout << "Jar maximal capacity: " << jar_max_capacity << "\n";

    // Preparing threads.
    Jar jar(jar_max_capacity);
    chef = Chef(&jar);

    std::thread chef_thread;


    cannibals.reserve(cannibals_amount);
    for (int i = 0; i < cannibals_amount; ++i) {
        cannibals.emplace_back(&jar, &chef, i);
    }

    std::vector<std::thread> cannibals_threads;
    cannibals_threads.reserve(cannibals_amount);

    // Running threads.
    chef_thread = std::thread(&Chef::startLifecycle, &chef);
    for (int i = 0; i < cannibals_amount; ++i) {
        cannibals_threads[i] = std::thread(&Cannibal::startLifecycle, &cannibals[i]);
    }

    // Joining threads.
    for (int i = 0; i < cannibals_amount; ++i) {
        cannibals_threads[i].join();
    }
    chef_thread.join();

    return 0;
}