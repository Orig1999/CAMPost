#include "postcommand.h"
//postCommand::postCommand(vector<postBlock> vblocks)
//{
//    ID = SYSTEM_ID+Index;
//    Name = name;
//    vBlocks = vblocks;
//    ++Index;
//}
int postCommand::Index = 0;
postCommand::postCommand(QString name,QString groupName)
{
    //默认向链表中添加一个头
    postBlock block;
    blocklist.push_back(block);
    State = ACTIVE;
    ID = SYSTEM_COMMAND_ID+Index;
    Name = name;
    GroupName = groupName;
     ++Index;
}
postCommand::postCommand()
{
//    //默认添加一个block
    postBlock block;
    vBlocks.push_back(block);


//    //默认向链表中添加一个头
//    BloskList.Insert(0,block);

//    State = ACTIVE;
//    ID = SYSTEM_COMMAND_ID+Index;
//    Name = "";
//    GroupName = "";
//     ++Index;
}
vector<QString> postCommand::GetValue()
{
    vector<QString> value ;
    for (size_t i = 0; i < vBlocks.size(); i++)
	{
		value.push_back(vBlocks[i].GetValue());
	}
	return value;
}
