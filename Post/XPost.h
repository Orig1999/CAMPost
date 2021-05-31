#ifndef XPOST_H
#define XPOST_H
#include "postcommand.h"
#include "PostMachine.h"
#include <QDebug>
#include <string>
#include <vector>
#include <map>

using namespace std;
class PostData
{
public :
    PostData();
    void IniltData();
//    PostData(PostMachineInfo MachineInfo,vector <postCommand> vCommand,
//             vector <PostParameter> vParameters,vector <ParameterFormat> vFormats);
    void SetCommands();

    void SetProgramParameters();
    void SetPathParameters();
    void SetControlStitchParameters();
    void SetMoveParameters();
    void SetToolParameters();
    void SetDrillParameters();
    void SetDefaultFormats();
	PostMachineInfo MachineInfo;
    vector<postCommand> vCommands;//命令
    map<int,postCommand> CommandsMap;//命令
    map<int,PostParameter> ParametersMap;//参数
    map<int,ParameterFormat> FormatsMap;//格式
};

class XPost
{
public :
    XPost();
    QString FileName;
    QString FilePath;
    PostData postData;
};

#endif // XPOST_H
