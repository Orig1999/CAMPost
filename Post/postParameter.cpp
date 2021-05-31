#include "postParameter.h"

PostParameter::PostParameter()
{
    GroupName = "";
    ID=SYSTEM_PARAMETER_ID+Index;//参数的标识符ID
    Name="";
    Type=UnknownParameter;//参数类型默认未知
    Value=ParameterValue();//值
    Format=ParameterFormat();//格式
    NeedOutPut=false;//该参数是否需要输出
    State = OutPut;
    //++Index;
}
int PostParameter::Index = 0;
int ParameterFormat::Index = 0;

//PostParameter::PostParameter(ParameterParentGroup group,QString name,ParameterType type,ParameterValue value,
//              ParameterFormat format,bool needOutPut)
//{
//    Group = group;
//    ID=SYSTEM_PARAMETER_ID+Index;//参数的标识符ID
//    Name=name;
//    Type=type;//参数类型
//    Value=value;//值
//    Format=format;//格式
//    NeedOutPut=needOutPut;//该参数是否需要输出
//    if(type!=Text)
//        ++Index;
//}


PostParameter::PostParameter(QString valStr)
{
    //文本参数不需要ID 格式
    GroupName = "";
    Name="";
    Type=Text;//参数类型
    Value.Type=StrValue;
    Value.s=valStr;
    NeedOutPut=true;//该参数是否需要输出
}

PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
              ParameterFormat format,bool needOutPut )
{
    GroupName = groupName;
    ID=SYSTEM_PARAMETER_ID+Index;//参数的标识符ID
    Name=name;
    Type=type;//参数类型
    Value=value;//值
    Format=format;//格式
    //Format.vParameterIDs.push_back(this->ID);//将当前参数添加到格式中
    NeedOutPut=needOutPut;//该参数是否需要输出
    if(type!=Text)
        ++Index;
}
void PostParameter::IniltStrParameter()//初始化字符串类参数
{
    Value = ParameterValue(StrValue);
    Format = ParameterFormat();
}

void PostParameter::IniltIntParameter()//初始化整数类参数
{

}

void PostParameter::IniltDoubleParameter()//初始化实数类参数
{

}

void PostParameter::IniltGroupParameter()//初始化组值类参数
{

}

QString PostParameter::GetValue()
{
	switch (Type)
	{
	case Text:
		return Format.Prefix+Value.s+Format.Postfix;
		break;
	case GeneralParameter:
		return Format.Prefix+Value.s+Format.Postfix;
		break;
	case GroupParameter://组值
		break;
	default:
		break;
	}
return "";
}
