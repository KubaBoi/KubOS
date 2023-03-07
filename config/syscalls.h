/**
 * Constans for SYS_CALL_H
 */
#define SYS_CALL_COUNT 4
// INPUT close app from memory pointer
#define SYS_CALL_CLOSE 0x0001 
// INPUT start new app from memory pointer
#define SYS_CALL_START 0x0002 
// move running app to next
#define SYS_CALL_NEXT 0x0003
// OUTPUT fill memory pointer with nvm
#define SYS_CALL_APPS 0x0004 