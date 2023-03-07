#include "config.h"
#include "chainList.h"
#include "syscalls.h"

#ifndef SYS_CALL_H
#define SYS_CALL_H

/**
 * ChainList of system calls
 * system call is request from app to core
 * SYS_CALL_... are stored in `config/syscalls.h`
 * 
 * app      - address of app which call syscall
 * syscall  - code of syscall
 * memory   - there is stored address of address where app expects output/input
 *          - core can easily change output address if need more space
 *            and it will still be in memory address able for reading
 *            for app
 *          - so if syscall is output then value of memory can be 0 (not address)
 */
class SysCall : public ChainList
{
public:
    SysCall(uintptr_t appn, uint8_t syscalln, uintptr_t *memoryn);

    uintptr_t app;
    uint8_t syscall;
    uintptr_t *memory;
};

#endif