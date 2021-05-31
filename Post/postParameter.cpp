#include "postParameter.h"

PostParameter::PostParameter()
{
    GroupName = "";
    ID=SYSTEM_PARAMETER_ID+Index;//�����ı�ʶ��ID
    Name="";
    Type=UnknownParameter;//��������Ĭ��δ֪
    Value=ParameterValue();//ֵ
    Format=ParameterFormat();//��ʽ
    NeedOutPut=false;//�ò����Ƿ���Ҫ���
    State = OutPut;
    //++Index;
}
int PostParameter::Index = 0;
int ParameterFormat::Index = 0;

//PostParameter::PostParameter(ParameterParentGroup group,QString name,ParameterType type,ParameterValue value,
//              ParameterFormat format,bool needOutPut)
//{
//    Group = group;
//    ID=SYSTEM_PARAMETER_ID+Index;//�����ı�ʶ��ID
//    Name=name;
//    Type=type;//��������
//    Value=value;//ֵ
//    Format=format;//��ʽ
//    NeedOutPut=needOutPut;//�ò����Ƿ���Ҫ���
//    if(type!=Text)
//        ++Index;
//}


PostParameter::PostParameter(QString valStr)
{
    //�ı���������ҪID ��ʽ
    GroupName = "";
    Name="";
    Type=Text;//��������
    Value.Type=StrValue;
    Value.s=valStr;
    NeedOutPut=true;//�ò����Ƿ���Ҫ���
}

PostParameter::PostParameter(QString groupName,QString name,ParameterType type,ParameterValue value,
              ParameterFormat format,bool needOutPut )
{
    GroupName = groupName;
    ID=SYSTEM_PARAMETER_ID+Index;//�����ı�ʶ��ID
    Name=name;
    Type=type;//��������
    Value=value;//ֵ
    Format=format;//��ʽ
    //Format.vParameterIDs.push_back(this->ID);//����ǰ������ӵ���ʽ��
    NeedOutPut=needOutPut;//�ò����Ƿ���Ҫ���
    if(type!=Text)
        ++Index;
}
void PostParameter::IniltStrParameter()//��ʼ���ַ��������
{
    Value = ParameterValue(StrValue);
    Format = ParameterFormat();
}

void PostParameter::IniltIntParameter()//��ʼ�����������
{

}

void PostParameter::IniltDoubleParameter()//��ʼ��ʵ�������
{

}

void PostParameter::IniltGroupParameter()//��ʼ����ֵ�����
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
	case GroupParameter://��ֵ
		break;
	default:
		break;
	}
return "";
}
