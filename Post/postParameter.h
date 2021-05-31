#ifndef POSTPARAMETER_H
#define POSTPARAMETER_H
#include <QString>
#include <QVariant>
using namespace std;
const int SYSTEM_PARAMETER_ID = 1;//ϵͳ����ID��ʼ��
const int USR_PARAMETER_ID = 100;//�Զ������ID��ʼ��
const int USR_PARAMETER_ID_MAX = 200;//�Զ������ID�����
const int SYSTEM_FORMAT_ID = 1;//ϵͳ��ʽID��ʼ��
const int USR_FORMAT_ID = 100;//�Զ����ʽID��ʼ��
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
    StrValue,//�ַ���
    IntValue,//����
    DoubleValue//ʵ��
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
    bool IsUpdate;//ֵ�Ƿ����˱仯
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
	Text,//�ı�
	GeneralParameter,//һ�����
	GroupParameter//��ֵ����
};
enum ParameterState
{
    OutPut,
    NotOutPut
};

//�����������ı����ַ���������ֵ��M07/M08/M09��,һ�����������F2000.5,·�����ƣ�
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

    //�ı��������캯��������Ҫ��ʽ��
    PostParameter(QString valStr);

    void IniltStrParameter();//��ʼ���ַ��������
    void IniltIntParameter();//��ʼ�����������
    void IniltDoubleParameter();//��ʼ��ʵ�������
    void IniltGroupParameter();//��ʼ����ֵ�����

	int ID;//�����ı�ʶ��ID
    QString Name;
    ParameterParentGroup Group;//����
    QString GroupName;
	ParameterType Type;//��������
	ParameterValue Value;//ֵ
	ParameterFormat Format;//��ʽ
    QString GetValue();//����Format��Value�������Ӧ���ַ���
	bool NeedOutPut;//�ò����Ƿ���Ҫ���
    ParameterState State;
};

Q_DECLARE_METATYPE(PostParameter)
//MyClass myClass;
//QVariant v3 = QVairant::fromValue(myClass);

#endif // POSTPARAMETER_H
