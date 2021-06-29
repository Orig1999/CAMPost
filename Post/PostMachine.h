#ifndef POSTMACHINE_H
#define POSTMACHINE_H
#include <QString>
using namespace std;

enum MachineStructType//�����ṹ
{
	T_3axis,
    TT_4axis_A,
    TT_4axis_B,
    TT_5axis_AC,
    TT_5axis_BC
};
enum MachineNCSType
{
    NCS_fanuc,
    NCS_JD50,
    NCS_HeidenHain
};
class PostMachineInfo
{
public :
    PostMachineInfo();
    bool Rtcp;
    bool LocalSystem;
	MachineStructType StructType;//�����ṹ����
	MachineNCSType NCSType ;//����ϵͳ����
};

#endif // POSTMACHINE_H
