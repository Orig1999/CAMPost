#include "XPost.h"
//PostData::PostData(PostMachineInfo machineInfo,vector <postCommand> vcommands,
//         vector <PostParameter> vparameters,vector <ParameterFormat> vformats)
//{
//    MachineInfo = machineInfo;
//    vCommands = vcommands;
//    vParameters = vparameters;
//    vFormats = vformats;
//}

void PostData::SetCommands()
{
    //开始程序命令
    //qDebug()<<"AAAA";
    postCommand progStartCmd("ProgramStart");
    CommandsMap.insert(map<int,postCommand>::value_type(progStartCmd.ID,progStartCmd));

    //开始路径命令
    postCommand pathStartCmd("PathStart");
    CommandsMap.insert(map<int,postCommand>::value_type(pathStartCmd.ID,pathStartCmd));

    //刀具长度补偿开启命令
    postCommand CutterCompOnCmd("CutterCompensationOn","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(CutterCompOnCmd.ID,CutterCompOnCmd));
    //刀具长度补偿关闭命令
    postCommand CutterCompOffCmd("CutterCompensationOff","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(CutterCompOffCmd.ID,CutterCompOffCmd));
    //主轴开启命令
    postCommand SpindleOnCmd("SpindleOn","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(SpindleOnCmd.ID,SpindleOnCmd));
    //主轴关闭命令
    postCommand SpindleOffCmd("SpindleOff","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(SpindleOffCmd.ID,SpindleOffCmd));
    //冷却开启命令
    postCommand CollantOnCmd("CollantOn","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(CollantOnCmd.ID,CollantOnCmd));
    //冷却关闭命令
    postCommand CollantOffCmd("CollantOff","ControllerSwitches");
    CommandsMap.insert(map<int,postCommand>::value_type(CollantOffCmd.ID,CollantOffCmd));
    //第一次换刀命令
    postCommand LoadFirstTCmd("LoadFirstTool","Tool");
    CommandsMap.insert(map<int,postCommand>::value_type(LoadFirstTCmd.ID,LoadFirstTCmd));
    //换刀命令
    postCommand LoadTCmd("LoadTool","Tool");
    CommandsMap.insert(map<int,postCommand>::value_type(LoadTCmd.ID,LoadTCmd));
    //卸载刀具命令
    postCommand UnLoadTCmd("UnLoadTool","Tool");
    CommandsMap.insert(map<int,postCommand>::value_type(UnLoadTCmd.ID,UnLoadTCmd));
    //钻孔开始
    postCommand CycleStartCmd("CycleStart","Cycle");
    CommandsMap.insert(map<int,postCommand>::value_type(CycleStartCmd.ID,CycleStartCmd));
    //深孔钻
    postCommand DeepCycleCmd("DeepCycleSetUp","Cycle");
    CommandsMap.insert(map<int,postCommand>::value_type(DeepCycleCmd.ID,DeepCycleCmd));
    //钻孔循环
    postCommand MoveInCycleCmd("MoveInCycle","Cycle");
    CommandsMap.insert(map<int,postCommand>::value_type(MoveInCycleCmd.ID,MoveInCycleCmd));
    //钻孔结束
    postCommand CycleEndCmd("CycleEnd","Cycle");
    CommandsMap.insert(map<int,postCommand>::value_type(CycleEndCmd.ID,CycleEndCmd));
    //换刀后第一次移动
    postCommand FirstMoveAfterTCmd("FirstMoveAfterToolChange","Move");
    CommandsMap.insert(map<int,postCommand>::value_type(FirstMoveAfterTCmd.ID,FirstMoveAfterTCmd));
    //第一次移动
    postCommand FirstMoveCmd("FirstMove","Move");
    CommandsMap.insert(map<int,postCommand>::value_type(FirstMoveCmd.ID,FirstMoveCmd));
    //快速移动
    postCommand RapidMoveCmd("MoveRapid","Move");
    CommandsMap.insert(map<int,postCommand>::value_type(RapidMoveCmd.ID,RapidMoveCmd));
    //线性移动
    postCommand LinearMoveCmd("MoveLinear","Move");
    CommandsMap.insert(map<int,postCommand>::value_type(LinearMoveCmd.ID,LinearMoveCmd));
    //圆弧移动
    postCommand CircleMoveXYCmd("CircleMoveXY","Arc");
    CommandsMap.insert(map<int,postCommand>::value_type(CircleMoveXYCmd.ID,CircleMoveXYCmd));
    //螺旋移动
    postCommand HelicMoveXYCmd("HelicMoveXY","Arc");
    CommandsMap.insert(map<int,postCommand>::value_type(HelicMoveXYCmd.ID,HelicMoveXYCmd));
    //结束路径命令
    postCommand pathEndCmd("PathEnd");
    CommandsMap.insert(map<int,postCommand>::value_type(pathEndCmd.ID,pathEndCmd));
    //结束程序命令
    postCommand progEndCmd("ProgramEnd");
    CommandsMap.insert(map<int,postCommand>::value_type(progEndCmd.ID,progEndCmd));

}
void PostData::SetProgramParameters()
{
  ParameterValue value = ParameterValue(StrValue);
  ParameterFormat format = ParameterFormat("ProgramNameFormat","","",0);
  FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
  PostParameter ProgName = PostParameter("ProgramGroup","ProgramName",GeneralParameter,value,format);
  ParametersMap.insert(map<int,PostParameter>::value_type(ProgName.ID,ProgName));
}
void PostData::SetPathParameters()
{  
    ParameterValue value = ParameterValue(StrValue);
    ParameterFormat format = ParameterFormat("PathNameFormat","","",0);
    FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
    PostParameter PathName = PostParameter("PathGroup","PathName",GeneralParameter,value,format);
    ParametersMap.insert(map<int,PostParameter>::value_type(PathName.ID,PathName));
}
void PostData::SetControlStitchParameters()
{
    ParameterValue value = ParameterValue(StrValue);
    ParameterFormat format = ParameterFormat("CollantFormat","","",0);
    FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
    PostParameter Collant = PostParameter("ControlSwitchGroup","Collant",GroupParameter,value,format);
    ParametersMap.insert(map<int,PostParameter>::value_type(Collant.ID,Collant));
}
void PostData::SetMoveParameters()
{
    ParameterValue value = ParameterValue(DoubleValue);
    ParameterFormat format = ParameterFormat("XFormat","X","",3);
    FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
    PostParameter X = PostParameter("MoveGroup","X",GeneralParameter,value,format);
    ParametersMap.insert(map<int,PostParameter>::value_type(X.ID,X));
}
void PostData::SetToolParameters()
{
  ParameterValue value = ParameterValue(StrValue);
  ParameterFormat format = ParameterFormat("ToolNameFormat","X","",0);
  FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
  PostParameter ToolName = PostParameter("ToolGroup","ToolName",GeneralParameter,value,format);
  ParametersMap.insert(map<int,PostParameter>::value_type(ToolName.ID,ToolName));
}
void PostData::SetDrillParameters()
{

}
void PostData::SetDefaultFormats()
{
//  ParameterFormat DefaultRealformat = ParameterFormat("","",4);
//  FormatsMap.insert(map<int,ParameterFormat>::value_type(DefaultRealformat.ID,DefaultRealformat));
//  ParameterFormat DefaultIntformat = ParameterFormat("","",0);
//  FormatsMap.insert(map<int,ParameterFormat>::value_type(DefaultIntformat.ID,DefaultIntformat));
//  ParameterFormat DefaultStrformat = ParameterFormat("","",0);
//  FormatsMap.insert(map<int,ParameterFormat>::value_type(DefaultStrformat.ID,DefaultStrformat));
}

PostData::PostData()
{

}

void PostData::IniltData()
{
    //1.系统参数初始化
    SetProgramParameters();
    SetPathParameters();
    SetControlStitchParameters();
    SetMoveParameters();
    SetToolParameters();
    SetDrillParameters();

    //2.系统命令初始化
    SetCommands();
}


XPost::XPost()
{
  postData.IniltData();
}
