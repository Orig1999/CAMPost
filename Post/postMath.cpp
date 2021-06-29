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
//单位化
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
//与另外一个向量反向
bool mathVector::isInverse(mathVector v2)
{
	//先单位化
	this->unitized();
	v2.unitized();

	//做点乘结果是一个数
	if((*this)*v2==-1)
		return true;
	else
		return false;
}
//与另外一个向量同向
bool mathVector::isSyntropy(mathVector v2)
{
	//先单位化
	this->unitized();
	v2.unitized();
	//做点乘结果是一个数
	if((*this)*v2==1)
		return true;
	else
		return false;
}
//计算与另外一个向量的夹角,弧度
double mathVector::getAngle(mathVector v2)//360或者2PI代表无效
{
	if( v2.isZero() || this->isZero())
	{
			return 2*math_pi;
	}
	else
	{
		double mode = v2.getMode()*this->getMode();
		double angle = acos((*this)*v2/mode);//重载*
	    return angle;
	}
}
//访问元素i,也可通过下标修改，注意必须返回引用才可以！
double & mathVector::operator [] (unsigned i)
{
	return elem[i];
}
//是否是0向量
bool mathVector::isZero()
{
	if(fabs(getMode())>TOLERANCE)
		return false;
	else
		return true;
}
//向量是否相等
bool operator == (mathVector &v1,mathVector &v2)
{
	for(unsigned i=0;i<v1.getLength();++i)
	{
		if(fabs(v1[i]-v2[i])>TOLERANCE)
			return false;
	}		
	return true;
}	
//向量的乘法（叉乘）仅仅支持三维向量 sin
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
//向量的乘法（点乘） cos
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
//绕着Y轴旋转矩阵
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
//绕着Z轴旋转矩阵
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

//绕着X轴旋转矩阵
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
//绕着Y轴旋转矩阵
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
//绕着Z轴旋转矩阵
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
//平移矩阵
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
//绕着任意向量旋转矩阵，该向量起点在坐标原点,angle（弧度制）
void  matrix::initRotateVector(mathVector v,double angle )
{
	if(v.getLength()!=3)
		return;

	setSize(4,4);

	//1.绕着X轴旋转angleX至XOZ面 Rx
	double cosa = v[2]/sqrt(v[1]*v[1]+v[2]*v[2]);
	double sina = v[1]/sqrt(v[1]*v[1]+v[2]*v[2]);
	matrix Rx(4,4);
	Rx.initRotateX(sina,cosa);

	//2.绕着Y轴旋转angleY与Z轴重合 Ry
	cosa = sqrt(v[1]*v[1]+v[2]*v[2])/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	sina = -1*v[0]/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	matrix Ry(4,4);
	Ry.initRotateX(sina,cosa);

	//3.绕着Z轴旋转angle (右手定则正向旋转)Rz
	matrix Rz(4,4);
	Rz.initRotateZ(angle);

	//4.乘以2和1的逆矩阵，
	//除了直接用公式求解逆矩阵外，由于是旋转变换，其逆就是反向旋转的矩阵
	//这里还是采用公式求
	matrix Rxi = Rx.getinverseMatrix();
	matrix Ryi = Ry.getinverseMatrix();

	matrix result = Rx*Ry*Rz*Ryi*Rxi;
	copy(result);
}
//绕着任意向量旋转矩阵，可指定向量的起点,angle（弧度制）
void  matrix::initRotateVector(mathVector v,point3D start,double angle)
{
	if(v.getLength()!=3)
		return;
	setSize(4,4);

	//1.先将向量移动到原点
	matrix To(4,4);
	To.initLinearMove(-1*start.getX(),-1*start.getY(),-1*start.getZ());

	//2.1 绕着X轴旋转angleX至XOZ面 Rx
	//2.2 绕着Y轴旋转angleY与Z轴重合 Ry
	//2.3 绕着Z轴旋转angle (右手定则正向旋转)Rz
	//2.4 乘以2.1和2.2的逆矩阵，
	matrix R(4,4);
	R.initRotateVector( v, angle );

	//3 乘以1的逆矩阵，
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
vecDou &  matrix::operator [](unsigned row)//也可通过下标修改，注意必须返回引用才可以！
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
	//a的第i行与b的第j列相乘作为c[i,j]
	for(unsigned i=0;i<a.getRowSize();++i)
	{
		mathVector v1(a.getColumnSize());//a的第i行向量
		for(unsigned k=0;k<a.getColumnSize();++k)
		{
			v1[k]= a[i][k];
		}

		for(unsigned j=0;j<b.getColumnSize();++j)
		{
			mathVector v2(b.getRowSize());//b的第j行向量
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
//是否是方阵
bool  matrix::isSquare()
{
	if(rowSize==columnSize &&rowSize!=0)
		return true;
	else
		return false;
}
//转置矩阵变换
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
//计算(r,c)元素的余子式矩阵
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
//计算代数余子式
double  matrix::getCofactor(unsigned i,unsigned j)
{
	matrix m1 = getComplementMinor(i,j);
	return pow(-1,(i+j))*m1.getDet();
}
//伴随矩阵
matrix  matrix::getAdjointMatrix()
{
	matrix result(rowSize,columnSize);
    for(unsigned i=0;i<rowSize;++i)
	{
        for(unsigned j=0;j<columnSize;++j)
		{
			result[i][j]= getCofactor(i,j);//构造代数余子式矩阵
		}
	}
	result.transpose();//做转置变换
	return result;
}
//计算对应的行列式的值
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
bool  matrix::canInverse()//方阵且对应的行列式为不为0
{
	if(isSquare() && fabs(getDet())>TOLERANCE)
		return true;
	else
		return false;
}
//求逆矩阵
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
		double model = getDet();//原始矩阵对应的行列式的值
		//inverseM[j][i]=double(pow(-1,i+j)*calDet3(remain)/calDet4(M));//代数余子式
		matrix adjoin = getAdjointMatrix();//求伴随矩阵
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
void point3D::Convert(matrix m)//右手定则
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
