
#include "managers.h"
#include "manager.h"
#include "irqManager.h"
#include "timeManager.h"

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

/**
 * Class controlling files
 * there is only one driver cause no external medium
 * can be connected
 * (may usb could be...?)
 */
class FileManager : public Manager
{
public:
    FileManager(ManagerMapper *mappern);

    static lv_fs_res_t open_cb(_lv_fs_drv_t *drv, void *file, const char *path, lv_fs_mode_t mode);
    static lv_fs_res_t write_cb(_lv_fs_drv_t *drv, void *file, const char *path, lv_fs_mode_t mode);

    static lv_fs_res_t dir_open_cb(_lv_fs_drv_t *drv, void *dir, const char *path);
    static lv_fs_res_t dir_read_cb(_lv_fs_drv_t *drv, void *dir, char *path);
    static lv_fs_res_t dir_close_cb(_lv_fs_drv_t *drv, void *dir);

private:
    lv_fs_drv_t drv;
    static char errComm[12][20];

    void __handleFileError(lv_fs_res_t res, const char *comment);
};

#endif