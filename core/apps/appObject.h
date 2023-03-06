#include "app.h"

#ifndef APP_OBJECT_H
#define APP_OBJECT_H

/**
 * One item of chain list
 */
class AppObject
{
public:
    AppObject(App *appn);

    App *app;
    AppObject *next, *prev;

    // Add new App after this and return new
    AppObject *addAfter(AppObject *appn);
    AppObject *addAfter(App *appn);
    // Remove this and return prev
    AppObject *remove(bool deleteApp = true);
    // Find AppObject in chain
    AppObject *find(App *app);
};

#endif