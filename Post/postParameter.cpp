#include "postParameter.h"

PostParameter::PostParameter()
{
    GroupName = "";
    ID=SYS_PARAM_UNKNOWN;//�����ı�ʶ��ID
    Name="";
    Type=UnknownParameter;//��������Ĭ��δ֪
    Value=ParameterValue();//ֵ
    Format=ParameterFormat();//��ʽ
    NeedOutPut=false;//�ò����Ƿ���Ҫ���
    //State = OutPut;
    //++Index;
}
PostParameter::PostParameter(int id)
{
    ID=id;//�����ı�ʶ��ID
}
PostParameter::PostParameter(QString valStr)
{
    //�ı���������ҪID ��ʽ
    GroupName = "";
    Name="";
    Type=Text;//��������
    Value.Type=StrValue;
    Value.s=valStr;
    NeedOutPut=true;//�ò����Ƿ���Ҫ���
    //ID=SYS_PARAM_UNKNOWN;
}
PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterFormat format,int id)
{
    GroupName = groupName;
    ID=id;//�����ı�ʶ��ID
    Name=name;
    Type=type;//��������
    CurValueStr="";
    PreValueStr="";
    ValIsChange = true;
    Format=format;//��ʽ
}
PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
              ParameterFormat format,bool needOutPut,int id )
{
    GroupName = groupName;
    ID=id;//�����ı�ʶ��ID
    Name=name;
    Type=type;//��������
    Value=value;//ֵ
    Format=format;//��ʽ
    //Format.vParameterIDs.push_back(this->ID);//����ǰ������ӵ���ʽ��
    NeedOutPut=needOutPut;//�ò����Ƿ���Ҫ���
    CurValueStr="";
    PreValueStr="";
    ValIsChange = true;
}

void PostParameter::UpdateIntVal(int val)
{
    if(Value.i == val)
        ValIsChange = false;
    else{
        ValIsChange = true;
        Value.i = val;
    }
}
void PostParameter::UpdateDoubleVal(double val)
{
    if(Value.d == val)
        ValIsChange = false;
    else{
        ValIsChange = true;
        Value.d = val;
    }
}
void PostParameter::UpdateStringVal(QString val)
{
    if(Value.s == val)
        ValIsChange = false;
    else{
        ValIsChange = true;
        Value.s = val;
    }
}
void PostParameter::UpdateGroupVal(QString id)
{
    if(Value.curGroupValId == id)
        ValIsChange = false;
    else{
        ValIsChange = true;
        Value.curGroupValId = id;
    }
}
void PostParameter::CopyParameter(PostParameter *parameter)
{
   parent = parameter;
   Value = parent->Value;
}
bool PostParameter::GetOutPutString(QString &str,bool preview)
{
    GetValue();//��ȡ CurValueStr
    if(Type==Text)
    {
        str = CurValueStr;
        return true;
    }
    else
    {
        if(preview)//Ԥ��
        {
           str = Format.Prefix+CurValueStr+Format.Postfix;
           return true;
        }
        else//���NC
        {
            if(!parent->ValIsChange)//ֵû�иı䣬�����
               return false;
            else//ֵ�����˸ı�
            {
                str = Format.Prefix+CurValueStr+Format.Postfix;
                parent->ValIsChange = false;
                return true;
            }
        }
    }
}

//bool PostParameter::GetOutPutString(QString &str,bool preview)
//{
//    if(preview)

//    bool out = false;
//    GetValue();
//    if(!preview)//����Ԥ��
//    {
//        if(!parent->ValIsChange)//ֵû�иı䣬�����
//            return false;
//        else
//            out = true;
//    }
//    else//Ԥ��
//        out = true;

//    if(out)
//    {
//        str = Format.Prefix+CurValueStr+Format.Postfix;
//        parent->ValIsChange = false;
//        return true;
//    }
//    else
//        return false;
//}

int PostParameter::GetIntVal()
{
    if (Type==GeneralParameter)
      return Value.i;

    else if (Type==GroupParameter)
      return Value.groupValList.at(Value.curGroupValId);

    return -1;
}

QString PostParameter::GetStrVal()
{
    if (Type==Text)
      return Value.s;

    else if (Type==GeneralParameter)
      return Value.s;

    else
        return "";
}
double PostParameter::GetDoubleVal()
{
    if (Type==GeneralParameter)
      return Value.d;

    else
        return 0;
}
QString PostParameter::GetValue()
{
    switch (Type)
    {
    case Text:
        CurValueStr = Value.s;
        break;
    case GeneralParameter:
        if(Value.Type==StrValue)
        {
            CurValueStr =  Value.s;
        }
        else if(Value.Type==IntValue)
        {
            CurValueStr =  QString::number(Value.i);
        }
        else if(Value.Type==DoubleValue)
        {
            CurValueStr =  QString::number(Value.d);
        }
        break;
    case GroupParameter://��ֵ
    {
        CurValueStr =  QString::number(Value.groupValList.at(Value.curGroupValId));
    }
        break;
    default:
        CurValueStr =  "";
        break;
    }
    return CurValueStr;
}

