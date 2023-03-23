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
    vlog(msg, valist, 0);
}

void Logger::err(const char *msg, ...)
{
    va_list valist;
    va_start(valist, msg);
    vlog(msg, valist, 1);
}

void Logger::war(const char *msg, ...)
{
    va_list valist;
    va_start(valist, msg);
    vlog(msg, valist, 2);
}

void Logger::vlog(const char *msg, va_list valist, uint8_t channel)
{
    vlog(msg, valist, channel, "");
}

void Logger::vlog(const char *msg, va_list valist, uint8_t channel, const char *prefix, ...)
{
    va_list internValist;
    va_start(internValist, prefix);
    char *pref = __findPref(channel);
    strncat(pref, prefix, LOGGER_LENGTH - 6);
    vvlog(msg, valist, pref, internValist);
    delete pref;
}

void Logger::vvlog(const char *msg, ...)
{
    va_list valist;
    va_start(valist, msg);
    vsnprintf(prepstr, LOGGER_MAX_LENGTH, msg, valist);
    __savelog(prepstr);
}

void Logger::vvlog(const char *msg, va_list valist, const char *prefix, va_list valist2)
{
    prepstr[0] = 0;
    if (prefix)
        vsnprintf(prepstr, LOGGER_MAX_LENGTH, prefix, valist2);
    size_t l = strlen(prepstr);
    vsnprintf(prepstr + l, LOGGER_MAX_LENGTH - l, msg, valist);
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

char *Logger::__findPref(uint8_t channel)
{
    char *prefix = (char *)malloc(LOGGER_LENGTH);
    switch (channel)
    {
    case 1:
        strcpy(prefix, "ERR: ");
        break;
    case 2:
        strcpy(prefix, "WAR: ");
        break;
    default:
        strcpy(prefix, "");
        break;
    }
    return prefix;
}

uint8_t Logger::getIterator() { return iterator; }

char *Logger::getLastLog(int offSet)
{
    return logs[(uint8_t)(iterator - offSet)];
}