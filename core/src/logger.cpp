#include "logger.h"

Logger::Logger()
{
    for (int i = 0; i < LOGGER_SIZE; i++)
        logs[i][0] = 0;

    for (int i = 0; i < LOGGER_LENGTH; i++)
        clear[i] = ' ';
    clear[LOGGER_LENGTH - 1] = 0;
}

void Logger::log(char *msg)
{
    strncpy(logs[iterator++], msg, LOGGER_LENGTH - 2);
}

uint8_t Logger::getIterator() { return iterator; }

char *Logger::getLastLog(int offSet)
{
    return logs[(uint8_t)(iterator - offSet)];
}