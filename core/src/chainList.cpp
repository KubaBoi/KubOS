#include "chainList.h"

ChainList::ChainList()
{
    next = this;
    prev = this;
}

ChainList *ChainList::addAfter(ChainList *chnp)
{
    chnp->next = this->next;
    chnp->prev = this;
    this->next->prev = chnp;
    this->next = chnp;
    return chnp;
}

ChainList *ChainList::remove()
{
    ChainList *ret = nullptr;
    if (this != this->prev)
    {
        this->next->prev = this->prev;
        this->prev->next = this->next;
        ret = this->prev;
    }
    return ret;
}