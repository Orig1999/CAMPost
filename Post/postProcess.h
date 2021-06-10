#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include "postcommand.h"
#include <list>
#include <fstream>
#include "postParameter.h"
#include "XPost.h"
using namespace std;

enum pntType
{
   unknownPnt,
   linearPnt,
   circlePnt,
   cyclePnt
};

class post3DPoint
{
public:
   double X;
   double Y;
   double Z;
};

class post3DVector
{
public:
   double I;
   double J;
   double K;
};

class circleData
{
public:
  post3DVector StartVector;//起始点向量
  double R;//半径
};

class cutterLocPosition//刀位点
{
public:
    pntType PointType;
    post3DPoint ToolLocation;
    post3DVector ToolAxis;
    circleData CircleData;
};
class postPath//路径
{
    postCommand PathStart;
    postCommand RapidMove;
    postCommand LinearMove;
    postCommand FirstLinearMove;
    postCommand ToolChange;
    postCommand SpindleOn;
    postCommand CollantOn;
    list<cutterLocPosition> PathList;
    postCommand SpindleOff;
    postCommand CollantOff;
    postCommand PathEnd;
};
class postProgram//程序
{
    postCommand ProgramStart;
    list<postPath> PathList;
    postCommand ProgramEnd;

};




class postProcess
{
  postProgram NCProgram;
  XPost xpost;
  void UpdateProgramParameters()//文件名称。。。
  {

  };
  void UpdatePathParameters()//路径名称。。。
  {

  };
  void UpdateToolParameters()//刀具名称，半径，刀具号，半径补偿号，长度补偿号。。。
  {

  };

  void UpdateCLPntParameters()//XYZABCIJK...
  {

  };


  void ReadCLSFAndWriteToNC(string clsfFullPath,string ncFullPath)
  {
    ifstream infile(clsfFullPath);
    ofstream outfile(ncFullPath,ios::trunc);



    //读
    string line="";
    while(getline(infile,line))
    {
      if(line.find("XXX"))//更新程序相关参数
      {

      }
      else if(line.find("XXX"))//更新路径相关参数
      {

      }
      else if(line.find("XXX"))//更新刀具相关参数
      {

      }
      else if(line.find("XXX"))//更新刀位点相关参数
      {

      }

    }

    //写
    outfile<<"";

    outfile.close();
    infile.close();
  }

};




#endif // POSTPROCESS_H
