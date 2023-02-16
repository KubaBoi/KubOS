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

    char *getLastLog();

private:
    char addresses[LOGGER_LENGTH][LOGGER_SIZE];
    uint8_t iterator = 0; // index of last message
};

#endif