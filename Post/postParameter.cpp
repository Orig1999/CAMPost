#include "postParameter.h"

PostParameter::PostParameter()
{
    GroupName = "";
    ID=SYS_PARAM_UNKNOWN;//参数的标识符ID
    Name="";
    Type=UnknownParameter;//参数类型默认未知
    Value=ParameterValue();//值
    Format=ParameterFormat();//格式
    NeedOutPut=false;//该参数是否需要输出
    //State = OutPut;
    //++Index;
}
PostParameter::PostParameter(int id)
{
    ID=id;//参数的标识符ID
}
PostParameter::PostParameter(QString valStr)
{
    //文本参数不需要ID 格式
    GroupName = "";
    Name="";
    Type=Text;//参数类型
    Value.Type=StrValue;
    Value.s=valStr;
    NeedOutPut=true;//该参数是否需要输出
    //ID=SYS_PARAM_UNKNOWN;
}
PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterFormat format,int id)
{
    GroupName = groupName;
    ID=id;//参数的标识符ID
    Name=name;
    Type=type;//参数类型
    CurValueStr="";
    PreValueStr="";
    ValIsChange = true;
    Format=format;//格式
}
PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
              ParameterFormat format,bool needOutPut,int id )
{
    GroupName = groupName;
    ID=id;//参数的标识符ID
    Name=name;
    Type=type;//参数类型
    Value=value;//值
    Format=format;//格式
    //Format.vParameterIDs.push_back(this->ID);//将当前参数添加到格式中
    NeedOutPut=needOutPut;//该参数是否需要输出
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
    GetValue();//获取 CurValueStr
    if(Type==Text)
    {
        str = CurValueStr;
        return true;
    }
    else
    {
        if(preview)//预览
        {
           str = Format.Prefix+CurValueStr+Format.Postfix;
           return true;
        }
        else//输出NC
        {
            if(!parent->ValIsChange)//值没有改变，不输出
               return false;
            else//值发生了改变
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
//    if(!preview)//不是预览
//    {
//        if(!parent->ValIsChange)//值没有改变，不输出
//            return false;
//        else
//            out = true;
//    }
//    else//预览
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
    case GroupParameter://组值
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

