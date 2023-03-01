#include "manager.h"

Manager::Manager(ManagerMapper *mappern, char *namen) 
{ 
    mapper = mappern;
    name = namen;
    logger = mapper->getLogger();
    logger->log("0x%x %s_MNG", this, name);
}

void Manager::log(const char *text, ...)
{
    va_list valist;
    va_start(valist, text);

    char txt[strlen(name)];
    strcpy(txt, name);
    strcat(txt, "_MNG: ");
    strcat(txt, text);
    logger->vlog(txt, valist);
}

void Manager::update() {}
