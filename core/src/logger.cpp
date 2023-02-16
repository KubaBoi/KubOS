#include "logger.h"

Logger::Logger()
{
}

void Logger::log(char *msg)
{
    strncpy(addresses[++iterator], msg, LOGGER_LENGTH);
}

char *Logger::getLastLog()
{
    return addresses[iterator];
}