//
// Created by roman on 11.12.2021.
//

#include "utils.h"

/*
 * Generate random int from 'from' to 'to'.
 */
int randInt(int from, int to) {
    return from + rand() % (to - from);
}