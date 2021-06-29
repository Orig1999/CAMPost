#include "postcommand.h"
//postCommand::postCommand(vector<postBlock> vblocks)
//{
//    ID = SYSTEM_ID+Index;
//    Name = name;
//    vBlocks = vblocks;
//    ++Index;
//}
int postCommand::Index = 0;
postCommand::postCommand(QString name,QString groupName,int id,CommandState state,bool addEmpty)
{
    //默认向链表中添加一个头
    if(addEmpty)
    {
        postBlock block;
        blocklist.push_back(block);
    }
    State = state;
    ID = id;
    Name = name;
    GroupName = groupName;
}
postCommand::postCommand(bool addEmpty)
{
    //默认添加一个block
    if(addEmpty)
    {
        postBlock block;
        blocklist.push_back(block);
    }
    ID = SYS_CMD_UNKNOWN;
}
bool postCommand::GetValue(map<int,PostParameter> &ParametersMap,vector<QString> &str,bool preview)
{
    for(list<postBlock>::iterator iblock= blocklist.begin();
        iblock!=blocklist.end(); ++iblock)
    {
        QString blkStr="";
        if(iblock->GetValue(ParametersMap,blkStr,preview))
            str.push_back(blkStr);
    }
    if(str.size()==0)
        return false;
    else
        return true;
}




