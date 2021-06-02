#include "postblockitem.h"
postBlockItem::postBlockItem(PostParameter &parameter)
{
  Parameter = parameter;
  State = OutPut;
}
postBlockItem::postBlockItem()
{
  State = OutPut;
}
bool postBlockItem::IsEmpty()
{
    //PostParameter aa = Parameter;
    if(Parameter.Type == UnknownParameter)
        return true ;
    return false;
}
QString postBlockItem:: GetValue()
{
    return Parameter.GetValue();
}
