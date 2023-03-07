#include "sysCall.h"

SysCall::SysCall(uintptr_t appn, uint8_t syscalln, uintptr_t *memoryn) : ChainList()
{
    app = appn;
    syscall = syscalln;
    memory = memoryn;
}
