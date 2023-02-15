#include "manager.h"

Manager::Manager(ManagerMapper* mappern, char* coden) {
  mapper = mappern;
  code = coden;
}

char* Manager::getCode() { return code; }