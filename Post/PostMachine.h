#ifndef POSTMACHINE_H
#define POSTMACHINE_H
#include <QString>
using namespace std;

enum MachineStructType//�����ṹ
{
	T_3axis,
	TT_4axis,
	TT_5axis
};
enum MachineNCSType
{
	JD45,
	JD50
};
class PostMachineInfo
{
public :
    PostMachineInfo();

	MachineStructType StructType;//�����ṹ����
	MachineNCSType NCSType ;//����ϵͳ����
};

#endif // POSTMACHINE_H
