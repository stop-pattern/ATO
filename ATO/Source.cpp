#include "AtsPI.h"
#include "Header.h"

bool door;	//�h�A���
int Signal;	//�M���C���f�b�N�X
double Accelaration;	//�������x[km/h/s]
bool ATSKey[16];	//ATSkey���

SpecPlus Specific;	//�ԗ����\
StatePlus Status;	//�ԗ����
StatePlus Status_previous;	//�ԗ����(�O�t���[��)
Hand Manual;	//�蓮�n���h���ʒu
Hand Handle;	//�n���h������l


int ATCstatus;	//ATC���
int LimitSpeed;	//�������x
int MasCon_Key;	//�}�X�R���L�[

c_ATO ATO;	//ATO
c_TASC TASC;	//TASC