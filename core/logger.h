#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "config.h"
#include "filesystem.h"

#ifndef LOGGER_H
#define LOGGER_H

/**
 * Logger can store 256 messages
 * channels:
 *  0 - log
 *  1 - err
 *  2 - war
 */
class Logger
{
public:
    Logger(FileSystem *fsn);

    // Save `msg` into memory
    void log(const char msg[LOGGER_MAX_LENGTH], ...);
    void err(const char msg[LOGGER_MAX_LENGTH], ...);
    void war(const char msg[LOGGER_MAX_LENGTH], ...);
    void vlog(const char msg[LOGGER_MAX_LENGTH], va_list valist, uint8_t channel);
    void vlog(const char msg[LOGGER_MAX_LENGTH], va_list valist, uint8_t channel, const char prefix[LOGGER_LENGTH], ...);
    void vvlog(const char msg[LOGGER_MAX_LENGTH], ...);
    void vvlog(const char msg[LOGGER_MAX_LENGTH], va_list valist, const char prefix[LOGGER_LENGTH], va_list valist2);

    // Return iterator
    uint8_t getIterator();

    // Return last `offSet` log
    char *getLastLog(int offSet = 0);

private:
    char logs[LOGGER_SIZE][LOGGER_LENGTH];
    char prepstr[LOGGER_MAX_LENGTH];
    uint8_t iterator = 0; // index of last message
    FileSystem *fs;

    void __savelog(char *msg);

    /*
     * Find "", "ERR: " or "WAR: " by channel
     * return malloc -> need to be deleted manualy
     */
    char *__findPref(uint8_t channel);
};

#endif