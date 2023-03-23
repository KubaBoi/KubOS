#include "manager.h"

Manager::Manager(ManagerMapper *mappern, char *namen) 
{ 
    mapper = mappern;
    name = namen;
    logger = mapper->getLogger();
    logger->log("%#x %s_MNG", this, name);
}

void Manager::log(const char *text, ...)
{
    va_list valist;
    va_start(valist, text);
    logger->vlog(text, valist, 0, "%s: ", name);
}

void Manager::err(const char *text, ...)
{
    va_list valist;
    va_start(valist, text);
    logger->vlog(text, valist, 1, "%s: ", name);
}

void Manager::war(const char *text, ...)
{
    va_list valist;
    va_start(valist, text);
    logger->vlog(text, valist, 2, "%s: ", name);
}

void Manager::update() {}
