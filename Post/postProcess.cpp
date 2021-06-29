#include "postProcess.h"
#include "postMath.h"

void cutterLocPosition::SetToolPosition(double x,double y,double z)
{
    ToolPosition.X=x;
    ToolPosition.Y=y;
    ToolPosition.Z=z;
}
void cutterLocPosition::SetToolAxisVector(double i,double j,double k)
{
    ToolAxis.I=i;
    ToolAxis.J=j;
    ToolAxis.K=k;
}
void cutterLocPosition::CalculateAC(double I,double J,double K)
{
    mathVector v1(3);
    v1[0]= ToolAxis.I;
    v1[1]= ToolAxis.J;
    v1[2]= ToolAxis.K;

    mathVector v2(3);
    v2[0]= I;
    v2[1]= J;
    v2[2]= K;

    //刀轴和G54Z轴平行
    if( v1.isSyntropy(v2))
    {
        A=0;
        C=0;
    }
    else
    {
        //计算A角
        if(ToolAxis.K==0)
            A = 90*math_pi/180;
        else if(ToolAxis.K>0)
            A = atan(sqrt(pow(ToolAxis.I,2)+pow(ToolAxis.J,2))/
                    ToolAxis.K);
        else
            A = 90*math_pi/180 - atan(sqrt(pow(ToolAxis.I,2)+pow(ToolAxis.J,2))/
                    ToolAxis.K);

        //计算C角
        if(ToolAxis.I>0)
        {
            C = 90*math_pi/180+atan(ToolAxis.J/ToolAxis.I);
        }
        if(ToolAxis.I<0)
        {
            C = 270*math_pi/180+atan(ToolAxis.J/ToolAxis.I);
        }
        else if(abs(ToolAxis.I)<0.00001)
        {
            if(ToolAxis.J>0)
                C = math_pi;
            else
                C = 0;
        }
    }
}



//设置圆弧数据
void cutterLocPosition::SetCircleCenter(double x,double y,double z)
{
    CircleData.Center.X=x;
    CircleData.Center.Y=y;
    CircleData.Center.Z=z;
}
void cutterLocPosition::SetCircleStartVector(double i,double j,double k)
{
    CircleData.StartVector.I=i;
    CircleData.StartVector.J=j;
    CircleData.StartVector.K=k;
}
postProcess::postProcess(QString path,XPost post)
{
    clsfFullPath=path;
    xpost = post;
}

bool postProcess::linkString(QString &str,vector<QString> &tmp)
{
    if(str.length()>1)
    {
        if(str.at(str.length()-1)=='$')//表示和下一行是同一行
        {
            str = str.mid(0,str.length()-1);//删掉末尾的 $
            tmp.push_back(str);
            return false;
        }
        else
        {
            QString line = "";
            for(size_t i = 0;i<tmp.size();++i)
            {
                line = line+tmp[i];
            }
            line = line+str;
            str = line;
            tmp.clear();
        }
    }
  return true;
}
void postProcess::writeCommandToNC(int cmdID,QTextStream &stream)
{
    postCommand cmd = xpost.postData.CommandsMap.at(cmdID);
    vector<QString> str;
    if(cmd.GetValue(xpost.postData.ParametersMap,str,false))
    {
       for(size_t i=0;i<str.size();++i)
       {
            stream << str[i];
            stream << endl; //换行
       }
    }
}
void postProcess::UpdateSystemParameters(QString str)
{
    QStringList  strs=  str.split(",");
    size_t pos = strs[0].indexOf("/");

    QString ostr[] = {strs[0].mid(pos+1,strs[0].length()-pos-1),strs[1],strs[2]};
    QString xstr[] = {strs[3],strs[4],strs[5]};
    QString ystr[] = {strs[6],strs[7],strs[8]};
    QString zstr[] = {strs[9],strs[10],strs[11]};

    xpost.postData.ParametersMap.at(SYS_PARAM_SystemOriginX).UpdateDoubleVal(ostr[0].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemOriginY).UpdateDoubleVal(ostr[1].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemOriginZ).UpdateDoubleVal(ostr[2].toDouble());

    xpost.postData.ParametersMap.at(SYS_PARAM_SystemXVectorI).UpdateDoubleVal(xstr[0].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemXVectorJ).UpdateDoubleVal(xstr[1].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemXVectorK).UpdateDoubleVal(xstr[2].toDouble());

    xpost.postData.ParametersMap.at(SYS_PARAM_SystemYVectorI).UpdateDoubleVal(ystr[0].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemYVectorJ).UpdateDoubleVal(ystr[1].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemYVectorK).UpdateDoubleVal(ystr[2].toDouble());

    xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorI).UpdateDoubleVal(zstr[0].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorJ).UpdateDoubleVal(zstr[1].toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorK).UpdateDoubleVal(zstr[2].toDouble());
}

