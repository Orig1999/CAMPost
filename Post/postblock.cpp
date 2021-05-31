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

QString postBlock::GetValue()
{
    QString value = "";
//    for (size_t i = 0; i < vBlockItems.size(); i++)
//	{
//		value += vBlockItems[i].GetValue();
//	}
    return value;
}
