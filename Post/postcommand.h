#ifndef POSTCOMMAND_H
#define POSTCOMMAND_H
#include <vector>
#include "postblock.h"
#include <QString>
#include "LinkList.h"
#include <list>
using namespace std;

const int SYSTEM_COMMAND_ID = 0;//系统命令ID起始号
const int USR_COMMAND_ID = 100;//自定义命令ID起始号
enum CommandState
{
    ACTIVE,
    INACTIVE
};

class postCommand
{
private:
    static int Index;
public:
    int ID;//ID号
    CommandState State;
    QString GroupName ;
    //int GroupID ;
    QString Name;//命令的名称
    vector<postBlock> vBlocks;
    //LinkList<postBlock> BloskList;//block链表
    list<postBlock> blocklist;
    postCommand();
    postCommand(QString name,QString groupName = "");

    vector<QString> GetValue();
    ~postCommand(){

    }
};

#endif // POSTCOMMAND_H
