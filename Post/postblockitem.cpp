#include "postblockitem.h"
postBlockItem::postBlockItem(PostParameter &parameter)
{
  Parameter = parameter;
}
postBlockItem::postBlockItem()
{

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
