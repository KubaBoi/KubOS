#include "manager.h"

Manager::Manager(ManagerMapper *mappern) 
{ 
    mapper = mappern;
    logger = mapper->getLogger();
}

void Manager::update() {}
