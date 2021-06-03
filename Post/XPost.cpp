#include "XPost.h"
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
void PostData::SetControlStitchParameters()//M07/8/9,M03/4/5
{
    {
        ParameterFormat format = ParameterFormat("CollantFormat","M","",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("mist",7));
        value.groupValList.insert(map<QString,int>::value_type("liquid",8));
        value.groupValList.insert(map<QString,int>::value_type("on",8));
        value.groupValList.insert(map<QString,int>::value_type("off",9));
        PostParameter parameter = PostParameter("ControlSwitchGroup","CollantMode",GroupParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SpindleModeFormat","M","",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("CW",3));
        value.groupValList.insert(map<QString,int>::value_type("CCW",4));
        value.groupValList.insert(map<QString,int>::value_type("off",5));
        //value.groupValList.insert(map<QString,int>::value_type("off",29));
        PostParameter parameter = PostParameter("ControlSwitchGroup","SpindleMode",GroupParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}
void PostData::SetWorkPlaneParameters()
{
    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginXFormat","X","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginX",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginYFormat","Y","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginY",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginZFormat","Z","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginZ",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorIFormat","I","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorI",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorJFormat","J","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorJ",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorIFormat","K","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorK",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorIFormat","I","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorI",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorJFormat","J","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorJ",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorIFormat","K","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorK",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorIFormat","I","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorI",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorJFormat","J","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorJ",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorIFormat","K","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorK",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}
void PostData::SetMoveParameters()//X,Y,X,Z,A,B,C
{   
    {
        ParameterFormat format = ParameterFormat("XFormat","X","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter X = PostParameter("MoveGroup","X",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(X.ID,X));
    }
    {
        ParameterFormat format = ParameterFormat("YFormat","Y","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter Y = PostParameter("MoveGroup","Y",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(Y.ID,Y));
    }
    {
        ParameterFormat format = ParameterFormat("ZFormat","Z","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter Z = PostParameter("MoveGroup","Z",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(Z.ID,Z));
    }
    {
        ParameterFormat format = ParameterFormat("XFormat","A","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter A = PostParameter("MoveGroup","A",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(A.ID,A));
    }
    {
        ParameterFormat format = ParameterFormat("XFormat","B","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter B = PostParameter("MoveGroup","B",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(B.ID,B));
    }
    {
        ParameterFormat format = ParameterFormat("CFormat","C","",4);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter C = PostParameter("MoveGroup","C",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(C.ID,C));
    }
}
void PostData::SetToolParameters()//刀具名称，刀具号，刀具长度补偿号，刀具半径补偿号
{
    {
        ParameterValue value = ParameterValue(StrValue);
        ParameterFormat format = ParameterFormat("ToolNameFormat","(ToolName: ",")",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolName",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolNumFormat","T","",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolNumber",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolCompNumFormat","D","",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolCompNumber",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolAdjustNumFormat","H","",0);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolAdjustNumber",GeneralParameter,value,format);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
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
    SetWorkPlaneParameters();
    SetToolParameters();
    SetDrillParameters();
    //2.系统命令初始化
    SetCommands();
}


XPost::XPost()
{
  postData.IniltData();
}
