#include "postblock.h"
//postBlock::postBlock(vector<postBlockItem> vblockItems)
//{
//    //vBlockItems = vblockItems;
//}
postBlock::postBlock()
{
  //postBlockItem *head = new postBlockItem();
  //BloskItemList.SetHead(*head);
  //bloskItemList.push_back(postBlockItem());
}
size_t postBlock::GetNotEmptySize()
{
    if(bloskItemList.size()==0)
        return 0;
    size_t count = 0;

    for(list<postBlockItem>::iterator i = bloskItemList.begin();i!=bloskItemList.end();++i)
    {
        if(!i->IsEmpty())
            ++ count;
    }
    return count;
}

bool postBlock::IsEmpty()
{
    if(bloskItemList.size()==0)
        return true;
    if(bloskItemList.size()==1 && bloskItemList.begin()->IsEmpty())
        return true;
    return false;
}

bool postBlock::GetValue(map<int,PostParameter> &ParametersMap,QString &str,bool preview)
{
    QString value = "";
    for(list<postBlockItem>::iterator item = bloskItemList.begin();
        item!=bloskItemList.end(); ++item)
    {
        item->Parameter.CopyParameter(&ParametersMap.at(item->Parameter.ID));
        QString content ="";
        if(item->GetValue(content,preview))
            value = value + content;
    }
    if(value=="")
        return false;
    else
        str = value;
    return true;
}