void postProcess::UpdateToolSpindleParameters(QString str)//刀具号，长度补偿号 转速
{
    QStringList  strs=  str.split(",");
    //1.刀具号
    size_t pos = strs[0].indexOf("/");
    QString toolNumber = strs[0].mid(pos+1,strs[0].length()-pos-1);
    //2.长度补偿号
    QString lengthAdjustNumber = strs[2];
    //3.转速
    QString spindle = strs[4];

    xpost.postData.ParametersMap.at(SYS_PARAM_ToolNumber).UpdateIntVal(toolNumber.toInt());
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolAdjustNumber).UpdateIntVal(lengthAdjustNumber.toInt());
    xpost.postData.ParametersMap.at(SYS_PARAM_SpindleSpeed).UpdateDoubleVal(spindle.toDouble());
};
void postProcess::UpdateToolCompAdjustParameters(QString str)//半径补偿号，长度补偿号
{
    // TLCOMP/1,ADJUST,1
    QStringList  strs=  str.split(",");
    //半径补偿
    size_t pos = strs[0].indexOf("/");
    QString CompNumber = strs[0].mid(pos+1,strs[0].length()-pos-1);
    //长度补偿号
    QString lengthAdjustNumber = strs[2];
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolCompNumber).UpdateIntVal(CompNumber.toInt());
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolAdjustNumber).UpdateIntVal(lengthAdjustNumber.toInt());
};

void postProcess::UpdateFeedrateParameters(QString str)
{
    //  【FEDRAT/  300.0000,MMPM】
    QStringList  strs=  str.split(",");
    //F
    size_t pos = strs[0].indexOf("/");
    QString F = strs[0].mid(pos+1,strs[0].length()-pos-1);
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolCompNumber).UpdateDoubleVal(F.toDouble());
    //G01
    xpost.postData.ParametersMap.at(SYS_PARAM_MotionMode).UpdateGroupVal("linear");
};
void postProcess::UpdateSpindleParameters(QString str)
{
    //  【SPINDL/   70.0000,RPM,CLW】
    QStringList  strs=  str.split(",");
    //S
    size_t pos = strs[0].indexOf("/");
    QString s = strs[0].mid(pos+1,strs[0].length()-pos-1);
    xpost.postData.ParametersMap.at(SYS_PARAM_SpindleSpeed).UpdateDoubleVal(s.toDouble());
    //M03
    xpost.postData.ParametersMap.at(SYS_PARAM_SpindleMode).UpdateGroupVal("cw");
};

void postProcess::UpdateAxisTypeParameters(QString str)
{
  QString idstr = "3axis";
  if(str=="3AXIS")
  {
      idstr = "3axis";
  }
  else
  {
      idstr = "multiAxis";
  }
  xpost.postData.ParametersMap.at(SYS_PARAM_AxisType).UpdateGroupVal(idstr);
}

void postProcess::UpdateMovelinearRapidParameters(QString str)
{
    //  GOTO/90.62016,10.00000,130.00000,0.000000,1.000000,0.000000
    QStringList  strs=  str.split(",");
    size_t pos = strs[0].indexOf("/");
    QString X = strs[0].mid(pos+1,strs[0].length()-pos-1);
    QString Y = strs[1];
    QString Z = strs[2];
    //刀轴
    QString I = strs[3];
    QString J = strs[4];
    QString K = strs[5];

    cutterLocPosition Pnt;
    Pnt.SetToolPosition(X.toDouble(),Y.toDouble(),Z.toDouble());
    Pnt.SetToolAxisVector(I.toDouble(),J.toDouble(),K.toDouble());

    //【更新点位置和刀轴参数】
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolAxis_I).UpdateDoubleVal(I.toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolAxis_J).UpdateDoubleVal(J.toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_ToolAxis_K).UpdateDoubleVal(K.toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_X).UpdateDoubleVal(X.toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_Y).UpdateDoubleVal(Y.toDouble());
    xpost.postData.ParametersMap.at(SYS_PARAM_Z).UpdateDoubleVal(Z.toDouble());
    //坐标转换（默认是双转台AC结构，有rtcp功能）
    if(xpost.postData.MachineInfo.Rtcp)
    {

    }
    if(xpost.postData.MachineInfo.LocalSystem)//支持局部坐标系
    {
      if(xpost.postData.ParametersMap.at(SYS_PARAM_AxisType).GetIntVal()==axisType_3)//定位加工
      {
        double Zaxis_i =  xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorI).GetDoubleVal();
        double Zaxis_j =  xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorJ).GetDoubleVal();
        double Zaxis_k =  xpost.postData.ParametersMap.at(SYS_PARAM_SystemZVectorK).GetDoubleVal();
        //计算AC角度
        Pnt.CalculateAC(Zaxis_i,Zaxis_j,Zaxis_k);
        //构建局部坐标系
        CoordinateSystem Sys = ConstructSystemByTwoVector(Pnt.A,Pnt.C);//a,c是弧度
        //【更新局部坐标系参数】
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneOriginX).UpdateDoubleVal(Sys.Origin.X);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneOriginY).UpdateDoubleVal(Sys.Origin.Y);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneOriginZ).UpdateDoubleVal(Sys.Origin.Z);

        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneXVectorI).UpdateDoubleVal(Sys.XVector.I);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneXVectorJ).UpdateDoubleVal(Sys.XVector.J);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneXVectorK).UpdateDoubleVal(Sys.XVector.K);

        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneYVectorI).UpdateDoubleVal(Sys.YVector.I);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneYVectorJ).UpdateDoubleVal(Sys.YVector.J);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneYVectorK).UpdateDoubleVal(Sys.YVector.K);

        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneZVectorI).UpdateDoubleVal(Sys.ZVector.I);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneZVectorJ).UpdateDoubleVal(Sys.ZVector.J);
        xpost.postData.ParametersMap.at(SYS_PARAM_WorkPlaneZVectorK).UpdateDoubleVal(Sys.ZVector.K);
      }
    }

};


