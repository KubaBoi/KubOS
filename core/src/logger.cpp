#include "logger.h"

Logger::Logger()
{
    for (int i = 0; i < LOGGER_SIZE; i++)
    {
        memset(logs[i], ' ', LOGGER_LENGTH);
        logs[i][LOGGER_LENGTH - 1] = 0;
    }
}

void Logger::log(const char *msg, ...)
{
    va_list valist;
    va_start(valist, msg);
    vlog(msg, valist);
}

void Logger::vlog(const char *msg, va_list valist)
{
    vsnprintf(prepstr, LOGGER_MAX_LENGTH, msg, valist);
    __savelog(prepstr);
}

void Logger::__savelog(char *msg)
{
    char *alog = logs[iterator++];
    alog = strncpy(alog, msg, LOGGER_LENGTH);
    uint16_t length = strlen(alog);
    if (length >= LOGGER_LENGTH)
        __savelog(msg + LOGGER_LENGTH);
    else
    {
        memset(alog + length, ' ', LOGGER_LENGTH - length);
        alog[LOGGER_LENGTH - 1] = 0;
    }
}

uint8_t Logger::getIterator() { return iterator; }

char *Logger::getLastLog(int offSet)
{
    return logs[(uint8_t)(iterator - offSet)];
}