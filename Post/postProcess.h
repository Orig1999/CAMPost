#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include "postcommand.h"
#include <list>
#include <fstream>
#include <QFile>
#include <string>
#include "postParameter.h"
#include "XPost.h"
#include <QTextCodec>
#include "CLFSmbol.h"
#include "postMath.h"
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

class CoordinateSystem
{
public:
    post3DPoint Origin;//原点
    post3DVector XVector;
    post3DVector YVector;
    post3DVector ZVector;
};


class circleData
{
public:
  post3DPoint Center;
  post3DVector StartVector;//起始点向量
  double R;//半径
  bool isFull;//整圆
};

class cutterLocPosition//刀位点
{
public:
    cutterLocPosition()
    {

    }
    ~cutterLocPosition()
    {

    }
    pntType PointType;
    post3DPoint ToolPosition;
    post3DVector ToolAxis;
    circleData CircleData;
    double A;
    double C;
    void CalculateAC(double i,double j,double k);
    void SetToolPosition(double x,double y,double z);
    void SetToolAxisVector(double i,double j,double k);

    //设置圆弧数据
    void SetCircleCenter(double x,double y,double z);
    void SetCircleStartVector(double i,double j,double k);
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


enum processflag
{
    unknownFlag,

    programStartFlag,
    toolChangeFirstFlag,
    toolChangeFlag,
    pathStartFlag,

    pathEndFlag,
    programEndFlag
};

class postProcess
{
public:
  postProgram NCProgram;
  XPost xpost;
  QString clsfFullPath;
  postProcess()
  {

  }
  ~postProcess()
  {

  }
  postProcess(QString path,XPost post);
  bool linkString(QString &str,vector<QString> &tmp);
  void writeCommandToNC(int cmdID,QTextStream &stream);
  void UpdateToolSpindleParameters(QString str);//刀具号，长度补偿号 转速
  void UpdateToolCompAdjustParameters(QString str);//半径补偿号，长度补偿号
  void UpdateSystemParameters(QString str);

  void UpdateFeedrateParameters(QString str);
  void UpdateSpindleParameters(QString str);
  void UpdateMovelinearRapidParameters(QString str);
  void UpdateAxisTypeParameters(QString str);
  void ReadCLSFAndWriteToNC();
  CoordinateSystem ConstructSystemByTwoVector(double a,double c);
  void eraseAllSpace(string &str);
  void eraseWrap(QString &str);

};

#endif // POSTPROCESS_H
