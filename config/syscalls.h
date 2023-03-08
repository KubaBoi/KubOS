/**
 * Constans for SYS_CALL_H
 */
#define SYS_CALL_COUNT 4
/**
 * Close app
 * <- memory = address of App which should be closed
 * -> return address of App after procedure or nullptr if fail
 */
#define SYS_CALL_CLOSE 1

/**
 * Start app
 * <- memory = address of new instance of an App
 * -> return address of App after procedure or nullptr if fail
 */
#define SYS_CALL_START 2

/**
 * Next app
 * <- memory = if 0 then next if anything else then prev
 * -> return address of App after procedure or nullptr if fail
 */
#define SYS_CALL_NEXT 3

// OUTPUT fill memory pointer with nvm
#define SYS_CALL_APPS 4

/**
 * Rewoke app
 * <- memory = address of App to be rewoken
 * -> return address of App after procedure or nullptr if fail
 */
#define SYS_CALL_REWOKE 5