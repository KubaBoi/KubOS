#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"

#ifndef LOGGER_H
#define LOGGER_H

/**
 * Logger can store 256 messages
 */
class Logger
{
public:
    Logger();

    // Save `msg` into memory
    void log(char *msg);

    // Return iterator
    uint8_t getIterator();

    // Return last `offSet` log
    char *getLastLog(uint8_t offSet = 0);

private:
    char logs[LOGGER_SIZE][LOGGER_LENGTH];
    uint8_t iterator = 0; // index of last message
};

#endif