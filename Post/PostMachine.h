#ifndef POSTMACHINE_H
#define POSTMACHINE_H
#include <QString>
using namespace std;

enum MachineStructType//机床结构
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

	MachineStructType StructType;//机床结构类型
	MachineNCSType NCSType ;//数控系统类型
};

#endif // POSTMACHINE_H
