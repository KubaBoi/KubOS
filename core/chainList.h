
#ifndef CHAIN_LIST_H
#define CHAIN_LIST_H

class ChainList
{
public:
    ChainList();

    ChainList *next, *prev;

    // Add new piece after this and return the new one
    ChainList *addAfter(ChainList *chnp);
    // Remove this and return prev but does not delete this
    ChainList *remove();
};

#endif