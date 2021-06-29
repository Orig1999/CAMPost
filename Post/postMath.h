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
//���������ֶ���
class point3D;
//����
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
	//����ģ
	double getMode();
	//��λ��
	bool unitized();
	//������һ����������
	bool isInverse(mathVector v2);
	//������һ������ͬ��
	bool isSyntropy(mathVector v2);
	//����������һ�������ļн�,0�����ػ���:1�����ؽǶ�
	double getAngle(mathVector v2);//360����2PI������Ч
	//����Ԫ��i,Ҳ��ͨ���±��޸ģ�ע����뷵�����òſ��ԣ�
	double & operator [] (unsigned i);
	//�Ƿ���0����
	bool isZero();

	//��Ԫ����
	//�����Ƿ����
	friend bool operator == (mathVector &v1,mathVector &v2);
	//�����ĳ˷�����ˣ�����֧����ά���� sin
	friend mathVector operator ^( mathVector &v1, mathVector &v2);
	//�����ĳ˷�����ˣ� cos
	friend double operator *( mathVector &v1, mathVector &v2);
};
//����
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
	//����X����ת����
	void initRotateX(double angle);
	//����Y����ת����
	void initRotateY(double angle);
	//����Z����ת����
	void initRotateZ(double angle);

	//����X����ת����
	void initRotateX(double sina,double cosa);
	//����Y����ת����
	void initRotateY(double sina,double cosa);
	//����Z����ת����
	void initRotateZ(double sina,double cosa);

	//ƽ�ƾ���
	void initLinearMove(double x,double y,double z);
	//��������������ת���󣬸��������������ԭ��,angle��isRadian =true �����ƣ�
	void initRotateVector(mathVector v,double angle);
	//��������������ת���󣬿�ָ�����������,angle��isRadian =true �����ƣ�
	void initRotateVector(mathVector v,point3D start,double angle);

	void print();
	unsigned getRowSize();
	unsigned getColumnSize();
	vecDou & operator [](unsigned row);//Ҳ��ͨ���±��޸ģ�ע����뷵�����òſ��ԣ�

	void operator/(double val);
	//�Ƿ��Ƿ���
	bool isSquare();
	//ת�þ���任
	void transpose();
	//����(r,c)Ԫ�ص�����ʽ����
	matrix getComplementMinor(unsigned r,unsigned c);
	//�����������ʽ
	double getCofactor(unsigned i,unsigned j);
	//�������
	matrix getAdjointMatrix();
	//�����Ӧ������ʽ��ֵ
	double getDet();

	bool canInverse();//�����Ҷ�Ӧ������ʽΪ��Ϊ0

	//�������
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
//��ά��
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
	void Convert(matrix m);//���ֶ���
};
