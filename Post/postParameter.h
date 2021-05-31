#ifndef POSTPARAMETER_H
#define POSTPARAMETER_H
#include <QString>
#include <QVariant>
using namespace std;
const int SYSTEM_PARAMETER_ID = 1;//系统参数ID起始号
const int USR_PARAMETER_ID = 100;//自定义参数ID起始号
const int USR_PARAMETER_ID_MAX = 200;//自定义参数ID最大编号
const int SYSTEM_FORMAT_ID = 1;//系统格式ID起始号
const int USR_FORMAT_ID = 100;//自定义格式ID起始号
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
    DoubleValue//实数
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
    ParameterValueType Type;
    QString s;
    int i;
    double d;
    bool IsUpdate;//值是否发生了变化
};
class ParameterFormat
{
private:
    static int Index;
public:
    ~ParameterFormat()
    {

    }

    ParameterFormat()
    {
        Name="";
        ID=SYSTEM_FORMAT_ID+Index;
        Prefix="";
        Postfix="";
        DecimalNum=0;
        ++Index;
    }
    ParameterFormat(QString name,QString prefix,QString postfix,int decimalNum)
    {
        Name = name;
        ID=SYSTEM_FORMAT_ID+Index;
        Prefix=prefix;
        Postfix=postfix;
        DecimalNum=decimalNum;
        ++Index;
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
enum ParameterState
{
    OutPut,
    NotOutPut
};

//参数可能是文本（字符串），组值（M07/M08/M09）,一般参数（进给F2000.5,路径名称）
class PostParameter
{
private:
    static int Index;
public :
    PostParameter();
//    PostParameter(ParameterParentGroup group,QString name,ParameterType type,ParameterValue value,
//                  ParameterFormat format,bool needOutPut = false);
    PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
                  ParameterFormat format,bool needOutPut = false);

    //文本参数构造函数（不需要格式）
    PostParameter(QString valStr);

    void IniltStrParameter();//初始化字符串类参数
    void IniltIntParameter();//初始化整数类参数
    void IniltDoubleParameter();//初始化实数类参数
    void IniltGroupParameter();//初始化组值类参数

	int ID;//参数的标识符ID
    QString Name;
    ParameterParentGroup Group;//所属
    QString GroupName;
	ParameterType Type;//参数类型
	ParameterValue Value;//值
	ParameterFormat Format;//格式
    QString GetValue();//参照Format将Value处理成相应的字符串
	bool NeedOutPut;//该参数是否需要输出
    ParameterState State;
};

Q_DECLARE_METATYPE(PostParameter)
//MyClass myClass;
//QVariant v3 = QVairant::fromValue(myClass);

#endif // POSTPARAMETER_H
