#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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
    char clear[LOGGER_LENGTH];

    // Save `msg` into memory
    void log(const char *msg, ...);
    void vlog(const char *msg, va_list valist);

    // Return iterator
    uint8_t getIterator();

    // Return last `offSet` log
    char *getLastLog(int offSet = 0);

private:
    char logs[LOGGER_SIZE][LOGGER_LENGTH];
    uint8_t iterator = 0; // index of last message
};

#endif