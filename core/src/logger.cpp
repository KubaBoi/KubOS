#include "logger.h"

Logger::Logger()
{
    for (int i = 0; i < LOGGER_SIZE; i++)
        logs[i][0] = 0;
}

void Logger::log(char *msg)
{
    strncpy(logs[++iterator], msg, LOGGER_LENGTH);
}

uint8_t Logger::getIterator() { return iterator; }

char *Logger::getLastLog(uint8_t offSet)
{
    return logs[(uint8_t)(iterator - offSet)];
}