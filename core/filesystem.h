#include "FS.h"
#include "SPIFFS.h"
#include <string.h>

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/**
 * Class controlling files
 * there is only one driver cause no external medium
 * can be connected
 * (may usb could be...?)
 */
class FileSystem
{
public:
    FileSystem();

    char *listAllFiles();

    /**
     * Read file and return as char array in `dest`
     * return -1 - file does not exist
     * return -2 - cannot open file
     * return 0>= - count of readed bytes
    */
    int readFile(const char *path, char *dest);

    // write into the path file and return count of written bytes
    int writeFile(const char *path, const char *content, const char *mode = "w");

    // Remove file and return true if removed
    bool remove(const char *path);

    // Return true if file exists
    bool exists(const char *path);

    // Format disk
    int format();
};

#endif