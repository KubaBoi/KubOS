#include "fileManager.h"

char FileManager::errComm[12][20] = {
    "Hardware Error",
    "File System Error",
    "Not Executable",
    "Full",
    "Locked",
    "Denied",
    "Busy",
    "Time Out",
    "Not Implemented",
    "Out of Memory",
    "INV param",
    "Unknown"};

FileManager::FileManager(ManagerMapper *mappern) : Manager(mappern, "FIL")
{
    lv_fs_file_t file;

    lv_fs_if_init();
    lv_fs_drv_init(&drv);
    drv.letter = 'P'; // An uppercase letter to identify the drive
    drv.open_cb = open_cb;
    drv.write_cb = write_cb;
    drv.dir_open_cb = dir_open_cb;
    drv.dir_read_cb = dir_read_cb;
    drv.dir_close_cb = dir_close_cb;
    drv.rddir_size = 256;
    drv.user_data = (uintptr_t *)this;
    lv_fs_drv_register(&drv);

    lv_fs_file_t f;
    lv_fs_res_t res;
    res = lv_fs_open(&f, "P:file.txt", LV_FS_MODE_WR);
    if (res != LV_FS_RES_OK)
        __handleFileError();
}

lv_fs_res_t FileManager::open_cb(_lv_fs_drv_t *drv, void *file, const char *path, lv_fs_mode_t mode)
{
    FileManager *self = (FileManager *)drv->user_data;
    LV_UNUSED(drv);

    const char *flags = "";

    if (mode == LV_FS_MODE_WR)
        flags = LV_FS_MODE_WR;
    else if (mode == LV_FS_MODE_RD)
        flags = LV_FS_MODE_RD;
    else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = LV_FS_MODE_WR;

    char complete_path[strlen(path) + 1];
    complete_path[0] = '/';
    complete_path[1] = '\0';
    strcat(complete_path, path);
    self->log("Try to open file: %s\n", complete_path);
    File f = LittleFS.open(complete_path, flags);
    if (!f)
    {
        self->err("Error with file: %s\n", complete_path);
        return LV_FS_RES_DENIED;
    }
    else
    {
        self->log("%s", f.name());
        time_t t = f.getLastWrite();
        struct tm *tmstruct = localtime(&t);
        self->log("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    }
    return LV_FS_RES_OK;
}

lv_fs_res_t FileManager::write_cb(_lv_fs_drv_t *drv, void *file, const char *path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);
    File *fl = (File *)file;
    //*bw = fl->write((uint8_t *)buf, btw);
    return 0;
    //return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

lv_fs_res_t FileManager::dir_open_cb(_lv_fs_drv_t *drv, void *dir, const char *path)
{
    FileManager *self = (FileManager *)drv->user_data;
    self->log("OPEN: %u - '%s'", (uint32_t)path, path);
    return 0;
}

lv_fs_res_t FileManager::dir_read_cb(_lv_fs_drv_t *drv, void *dir, char *path)
{
    FileManager *self = (FileManager *)drv->user_data;
    self->log("READ: '%s'", &path);
    return 0;
}

lv_fs_res_t FileManager::dir_close_cb(_lv_fs_drv_t *drv, void *dir)
{
    FileManager *self = (FileManager *)drv->user_data;
    self->log("CLOSE: %u", (uint32_t)dir);
    return 0;
}

void FileManager::__handleFileError(lv_fs_res_t res, const char *comment)
{
    err("%u: %s - %s", res, errComm[res - 1], comment);
}