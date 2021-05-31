#ifndef POSTCOMMAND_H
#define POSTCOMMAND_H
#include <vector>
#include "postblock.h"
#include <QString>
#include "LinkList.h"
#include <list>
using namespace std;

const int SYSTEM_COMMAND_ID = 0;//ϵͳ����ID��ʼ��
const int USR_COMMAND_ID = 100;//�Զ�������ID��ʼ��
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
    int ID;//ID��
    CommandState State;
    QString GroupName ;
    //int GroupID ;
    QString Name;//���������
    vector<postBlock> vBlocks;
    //LinkList<postBlock> BloskList;//block����
    list<postBlock> blocklist;
    postCommand();
    postCommand(QString name,QString groupName = "");

    vector<QString> GetValue();
    ~postCommand(){

    }
};

#endif // POSTCOMMAND_H
