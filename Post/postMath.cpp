#include "postMath.h"

double mathVector::getMode()
{
	double result = 0;
	for(unsigned i=0;i<getLength();++i)
	{
		result = result + elem[i]*elem[i];
	}	
	if(fabs(result)>TOLERANCE)
		return sqrt(result);
	else
		return 0;
}
//��λ��
bool mathVector::unitized()
{
	if(isZero())
		return false;

	double mode = getMode();
	for(unsigned i=0;i<getLength();++i)
	{
		elem[i]=elem[i]/mode;
	}
	return true;
}
//������һ����������
bool mathVector::isInverse(mathVector v2)
{
	//�ȵ�λ��
	this->unitized();
	v2.unitized();

	//����˽����һ����
	if((*this)*v2==-1)
		return true;
	else
		return false;
}
//������һ������ͬ��
bool mathVector::isSyntropy(mathVector v2)
{
	//�ȵ�λ��
	this->unitized();
	v2.unitized();
	//����˽����һ����
	if((*this)*v2==1)
		return true;
	else
		return false;
}
//����������һ�������ļн�,����
double mathVector::getAngle(mathVector v2)//360����2PI������Ч
{
	if( v2.isZero() || this->isZero())
	{
			return 2*math_pi;
	}
	else
	{
		double mode = v2.getMode()*this->getMode();
		double angle = acos((*this)*v2/mode);//����*
	    return angle;
	}
}
//����Ԫ��i,Ҳ��ͨ���±��޸ģ�ע����뷵�����òſ��ԣ�
double & mathVector::operator [] (unsigned i)
{
	return elem[i];
}
//�Ƿ���0����
bool mathVector::isZero()
{
	if(fabs(getMode())>TOLERANCE)
		return false;
	else
		return true;
}
//�����Ƿ����
bool operator == (mathVector &v1,mathVector &v2)
{
	for(unsigned i=0;i<v1.getLength();++i)
	{
		if(fabs(v1[i]-v2[i])>TOLERANCE)
			return false;
	}		
	return true;
}	
//�����ĳ˷�����ˣ�����֧����ά���� sin
mathVector operator ^( mathVector &v1, mathVector &v2)
{
	if( v1.getLength()==v2.getLength() 
		&& v1.getLength()==3)
	{
		mathVector v3(3);
		double a1 = v1[0];
		double b1 = v1[1];
		double c1 = v1[2];

		double a2 = v2[0];
		double b2 = v2[1];
		double c2 = v2[2];

		v3[0]=b1*c2-b2*c1;
		v3[1]=c1*a2-c2*a1;
		v3[2]=a1*b2-a2*b1;

		return v3; 
	}
	else
	{
		mathVector v3(1);
		v3[0]=-99999999;
		return v3;
	}
}
//�����ĳ˷�����ˣ� cos
double operator *( mathVector &v1, mathVector &v2)
{
	if( v1.getLength()==v2.getLength() 
		&& v1.getLength()>0 && v2.getLength()>0 )
	{
		double result = 0;
		mathVector v3(v1.getLength());
		for(unsigned i=0;i<v1.getLength();++i)
		{
			result = result + v1[i]*v2[i];
		}
		return result;
	}
	else
		return -999999;
}




