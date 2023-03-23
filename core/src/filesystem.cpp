#include "filesystem.h"

FileSystem::FileSystem()
{
    // need to be save
    SPIFFS.begin(true);
}

char *FileSystem::listAllFiles()
{
    char *files = (char *)malloc(100);
    files[0] = 0;
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file)
    {
        strcat(files, file.name());
        file = root.openNextFile();
    }
    root.close();
    return files;
}

int FileSystem::readFile(const char *path, char *dest)
{
    if (!exists(path))
        return -1;

    File file = SPIFFS.open(path, "r");
    if (!file)
        return -2;

    String s = file.readStringUntil(0);
    const int length = s.length();
    strcpy(dest, s.c_str());
    file.close();
    return strlen(dest);
}

int FileSystem::writeFile(const char *path, const char *content, const char *mode)
{
    File file = SPIFFS.open(path, mode);
    if (!file)
        return 0;
    int bytesWritten = file.print(content);
    file.close();
    return bytesWritten;
}

bool FileSystem::remove(const char *path) { return SPIFFS.remove(path); }
bool FileSystem::exists(const char *path) { return SPIFFS.exists(path); }
int FileSystem::format() { return SPIFFS.format(); }