CoordinateSystem postProcess::ConstructSystemByTwoVector(double a,double c)
{
  CoordinateSystem sys;
  return sys;
}

void postProcess::ReadCLSFAndWriteToNC()
{
    QFile file(clsfFullPath);
    QString aptflag = "aptsource";
    QString ncflag = "nc";
    QString ncfile = clsfFullPath.replace(clsfFullPath.indexOf(aptflag),aptflag.length(),ncflag);

    QFile outfile(ncfile);
    QTextStream stream(&outfile);
    //stream << "11111";
    processflag currentFlag = unknownFlag ;
    bool fistpoint = true;
    if (outfile.open(QIODevice::ReadWrite | QIODevice::Text)
            && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        vector<QString> tmp ;
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            //1.去除所有的空格
            str.replace(QRegExp(" "), "");
            //2.删除末尾的换行
            eraseWrap(str);
            //3.换行需要拼接
            if(!linkString(str,tmp))
                continue;
            //4.开始解析和写入NC
            //4.1程序头
            if(str.contains(catia_prog_start))
            {
              //【1.程序头】写入NC
              writeCommandToNC(SYS_CMD_PROGSTART,stream);
            }
            //4.3 换刀
            else if(str.contains(catia_tool_change_begin))
            {
               currentFlag = toolChangeFlag;
            }


            else if(str.contains(catia_coodnitate_sys))
            {
                UpdateSystemParameters(str);
            }
            else if(str.contains(catia_tool_num))//1.刀具号//2.长度补偿号//3.转速
            {
               UpdateToolSpindleParameters(str);
            }
            else if(str.contains(catia_tool_change_end))
            {
              //【2.换刀】写入NC
              writeCommandToNC(SYS_CMD_LOADTOOL,stream);
            }
            else if(str.contains(catia_path_start))
            {
              fistpoint = true;
            }
            //路径类型
            else if(str.contains(catia_path_type))
            {
              UpdateAxisTypeParameters(str);
            }
            //4.4 半径补偿和长度补偿号
            else if(str.contains(catia_tool_comp))// TLCOMP/1,ADJUST,1
            {
              UpdateToolCompAdjustParameters(str);
            }
            //4.5 进给
            else if(str.contains(catia_fedrat))//  【FEDRAT/  300.0000,MMPM】
            {
              UpdateFeedrateParameters(str);
            }
            //4.6 转速 m s
            else if(str.contains(catia_spindle_speed))//  【SPINDL/   70.0000,RPM,CLW】
            {
              UpdateSpindleParameters(str);
            }
            //4.7 刀位点 //GOTO/90.62016,10.00000,130.00000,0.000000,1.000000,0.000000】
            else if(str.contains(catia_apt_move))
            {
              UpdateMovelinearRapidParameters(str);

              if(fistpoint == true)
              {
                  //【3.路径开始】写入NC
                  writeCommandToNC(SYS_CMD_PATHSTART,stream);
                  //【4.换刀后第一次移动】写入NC
                  writeCommandToNC(SYS_CMD_FIRDTMOVEAFTERTOOL,stream);
                  fistpoint = false;
              }
              else
              {
                  if(xpost.postData.ParametersMap.at(SYS_PARAM_MotionMode).Value.curGroupValId == "rapid")
                  {
                      //G00
                      writeCommandToNC(SYS_CMD_MOVERAPID,stream);//写入NC
                  }
                  else if(xpost.postData.ParametersMap.at(SYS_PARAM_MotionMode).Value.curGroupValId == "linear")
                  {
                      //G01
                      writeCommandToNC(SYS_CMD_MOVELINEAR,stream);//写入NC
                  }
              }
            }
            //4.8 路径尾 END_OP/MILL
            else if(str.contains(catia_path_end))
            {
              writeCommandToNC(SYS_CMD_PATHEND,stream);//写入NC
            }
            //4.9 程序尾 catia_program_end
            else if(str==catia_path_end)
            {
              writeCommandToNC(SYS_CMD_PROGEND,stream);//写入NC
            }
        }
        file.close();
        outfile.close();
    }
}

void postProcess::eraseAllSpace(string &str)
{
    while(str.find(" ")!=string::npos)
    {
        size_t pos = str.find(" ");
        str.erase(pos,1);
    }
}

void postProcess::eraseWrap(QString &str)
{
    if(str.at(str.length()-1)=='\n')
    {
        str = str.mid(0,str.length()-1);//删掉末尾的 \r
    }
}
