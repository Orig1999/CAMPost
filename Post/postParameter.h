#ifndef POSTPARAMETER_H
#define POSTPARAMETER_H
#include <QString>
#include <QVariant>
#include <QDebug>
using namespace std;

const int SYS_PARAM_UNKNOWN = 0;
const int SYS_PARAM_ProgramName = 1;
const int SYS_PARAM_PathName = 2;
const int SYS_PARAM_CollantMode = 3;
const int SYS_PARAM_SpindleMode = 4;
const int SYS_PARAM_WorkPlaneOriginX = 5;
const int SYS_PARAM_WorkPlaneOriginY = 6;
const int SYS_PARAM_WorkPlaneOriginZ = 7;
const int SYS_PARAM_WorkPlaneXVectorI = 8;
const int SYS_PARAM_WorkPlaneXVectorJ = 9;
const int SYS_PARAM_WorkPlaneXVectorK = 10;
const int SYS_PARAM_WorkPlaneYVectorI = 11;
const int SYS_PARAM_WorkPlaneYVectorJ = 12;
const int SYS_PARAM_WorkPlaneYVectorK = 13;
const int SYS_PARAM_WorkPlaneZVectorI = 14;
const int SYS_PARAM_WorkPlaneZVectorJ = 15;
const int SYS_PARAM_WorkPlaneZVectorK = 16;
const int SYS_PARAM_X = 17;
const int SYS_PARAM_Y = 18;
const int SYS_PARAM_Z = 19;
const int SYS_PARAM_A = 20;
const int SYS_PARAM_B = 21;
const int SYS_PARAM_C = 22;
const int SYS_PARAM_ToolName = 23;
const int SYS_PARAM_ToolNumber = 24;
const int SYS_PARAM_ToolCompNumber = 25;
const int SYS_PARAM_ToolAdjustNumber = 26;
const int SYS_PARAM_SpindleSpeed = 27;
const int SYS_PARAM_Feed = 28;
const int SYS_PARAM_MotionMode = 29;
const int SYS_PARAM_AxisType = 30;

const int SYS_PARAM_ToolAxis_I = 31;
const int SYS_PARAM_ToolAxis_J = 32;
const int SYS_PARAM_ToolAxis_K = 33;


const int SYS_PARAM_SystemOriginX = 35;
const int SYS_PARAM_SystemOriginY = 36;
const int SYS_PARAM_SystemOriginZ = 37;
const int SYS_PARAM_SystemXVectorI = 38;
const int SYS_PARAM_SystemXVectorJ = 39;
const int SYS_PARAM_SystemXVectorK = 40;
const int SYS_PARAM_SystemYVectorI = 41;
const int SYS_PARAM_SystemYVectorJ = 42;
const int SYS_PARAM_SystemYVectorK = 43;
const int SYS_PARAM_SystemZVectorI = 44;
const int SYS_PARAM_SystemZVectorJ = 45;
const int SYS_PARAM_SystemZVectorK = 46;


const int USR_PARAMETER_ID = 100;//自定义参数ID起始号



const int USR_PARAMETER_ID_MAX = 200;//自定义参数ID最大编号
const int SYSTEM_FORMAT_ID = 1;//系统格式ID起始号
const int USR_FORMAT_ID = 100;//自定义格式ID起始号

const int SYS_FORMAT_UNKNOWN = 0;
const int SYS_FORMAT_ProgramName = 1;
const int SYS_FORMAT_PathName = 2;
const int SYS_FORMAT_CollantMode = 3;
const int SYS_FORMAT_SpindleMode = 4;
const int SYS_FORMAT_WorkPlaneOriginX = 5;
const int SYS_FORMAT_WorkPlaneOriginY = 6;
const int SYS_FORMAT_WorkPlaneOriginZ = 7;
const int SYS_FORMAT_WorkPlaneXVectorI = 8;
const int SYS_FORMAT_WorkPlaneXVectorJ = 9;
const int SYS_FORMAT_WorkPlaneXVectorK = 10;
const int SYS_FORMAT_WorkPlaneYVectorI = 11;
const int SYS_FORMAT_WorkPlaneYVectorJ = 12;
const int SYS_FORMAT_WorkPlaneYVectorK = 13;
const int SYS_FORMAT_WorkPlaneZVectorI = 14;
const int SYS_FORMAT_WorkPlaneZVectorJ = 15;
const int SYS_FORMAT_WorkPlaneZVectorK = 16;
const int SYS_FORMAT_X = 17;
const int SYS_FORMAT_Y = 18;
const int SYS_FORMAT_Z = 19;
const int SYS_FORMAT_A = 20;
const int SYS_FORMAT_B = 21;
const int SYS_FORMAT_C = 22;
const int SYS_FORMAT_ToolName = 23;
const int SYS_FORMAT_ToolNumber = 24;
const int SYS_FORMAT_ToolCompNumber = 25;
const int SYS_FORMAT_ToolAdjustNumber = 26;
const int SYS_FORMAT_SpindleSpeed = 27;
const int SYS_FORMAT_Feed = 28;
const int SYS_FORMAT_MotionMode = 29;
const int SYS_FORMAT_AxisType = 30;

