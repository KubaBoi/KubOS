#include "appObject.h"

AppObject::AppObject(App *appn) : ChainList()
{
    app = appn;
}

AppObject *AppObject::addAfter(App *appn)
{
    AppObject *newApp = new AppObject(appn);
    return (AppObject *)ChainList::addAfter(newApp);
}

AppObject *AppObject::remove(bool deleteApp)
{
    AppObject *ret = nullptr;
    if (deleteApp && this->app)
    {
        if (this->app->screen);
            lv_obj_del(this->app->screen);
        delete (this->app);
    }
    return (AppObject *)ChainList::remove();
}

AppObject *AppObject::find(App *app)
{
    AppObject *search = this;
    do
    {
        if (search->app == app)
            return search;
        search = (AppObject *)search->next;
    } while (search != this);
    return nullptr;
}