void matrix::initRotateX(double angle)
{
	setSize(4,4);
	elem[0][0]=1;
	elem[0][1]=0;
	elem[0][2]=0;
	elem[0][3]=0;

	elem[1][0]=0;
	elem[1][1]=cos(angle);
	elem[1][2]=-sin(angle);
	elem[1][3]=0;

	elem[2][0]=0;
	elem[2][1]=sin(angle);
	elem[2][2]=cos(angle);
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//����Y����ת����
void  matrix::initRotateY(double angle)
{
	setSize(4,4);
	elem[0][0]=cos(angle);
	elem[0][1]=0;
	elem[0][2]=-sin(angle);
	elem[0][3]=0;

	elem[1][0]=0;
	elem[1][1]=1;
	elem[1][2]=0;
	elem[1][3]=0;

	elem[2][0]=sin(angle);
	elem[2][1]=0;
	elem[2][2]=cos(angle);
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//����Z����ת����
void  matrix::initRotateZ(double angle)
{
	setSize(4,4);
	elem[0][0]=cos(angle);
	elem[0][1]=sin(angle);
	elem[0][2]=0;
	elem[0][3]=0;

	elem[1][0]=-sin(angle);
	elem[1][1]=cos(angle);
	elem[1][2]=0;
	elem[1][3]=0;

	elem[2][0]=0;
	elem[2][1]=0;
	elem[2][2]=1;
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}

//����X����ת����
void  matrix::initRotateX(double sina,double cosa)
{
	setSize(4,4);
	elem[0][0]=1;
	elem[0][1]=0;
	elem[0][2]=0;
	elem[0][3]=0;

	elem[1][0]=0;
	elem[1][1]=cosa;
	elem[1][2]=sina;
	elem[1][3]=0;

	elem[2][0]=0;
	elem[2][1]=-sina;
	elem[2][2]=cosa;
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//����Y����ת����
void  matrix::initRotateY(double sina,double cosa)
{
	setSize(4,4);
	elem[0][0]=cosa;
	elem[0][1]=0;
	elem[0][2]=-sina;
	elem[0][3]=0;

	elem[1][0]=0;
	elem[1][1]=1;
	elem[1][2]=0;
	elem[1][3]=0;

	elem[2][0]=sina;
	elem[2][1]=0;
	elem[2][2]=cosa;
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//����Z����ת����
void  matrix::initRotateZ(double sina,double cosa)
{
	setSize(4,4);
	elem[0][0]=cosa;
	elem[0][1]=sina;
	elem[0][2]=0;
	elem[0][3]=0;

	elem[1][0]=-sina;
	elem[1][1]=cosa;
	elem[1][2]=0;
	elem[1][3]=0;

	elem[2][0]=0;
	elem[2][1]=0;
	elem[2][2]=1;
	elem[2][3]=0;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//ƽ�ƾ���
void  matrix::initLinearMove(double x,double y,double z)
{
	setSize(4,4);
	elem[0][0]=1;
	elem[0][1]=0;
	elem[0][2]=0;
	elem[0][3]=x;

	elem[1][0]=0;
	elem[1][1]=1;
	elem[1][2]=0;
	elem[1][3]=y;

	elem[2][0]=0;
	elem[2][1]=0;
	elem[2][2]=1;
	elem[2][3]=z;

	elem[3][0]=0;
	elem[3][1]=0;
	elem[3][2]=0;
	elem[3][3]=1;
}
//��������������ת���󣬸��������������ԭ��,angle�������ƣ�
void  matrix::initRotateVector(mathVector v,double angle )
{
	if(v.getLength()!=3)
		return;

	setSize(4,4);

	//1.����X����תangleX��XOZ�� Rx
	double cosa = v[2]/sqrt(v[1]*v[1]+v[2]*v[2]);
	double sina = v[1]/sqrt(v[1]*v[1]+v[2]*v[2]);
	matrix Rx(4,4);
	Rx.initRotateX(sina,cosa);

	//2.����Y����תangleY��Z���غ� Ry
	cosa = sqrt(v[1]*v[1]+v[2]*v[2])/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	sina = -1*v[0]/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	matrix Ry(4,4);
	Ry.initRotateX(sina,cosa);

	//3.����Z����תangle (���ֶ���������ת)Rz
	matrix Rz(4,4);
	Rz.initRotateZ(angle);

	//4.����2��1�������
	//����ֱ���ù�ʽ���������⣬��������ת�任��������Ƿ�����ת�ľ���
	//���ﻹ�ǲ��ù�ʽ��
	matrix Rxi = Rx.getinverseMatrix();
	matrix Ryi = Ry.getinverseMatrix();

	matrix result = Rx*Ry*Rz*Ryi*Rxi;
	copy(result);
}
//��������������ת���󣬿�ָ�����������,angle�������ƣ�
void  matrix::initRotateVector(mathVector v,point3D start,double angle)
{
	if(v.getLength()!=3)
		return;
	setSize(4,4);

	//1.�Ƚ������ƶ���ԭ��
	matrix To(4,4);
	To.initLinearMove(-1*start.getX(),-1*start.getY(),-1*start.getZ());

	//2.1 ����X����תangleX��XOZ�� Rx
	//2.2 ����Y����תangleY��Z���غ� Ry
	//2.3 ����Z����תangle (���ֶ���������ת)Rz
	//2.4 ����2.1��2.2�������
	matrix R(4,4);
	R.initRotateVector( v, angle );

	//3 ����1�������
	matrix Toi = To.getinverseMatrix();
	matrix result = To*R*Toi;
	copy(result);
}
void  matrix::print()
{
	for(unsigned i=0;i<getRowSize();++i)
	{
		mathVector v1(getColumnSize());
		for(unsigned k=0;k<getColumnSize();++k)
		{
			if(fabs(elem[i][k])<TOLERANCE)

                qDebug()<<0<<"  ";
			else
                qDebug()<<elem[i][k]<<"  ";
		}
        qDebug()<<endl;
	}
    qDebug()<<endl;
}
unsigned  matrix::getRowSize()
{
	return rowSize;
}
unsigned  matrix::getColumnSize()
{
	return columnSize;
}
vecDou &  matrix::operator [](unsigned row)//Ҳ��ͨ���±��޸ģ�ע����뷵�����òſ��ԣ�
{
	return elem[row];
}
matrix::matrix(unsigned r,unsigned c)
{
	setSize( r, c);
}
matrix operator * ( matrix a, matrix b)
{
	matrix c(a.getRowSize(),b.getColumnSize());
	//a�ĵ�i����b�ĵ�j�������Ϊc[i,j]
	for(unsigned i=0;i<a.getRowSize();++i)
	{
		mathVector v1(a.getColumnSize());//a�ĵ�i������
		for(unsigned k=0;k<a.getColumnSize();++k)
		{
			v1[k]= a[i][k];
		}

		for(unsigned j=0;j<b.getColumnSize();++j)
		{
			mathVector v2(b.getRowSize());//b�ĵ�j������
			for(unsigned jj=0;jj<b.getRowSize();++jj)
			{
				v2[jj]=b[jj][j];
			}
			c[i][j]=v1*v2;
		}	
	}
	return c;
}
void  matrix::operator/(double val)
{
	if(fabs(val)>TOLERANCE)
		return;
    for(unsigned i=0;i<rowSize;++i)
	{
        for(unsigned j=0;j<columnSize;++j)
		{
			elem[i][j]= elem[i][j]/val;
		}
	}
}
//�Ƿ��Ƿ���
bool  matrix::isSquare()
{
	if(rowSize==columnSize &&rowSize!=0)
		return true;
	else
		return false;
}
//ת�þ���任
void  matrix::transpose()
{
    for(unsigned i=0;i<rowSize;++i)
	{
        for(unsigned j=i+1;j<columnSize;++j)
		{
			double tmp = elem[i][j];
			elem[i][j]=elem[j][i];
			elem[j][i] = tmp;
		}
	}     
}
//����(r,c)Ԫ�ص�����ʽ����
matrix  matrix::getComplementMinor(unsigned r,unsigned c)
{
	if(!isSquare())
	{
		matrix result(1,1);
		result[0][0]=-99999;
		return result;
	}
	else
	{
		matrix result(rowSize-1,columnSize-1);
		int newRow = 0;
        for(unsigned i=0;i<rowSize;++i)
		{
			if(i==r)
				continue;
			int newCol = 0;
            for(unsigned j=0;j<columnSize;++j)
			{
				if(j==c)
					continue;
				result[newRow][newCol]=elem[i][j];
				++newCol;
			}
			++newRow;
		}
		return result ;
	}
}
//�����������ʽ
double  matrix::getCofactor(unsigned i,unsigned j)
{
	matrix m1 = getComplementMinor(i,j);
	return pow(-1,(i+j))*m1.getDet();
}
//�������
matrix  matrix::getAdjointMatrix()
{
	matrix result(rowSize,columnSize);
    for(unsigned i=0;i<rowSize;++i)
	{
        for(unsigned j=0;j<columnSize;++j)
		{
			result[i][j]= getCofactor(i,j);//�����������ʽ����
		}
	}
	result.transpose();//��ת�ñ任
	return result;
}
//�����Ӧ������ʽ��ֵ
double  matrix::getDet()
{
	if(!isSquare())
		return -999999;
	if(rowSize>2)
	{
		double result = 0;
        for(unsigned i=0;i<rowSize;++i)
		{
			result = result + elem[i][0]*getCofactor(i,0);
		}
		return result;
	}
	else
		return elem[0][0]*elem[1][1]-elem[1][0]*elem[0][1];
}
bool  matrix::canInverse()//�����Ҷ�Ӧ������ʽΪ��Ϊ0
{
	if(isSquare() && fabs(getDet())>TOLERANCE)
		return true;
	else
		return false;
}
//�������
matrix  matrix::getinverseMatrix()
{
	if(!canInverse())
	{
		matrix result(1,1);
		result[0][0]=-99999;
		return result;
	}
	else
	{
		double model = getDet();//ԭʼ�����Ӧ������ʽ��ֵ
		//inverseM[j][i]=double(pow(-1,i+j)*calDet3(remain)/calDet4(M));//��������ʽ
		matrix adjoin = getAdjointMatrix();//��������
		adjoin/model;
		return adjoin;
	}
}




void point3D::Rotate(mathVector v,point3D start,double angle)
{
	matrix m(4,4);
	m.initRotateVector(v,start,angle);
	//m.print();
	Convert(m);
}
void point3D::Convert(matrix m)//���ֶ���
{
	if( m.getRowSize()!=4 || m.getColumnSize()!=4)
		return;

	matrix m1(1,4);
	m1[0][0]=x;
	m1[0][1]=y;
	m1[0][2]=z;
	m1[0][3]=1;
	matrix result = m1*m;

	x= result[0][0];
	y= result[0][1];
	z= result[0][2];
}
