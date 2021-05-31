#ifndef POSTBLOCKITEM_H
#define POSTBLOCKITEM_H
#include "postParameter.h"
#include <vector>
#include <QString>
using namespace std;

class postBlockItem
{
public:
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
