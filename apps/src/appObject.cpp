#include "appObject.h"

AppObject::AppObject(App *appn)
{
    app = appn;
    next = this;
    prev = this;
}

AppObject *AppObject::addAfter(AppObject *appn)
{
    appn->next = this->next;
    appn->prev = this;
    this->next->prev = appn;
    this->next = appn;
    return appn;
}

AppObject *AppObject::addAfter(App *appn)
{
    AppObject *newApp = new AppObject(appn);
    return addAfter(newApp);
}

AppObject *AppObject::remove(bool deleteApp)
{
    AppObject *ret = nullptr;
    if (deleteApp && this->app)
        delete (this->app);

    if (this != this->prev)
    {
        this->next->prev = this->prev;
        this->prev->next = this->next;
        ret = this->prev;
    }
    delete (this);
    return ret;
}

AppObject *AppObject::find(App *app)
{
    AppObject *search = this;
    do
    {
        if (search->app == app)
            return search;
        search = search->next;
    } while (search != this);
    return nullptr;
}