#include "logger.h"

Logger::Logger()
{
}

void Logger::log(char *msg)
{
    strncpy(logs[++iterator], msg, LOGGER_LENGTH);
}

uint8_t Logger::getIterator() { return iterator; }

char *Logger::getLastLog(uint8_t offSet) { return logs[iterator - offSet]; }