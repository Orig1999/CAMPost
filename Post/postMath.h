#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include <qdebug.h>
using namespace std;
typedef vector<double> vecDou;
typedef vector<vecDou> Elem;
const double TOLERANCE = 0.00001;
const double math_pi = 3.1415926;
//均采用右手定则
class point3D;
//向量
class mathVector
{
private:
	vecDou elem;
	unsigned length;
public:
	void print()
	{
		for(unsigned i=0;i<getLength();++i)
		{
            qDebug()<<elem[i]<<"  ";
		}
        qDebug()<<endl;
	}
	unsigned getLength()
	{
		return length;
	}
	mathVector(int l)
	{
		length = l;
		elem.resize(l);
	}
	mathVector()
	{

	}
	~mathVector()
	{

	}
	//计算模
	double getMode();
	//单位化
	bool unitized();
	//与另外一个向量反向
	bool isInverse(mathVector v2);
	//与另外一个向量同向
	bool isSyntropy(mathVector v2);
	//计算与另外一个向量的夹角,0：返回弧度:1：返回角度
	double getAngle(mathVector v2);//360或者2PI代表无效
	//访问元素i,也可通过下标修改，注意必须返回引用才可以！
	double & operator [] (unsigned i);
	//是否是0向量
	bool isZero();

	//友元函数
	//向量是否相等
	friend bool operator == (mathVector &v1,mathVector &v2);
	//向量的乘法（叉乘）仅仅支持三维向量 sin
	friend mathVector operator ^( mathVector &v1, mathVector &v2);
	//向量的乘法（点乘） cos
	friend double operator *( mathVector &v1, mathVector &v2);
};
//矩阵
class matrix
{
private:
	unsigned rowSize;
	unsigned columnSize;
	Elem elem;
	void setSize(int r,int c)
	{
		elem.resize(r);
		for(unsigned i=0;i<elem.size();++i)
		{
			elem[i].resize(c);
		}
		rowSize = r;
		columnSize = c;
	}
public :
	void copy(matrix &m)
	{
		*this = m;
	}
	//绕着X轴旋转矩阵
	void initRotateX(double angle);
	//绕着Y轴旋转矩阵
	void initRotateY(double angle);
	//绕着Z轴旋转矩阵
	void initRotateZ(double angle);

	//绕着X轴旋转矩阵
	void initRotateX(double sina,double cosa);
	//绕着Y轴旋转矩阵
	void initRotateY(double sina,double cosa);
	//绕着Z轴旋转矩阵
	void initRotateZ(double sina,double cosa);

	//平移矩阵
	void initLinearMove(double x,double y,double z);
	//绕着任意向量旋转矩阵，该向量起点在坐标原点,angle（isRadian =true 弧度制）
	void initRotateVector(mathVector v,double angle);
	//绕着任意向量旋转矩阵，可指定向量的起点,angle（isRadian =true 弧度制）
	void initRotateVector(mathVector v,point3D start,double angle);

	void print();
	unsigned getRowSize();
	unsigned getColumnSize();
	vecDou & operator [](unsigned row);//也可通过下标修改，注意必须返回引用才可以！

	void operator/(double val);
	//是否是方阵
	bool isSquare();
	//转置矩阵变换
	void transpose();
	//计算(r,c)元素的余子式矩阵
	matrix getComplementMinor(unsigned r,unsigned c);
	//计算代数余子式
	double getCofactor(unsigned i,unsigned j);
	//伴随矩阵
	matrix getAdjointMatrix();
	//计算对应的行列式的值
	double getDet();

	bool canInverse();//方阵且对应的行列式为不为0

	//求逆矩阵
	matrix getinverseMatrix();
	matrix()
	{

	}
	~matrix()
	{

	}
	matrix(unsigned r,unsigned c);
	friend matrix operator * ( matrix a, matrix b);
};
//三维点
class point3D
{
private:
	double x;
	double y;
	double z;
public:
	point3D()
	{
	}
	point3D(double val1,double val2,double val3)
	{
		x=val1;
		y=val2;
		z=val3;
	}
	~point3D()
	{
	}
	void print()
	{
		if(fabs(x)<TOLERANCE)
            qDebug()<<0<<"  ";
		else
            qDebug()<<x<<"  ";

		if(fabs(y)<TOLERANCE)
            qDebug()<<0<<"  ";
		else
            qDebug()<<y<<"  ";

		if(fabs(z)<TOLERANCE)
            qDebug()<<0<<"  ";
		else
            qDebug()<<z<<"  ";
        qDebug()<<endl;
        //qDebug()<<x<<","<<y<<","<<z<<endl;
	}
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getZ()
	{
		return z;
	}

	void Rotate(mathVector v,point3D start,double angle);
	void Convert(matrix m);//右手定则
};
