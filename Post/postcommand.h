#ifndef POSTCOMMAND_H
#define POSTCOMMAND_H
#include <vector>
#include "postblock.h"
#include <QString>
#include "LinkList.h"
#include <list>
using namespace std;

const int SYS_CMD_UNKNOWN = 0;
const int SYS_CMD_PROGSTART = 1;
const int SYS_CMD_PATHSTART = 2;
const int SYS_CMD_LOADFIRSTTOOL = 3;
const int SYS_CMD_LOADTOOL = 4;
const int SYS_CMD_UNLOADTOOL = 5;
const int SYS_CMD_CYCLESTART = 6;
const int SYS_CMD_DEEPCYCLE = 7;
const int SYS_CMD_MOVEINCYCLE = 8;
const int SYS_CMD_CYCLEEND = 9;
const int SYS_CMD_FIRDTMOVEAFTERTOOL = 10;
const int SYS_CMD_FIRSTMOVE = 11;
const int SYS_CMD_MOVERAPID = 12;
const int SYS_CMD_MOVELINEAR = 13;
const int SYS_CMD_CIRCLEXY = 14;
const int SYS_CMD_HELICXY = 15;
const int SYS_CMD_PATHEND = 16;
const int SYS_CMD_PROGEND = 17;

const int SYS_CMD_COMPENON = 18;
const int SYS_CMD_COMPENOFF = 19;
const int SYS_CMD_SPINDLEON = 20;
const int SYS_CMD_SPINDLEOFF = 21;
const int SYS_CMD_COLLANTON = 22;
const int SYS_CMD_COLLANTOFF = 23;

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
    postCommand(bool addEmpty=true);
    postCommand(QString name,QString groupName = "",int id = SYS_CMD_UNKNOWN,CommandState state=ACTIVE,bool addEmpty=true);

    bool GetValue(map<int,PostParameter> &ParametersMap,vector<QString> &str,bool preview);
    ~postCommand(){

    }
};

#endif // POSTCOMMAND_H
