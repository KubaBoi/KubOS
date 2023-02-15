#include "managerMapper.h"

#ifndef MANAGER_H
#define MANAGER_H

/**
Class for manager inheritance
*/
class Manager {
public:
  ManagerMapper* mapper;
  char* code;
  
  Manager(ManagerMapper* mappern, char* coden);
  char* getCode();
};

#endif