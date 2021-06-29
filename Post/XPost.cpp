#include "XPost.h"
void PostData::SetCommands()
{
    //开始程序命令
    //qDebug()<<"AAAA";
    postCommand progStartCmd("ProgramStart","",SYS_CMD_PROGSTART);
    CommandsMap.insert(map<int,postCommand>::value_type(progStartCmd.ID,progStartCmd));

    //开始路径命令
    postCommand pathStartCmd("PathStart","",SYS_CMD_PATHSTART);
    CommandsMap.insert(map<int,postCommand>::value_type(pathStartCmd.ID,pathStartCmd));

    //刀具长度补偿开启命令
    postCommand CutterCompOnCmd("CutterCompensationOn","ControllerSwitches",SYS_CMD_COMPENON);
    CommandsMap.insert(map<int,postCommand>::value_type(CutterCompOnCmd.ID,CutterCompOnCmd));
    //刀具长度补偿关闭命令
    postCommand CutterCompOffCmd("CutterCompensationOff","ControllerSwitches",SYS_CMD_COMPENOFF);
    CommandsMap.insert(map<int,postCommand>::value_type(CutterCompOffCmd.ID,CutterCompOffCmd));
    //主轴开启命令
    postCommand SpindleOnCmd("SpindleOn","ControllerSwitches",SYS_CMD_SPINDLEON);
    CommandsMap.insert(map<int,postCommand>::value_type(SpindleOnCmd.ID,SpindleOnCmd));
    //主轴关闭命令
    postCommand SpindleOffCmd("SpindleOff","ControllerSwitches",SYS_CMD_SPINDLEOFF);
    CommandsMap.insert(map<int,postCommand>::value_type(SpindleOffCmd.ID,SpindleOffCmd));
    //冷却开启命令
    postCommand CollantOnCmd("CollantOn","ControllerSwitches",SYS_CMD_COLLANTON);
    CommandsMap.insert(map<int,postCommand>::value_type(CollantOnCmd.ID,CollantOnCmd));
    //冷却关闭命令
    postCommand CollantOffCmd("CollantOff","ControllerSwitches",SYS_CMD_COLLANTOFF);
    CommandsMap.insert(map<int,postCommand>::value_type(CollantOffCmd.ID,CollantOffCmd));
    //第一次换刀命令
    postCommand LoadFirstTCmd("LoadFirstTool","Tool",SYS_CMD_LOADFIRSTTOOL);
    CommandsMap.insert(map<int,postCommand>::value_type(LoadFirstTCmd.ID,LoadFirstTCmd));
    //换刀命令
    postCommand LoadTCmd("LoadTool","Tool",SYS_CMD_LOADTOOL);
    CommandsMap.insert(map<int,postCommand>::value_type(LoadTCmd.ID,LoadTCmd));
    //卸载刀具命令
    postCommand UnLoadTCmd("UnLoadTool","Tool",SYS_CMD_UNLOADTOOL);
    CommandsMap.insert(map<int,postCommand>::value_type(UnLoadTCmd.ID,UnLoadTCmd));
    //钻孔开始
    postCommand CycleStartCmd("CycleStart","Cycle",SYS_CMD_CYCLESTART);
    CommandsMap.insert(map<int,postCommand>::value_type(CycleStartCmd.ID,CycleStartCmd));
    //深孔钻
    postCommand DeepCycleCmd("DeepCycleSetUp","Cycle",SYS_CMD_DEEPCYCLE);
    CommandsMap.insert(map<int,postCommand>::value_type(DeepCycleCmd.ID,DeepCycleCmd));
    //钻孔循环
    postCommand MoveInCycleCmd("MoveInCycle","Cycle",SYS_CMD_MOVEINCYCLE);
    CommandsMap.insert(map<int,postCommand>::value_type(MoveInCycleCmd.ID,MoveInCycleCmd));
    //钻孔结束
    postCommand CycleEndCmd("CycleEnd","Cycle",SYS_CMD_CYCLEEND);
    CommandsMap.insert(map<int,postCommand>::value_type(CycleEndCmd.ID,CycleEndCmd));
    //换刀后第一次移动
    postCommand FirstMoveAfterTCmd("FirstMoveAfterToolChange","Move",SYS_CMD_FIRDTMOVEAFTERTOOL);
    CommandsMap.insert(map<int,postCommand>::value_type(FirstMoveAfterTCmd.ID,FirstMoveAfterTCmd));
    //第一次移动
    postCommand FirstMoveCmd("FirstMove","Move",SYS_CMD_FIRSTMOVE);
    CommandsMap.insert(map<int,postCommand>::value_type(FirstMoveCmd.ID,FirstMoveCmd));
    //快速移动
    postCommand RapidMoveCmd("MoveRapid","Move",SYS_CMD_MOVERAPID);
    CommandsMap.insert(map<int,postCommand>::value_type(RapidMoveCmd.ID,RapidMoveCmd));
    //线性移动
    postCommand LinearMoveCmd("MoveLinear","Move",SYS_CMD_MOVELINEAR);
    CommandsMap.insert(map<int,postCommand>::value_type(LinearMoveCmd.ID,LinearMoveCmd));
    //圆弧移动
    postCommand CircleMoveXYCmd("CircleMoveXY","Arc",SYS_CMD_CIRCLEXY);
    CommandsMap.insert(map<int,postCommand>::value_type(CircleMoveXYCmd.ID,CircleMoveXYCmd));
    //螺旋移动
    postCommand HelicMoveXYCmd("HelicMoveXY","Arc",SYS_CMD_HELICXY);
    CommandsMap.insert(map<int,postCommand>::value_type(HelicMoveXYCmd.ID,HelicMoveXYCmd));
    //结束路径命令
    postCommand pathEndCmd("PathEnd","",SYS_CMD_PATHEND);
    CommandsMap.insert(map<int,postCommand>::value_type(pathEndCmd.ID,pathEndCmd));
    //结束程序命令
    postCommand progEndCmd("ProgramEnd","",SYS_CMD_PROGEND);
    CommandsMap.insert(map<int,postCommand>::value_type(progEndCmd.ID,progEndCmd));
}
void PostData::SetProgramParameters()
{
  ParameterValue value = ParameterValue(StrValue);
  ParameterFormat format = ParameterFormat("ProgramNameFormat","","",0,SYS_FORMAT_ProgramName);
  FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
  PostParameter ProgName = PostParameter("ProgramGroup","ProgramName",GeneralParameter,value,format,true,SYS_PARAM_ProgramName);
  ParametersMap.insert(map<int,PostParameter>::value_type(ProgName.ID,ProgName));
}
void PostData::SetPathParameters()
{  
    ParameterValue value = ParameterValue(StrValue);
    ParameterFormat format = ParameterFormat("PathNameFormat","","",0,SYS_FORMAT_PathName);
    FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
    PostParameter PathName = PostParameter("PathGroup","PathName",GeneralParameter,value,format,true,SYS_PARAM_PathName);
    ParametersMap.insert(map<int,PostParameter>::value_type(PathName.ID,PathName));
}
void PostData::SetControlStitchParameters()//M07/8/9,M03/4/5，G00/01/02/03 ,
{
    {
        ParameterFormat format = ParameterFormat("MotionModeFormat","G","",0,SYS_FORMAT_MotionMode);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("rapid",0));
        value.groupValList.insert(map<QString,int>::value_type("linear",1));
        value.groupValList.insert(map<QString,int>::value_type("cw",2));
        value.groupValList.insert(map<QString,int>::value_type("ccw",3));
        PostParameter parameter = PostParameter("ControlSwitchGroup","MotionMode",GroupParameter,value,format,true,SYS_PARAM_MotionMode);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }

    {
        ParameterFormat format = ParameterFormat("CollantFormat","M","",0,SYS_FORMAT_CollantMode);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("mist",7));
        value.groupValList.insert(map<QString,int>::value_type("liquid",8));
        value.groupValList.insert(map<QString,int>::value_type("on",8));
        value.groupValList.insert(map<QString,int>::value_type("off",9));
        PostParameter parameter = PostParameter("ControlSwitchGroup","CollantMode",GroupParameter,value,format,true,SYS_PARAM_CollantMode);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SpindleModeFormat","M","",0,SYS_FORMAT_SpindleMode);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("CW",3));
        value.groupValList.insert(map<QString,int>::value_type("CCW",4));
        value.groupValList.insert(map<QString,int>::value_type("off",5));
        //value.groupValList.insert(map<QString,int>::value_type("off",29));
        PostParameter parameter = PostParameter("ControlSwitchGroup","SpindleMode",GroupParameter,value,format,true,SYS_PARAM_SpindleMode);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }

    {
        ParameterFormat format = ParameterFormat("SpindleSpeedFormat","S","",2,SYS_FORMAT_SpindleSpeed);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("ControlSwitchGroup","SpindleSpeed",GeneralParameter,value,format,true,SYS_PARAM_SpindleSpeed);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("FeedFormat","F","",2,SYS_FORMAT_Feed);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("ControlSwitchGroup","Feed",GeneralParameter,value,format,true,SYS_PARAM_Feed);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("AxisTypeFormat","","",0,SYS_FORMAT_AxisType);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(GroupValue);
        value.groupValList.insert(map<QString,int>::value_type("3axis",axisType_3));
        value.groupValList.insert(map<QString,int>::value_type("multiAxis",axisType_multi));
        PostParameter parameter = PostParameter("ControlSwitchGroup","AxisType",GroupParameter,value,format,true,SYS_PARAM_AxisType);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}
