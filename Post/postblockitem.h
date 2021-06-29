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
    bool GetValue(QString &str,bool preview);
    postBlockItem(PostParameter &parameter,ItemState stste = OutPut);
    postBlockItem();
    ~postBlockItem()
    {

    }
    bool IsEmpty();
};

#endif // POSTBLOCKITEM_H
