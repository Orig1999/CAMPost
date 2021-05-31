#ifndef POSTBLOCK_H
#define POSTBLOCK_H
#include "postblockitem.h"
#include <vector>
#include <string>
#include "LinkList.h"
#include <list>
using namespace std;

class postBlock
{
public:
    //vector<postBlockItem> vBlockItems;
    //LinkList<postBlockItem> BloskItemList;//BloskItem链表
    list<postBlockItem> bloskItemList;//BloskItem链表
    QString GetValue();
    postBlock();
    bool IsEmpty();
    size_t GetNotEmptySize();
    //postBlock(vector<postBlockItem> vblockItems);
};

#endif // POSTBLOCK_H
