#include "manager.h"

Manager::Manager(ManagerMapper *mappern, char *namen) 
{ 
    mapper = mappern;
    name = namen;
    logger = mapper->getLogger();
    log("Initialized");
}

void Manager::log(char *text)
{
    char txt[strlen(name)];
    strcpy(txt, name);
    strcat(txt,  "_MNG: ");
    strcat(txt, text);
    logger->log(txt);
}

void Manager::update() {}
