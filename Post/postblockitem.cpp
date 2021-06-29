#include "postblockitem.h"
postBlockItem::postBlockItem(PostParameter &parameter,ItemState stste )
{
  Parameter = parameter;
  State = stste;
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
bool postBlockItem::GetValue(QString &str,bool preview)
{
    return Parameter.GetOutPutString(str,preview);
}