const int SYS_FORMAT_ToolAxisI=31;
const int SYS_FORMAT_ToolAxisJ=32;
const int SYS_FORMAT_ToolAxisK=33;

const int SYS_FORMAT_SystemOriginX=34;
const int SYS_FORMAT_SystemOriginY=35;
const int SYS_FORMAT_SystemOriginZ=36;

const int SYS_FORMAT_SystemXVectorI=37;
const int SYS_FORMAT_SystemXVectorJ=38;
const int SYS_FORMAT_SystemXVectorK=39;

const int SYS_FORMAT_SystemYVectorI=40;
const int SYS_FORMAT_SystemYVectorJ=41;
const int SYS_FORMAT_SystemYVectorK=42;

const int SYS_FORMAT_SystemZVectorI=43;
const int SYS_FORMAT_SystemZVectorJ=44;
const int SYS_FORMAT_SystemZVectorK=45;


const int USR_FORMATETER_ID = 100;//自定义
enum AxisType
{
  axisType_3,//三轴
  axisType_multi//多轴联动
};
class PostParameter;
enum ParameterParentGroup
{
    ProgramGroup,
    PathGroup,
    ToolGroup,
    MoveGroup,
    ControlSwitchGroup
};
enum ParameterValueType
{
    StrValue,//字符串
    IntValue,//整数
    DoubleValue,//实数
    GroupValue//组
};

class ParameterValue
{
public :

    ParameterValue()
    {
      Type = StrValue;
      s="";
      i=0;
      d=0.0;
      IsUpdate = false;
    }
    ParameterValue(ParameterValueType T,QString S,int I,double D,bool update = false)
    {
      Type = T;
      s=S;
      i=I;
      d=D;
      IsUpdate = update;
    }
    ParameterValue(ParameterValueType T)
    {
      Type = T;
      s="";
      i=0;
      d=0.0;
      IsUpdate = false;
    }

    void SetGroupValue(QString id,int val)
    {
      groupValList.insert(map<QString,int>::value_type(id,val));
    }

    ParameterValueType Type;
    QString s;
    int i;
    double d;
    map<QString,int>groupValList;
    QString curGroupValId;
    bool IsUpdate;//值是否发生了变化
};
class ParameterFormat
{
private:

public:
    ~ParameterFormat()
    {

    }

    ParameterFormat()
    {
        Name="";
        ID= SYS_FORMAT_UNKNOWN;
        Prefix="";
        Postfix="";
        DecimalNum=0;

    }
    ParameterFormat(QString name,QString prefix,QString postfix,int decimalNum,int id= SYS_FORMAT_UNKNOWN)
    {
        Name = name;
        ID= id;
        Prefix=prefix;
        Postfix=postfix;
        DecimalNum=decimalNum;
    }  
	int ID;
    QString Prefix;
    QString Postfix;
	int DecimalNum;
    QString Name;
    //vector<int> vParameterIDs;
};
enum ParameterType
{
    UnknownParameter,
	Text,//文本
	GeneralParameter,//一般参数
	GroupParameter//组值参数
};

//参数可能是文本（字符串），组值（M07/M08/M09）,一般参数（进给F2000.5,路径名称）
class PostParameter
{
private:
    bool ValIsChange;
    QString PreValueStr;//前一个值
    QString CurValueStr;//前一个值
    PostParameter *parent;//父参数
public :
    PostParameter();
//    PostParameter(ParameterParentGroup group,QString name,ParameterType type,ParameterValue value,
//                  ParameterFormat format,bool needOutPut = false);
    PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
                  ParameterFormat format,bool needOutPut = false,int id = SYS_PARAM_UNKNOWN);

    PostParameter(QString groupName,QString name,ParameterType type,ParameterFormat format,int id = SYS_PARAM_UNKNOWN);

    PostParameter(int id);
    //文本参数构造函数（不需要格式）
    PostParameter(QString valStr);



	int ID;//参数的标识符ID
    QString Name;
    ParameterParentGroup Group;//所属
    QString GroupName;
	ParameterType Type;//参数类型
	ParameterValue Value;//值
	ParameterFormat Format;//格式
    QString GetValue();//参照Format将Value处理成相应的字符串

    int GetIntVal();
    QString GetStrVal();
    double GetDoubleVal();

    bool GetOutPutString(QString &str,bool preview);//输出
    void CopyParameter(PostParameter *parameter);
	bool NeedOutPut;//该参数是否需要输出
    void UpdateIntVal(int val);
    void UpdateDoubleVal(double val);
    void UpdateStringVal(QString val);
    void UpdateGroupVal(QString id);
    //ParameterState State;
};

Q_DECLARE_METATYPE(PostParameter)
//MyClass myClass;
//QVariant v3 = QVairant::fromValue(myClass);

#endif // POSTPARAMETER_H
