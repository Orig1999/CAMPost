#ifndef POSTBLOCKITEM_H
#define POSTBLOCKITEM_H
#include "postParameter.h"
#include <vector>
#include <QString>
using namespace std;
enum ItemState
{
    OutPut,
    NotOutPut
};
class postBlockItem
{
public:
    ItemState State;
    PostParameter Parameter;
    QString GetValue();
    postBlockItem(PostParameter &parameter);
    postBlockItem();
    ~postBlockItem()
    {

    }
    bool IsEmpty();
};

#endif // POSTBLOCKITEM_H
