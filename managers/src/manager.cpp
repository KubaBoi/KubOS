#include "manager.h"

Manager::Manager(ManagerMapper *mappern) 
{ 
    mapper = mappern;
    //logger = mapper->getLogger();
    //logger->log(typeid(this).name());
}

void Manager::update() {}