void PostData::SetWorkPlaneParameters()
{ 
    {
        ParameterFormat format = ParameterFormat("ToolAxisIFormat","I","",4,SYS_FORMAT_ToolAxisI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","ToolAxis_I",GeneralParameter,value,format,true,SYS_PARAM_ToolAxis_I);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("ToolAxisJFormat","J","",4,SYS_FORMAT_ToolAxisJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","ToolAxis_J",GeneralParameter,value,format,true,SYS_PARAM_ToolAxis_J);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("ToolAxisKFormat","K","",4,SYS_FORMAT_ToolAxisK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","ToolAxis_K",GeneralParameter,value,format,true,SYS_PARAM_ToolAxis_K);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }

    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginXFormat","X","",4,SYS_FORMAT_WorkPlaneOriginX);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginX",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneOriginX);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginYFormat","Y","",4,SYS_FORMAT_WorkPlaneOriginY);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginY",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneOriginY);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneOriginZFormat","Z","",4,SYS_FORMAT_WorkPlaneOriginZ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneOriginZ",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneOriginZ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorIFormat","I","",4,SYS_FORMAT_WorkPlaneXVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorI",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneXVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorJFormat","J","",4,SYS_FORMAT_WorkPlaneXVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorJ",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneXVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneXVectorIFormat","K","",4,SYS_FORMAT_WorkPlaneXVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneXVectorK",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneXVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorIFormat","I","",4,SYS_FORMAT_WorkPlaneYVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorI",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneYVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorJFormat","J","",4,SYS_FORMAT_WorkPlaneYVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorJ",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneYVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneYVectorIFormat","K","",4,SYS_FORMAT_WorkPlaneYVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneYVectorK",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneYVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorIFormat","I","",4,SYS_FORMAT_WorkPlaneZVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorI",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneZVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorJFormat","J","",4,SYS_FORMAT_WorkPlaneZVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorJ",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneZVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("WorkPlaneZVectorIFormat","K","",4,SYS_FORMAT_WorkPlaneZVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("WorkPlaneGroup","WorkPlaneZVectorK",GeneralParameter,value,format,true,SYS_PARAM_WorkPlaneZVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}


//    const int  = 38;
//    const int  = 39;
//    const int  = 40;
//    const int SYS_PARAM_SystemYVectorI = 41;
//    const int SYS_PARAM_SystemYVectorJ = 42;
//    const int SYS_PARAM_SystemYVectorK = 43;

//    const int SYS_PARAM_SystemZVectorI = 44;
//    const int SYS_PARAM_SystemZVectorJ = 45;
//    const int SYS_PARAM_SystemZVectorK = 46;
void PostData::SetSystemCoordinateParameters()
{
    {
        ParameterFormat format = ParameterFormat("SystemOriginXFormat","X","",4,SYS_FORMAT_SystemOriginX);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemOriginGroup","SystemOriginX",GeneralParameter,value,format,true,SYS_PARAM_SystemOriginX);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemOriginYFormat","Y","",4,SYS_FORMAT_SystemOriginY);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemOriginGroup","SystemOriginY",GeneralParameter,value,format,true,SYS_PARAM_SystemOriginY);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemOriginZFormat","Z","",4,SYS_FORMAT_SystemOriginZ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemOriginGroup","SystemOriginZ",GeneralParameter,value,format,true,SYS_PARAM_SystemOriginZ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemXVectorIFormat","I","",4,SYS_FORMAT_SystemXVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemXVectorI",GeneralParameter,value,format,true,SYS_PARAM_SystemXVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemXVectorJFormat","J","",4,SYS_FORMAT_SystemXVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemXVectorJ",GeneralParameter,value,format,true,SYS_PARAM_SystemXVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemXVectorIFormat","K","",4,SYS_FORMAT_SystemXVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemXVectorK",GeneralParameter,value,format,true,SYS_PARAM_SystemXVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemYVectorIFormat","I","",4,SYS_FORMAT_SystemYVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemYVectorI",GeneralParameter,value,format,true,SYS_PARAM_SystemYVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemYVectorJFormat","J","",4,SYS_FORMAT_SystemYVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemYVectorJ",GeneralParameter,value,format,true,SYS_PARAM_SystemYVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemYVectorIFormat","K","",4,SYS_FORMAT_SystemYVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemYVectorK",GeneralParameter,value,format,true,SYS_PARAM_SystemYVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemZVectorIFormat","I","",4,SYS_FORMAT_SystemZVectorI);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemZVectorI",GeneralParameter,value,format,true,SYS_PARAM_SystemZVectorI);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemZVectorJFormat","J","",4,SYS_FORMAT_SystemZVectorJ);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemZVectorJ",GeneralParameter,value,format,true,SYS_PARAM_SystemZVectorJ);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterFormat format = ParameterFormat("SystemZVectorIFormat","K","",4,SYS_FORMAT_SystemZVectorK);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter parameter = PostParameter("SystemGroup","SystemZVectorK",GeneralParameter,value,format,true,SYS_PARAM_SystemZVectorK);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}
void PostData::SetMoveParameters()//X,Y,X,Z,A,B,C
{   
    {
        ParameterFormat format = ParameterFormat("XFormat","X","",4,SYS_FORMAT_X);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter X = PostParameter("MoveGroup","X",GeneralParameter,value,format,true,SYS_PARAM_X);
        ParametersMap.insert(map<int,PostParameter>::value_type(X.ID,X));
    }
    {
        ParameterFormat format = ParameterFormat("YFormat","Y","",4,SYS_FORMAT_Y);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter Y = PostParameter("MoveGroup","Y",GeneralParameter,value,format,true,SYS_PARAM_Y);
        ParametersMap.insert(map<int,PostParameter>::value_type(Y.ID,Y));
    }
    {
        ParameterFormat format = ParameterFormat("ZFormat","Z","",4,SYS_FORMAT_Z);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter Z = PostParameter("MoveGroup","Z",GeneralParameter,value,format,true,SYS_PARAM_Z);
        ParametersMap.insert(map<int,PostParameter>::value_type(Z.ID,Z));
    }
    {
        ParameterFormat format = ParameterFormat("XFormat","A","",4,SYS_FORMAT_A);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter A = PostParameter("MoveGroup","A",GeneralParameter,value,format,true,SYS_PARAM_A);
        ParametersMap.insert(map<int,PostParameter>::value_type(A.ID,A));
    }
    {
        ParameterFormat format = ParameterFormat("XFormat","B","",4,SYS_FORMAT_B);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter B = PostParameter("MoveGroup","B",GeneralParameter,value,format,true,SYS_PARAM_B);
        ParametersMap.insert(map<int,PostParameter>::value_type(B.ID,B));
    }
    {
        ParameterFormat format = ParameterFormat("CFormat","C","",4,SYS_FORMAT_C);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        ParameterValue value = ParameterValue(DoubleValue);
        PostParameter C = PostParameter("MoveGroup","C",GeneralParameter,value,format,true,SYS_PARAM_C);
        ParametersMap.insert(map<int,PostParameter>::value_type(C.ID,C));
    }
}
void PostData::SetToolParameters()//刀具名称，刀具号，刀具长度补偿号，刀具半径补偿号
{
    {
        ParameterValue value = ParameterValue(StrValue);
        ParameterFormat format = ParameterFormat("ToolNameFormat","(ToolName: ",")",0,SYS_FORMAT_ToolName);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolName",GeneralParameter,value,format,true,SYS_PARAM_ToolName);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
    {
        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolNumFormat","T","",0,SYS_FORMAT_ToolNumber);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolNumber",GeneralParameter,value,format,true,SYS_PARAM_ToolNumber);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));

    }
    {

        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolCompNumFormat","D","",0,SYS_FORMAT_ToolCompNumber);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolCompNumber",GeneralParameter,value,format,true,SYS_PARAM_ToolCompNumber);
        ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));

    }
    {
        ParameterValue value = ParameterValue(IntValue);
        ParameterFormat format = ParameterFormat("ToolAdjustNumFormat","H","",0,SYS_FORMAT_ToolAdjustNumber);
        FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
        PostParameter parameter = PostParameter("ToolGroup","ToolAdjustNumber",GeneralParameter,value,format,true,SYS_PARAM_ToolAdjustNumber);
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
    SetSystemCoordinateParameters();
    SetToolParameters();
    SetDrillParameters();
    //2.系统命令初始化
    SetCommands();
}


XPost::XPost()
{
  postData.IniltData();
}
