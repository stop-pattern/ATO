#include "pch/pch.h"
#include "Header.h"

bool door;	//�h�A���
int Signal;	//�M���C���f�b�N�X
double Speed;	//���ݑ��x[km/h]
double Distance;	//���݈ʒu[m]
double Accelaration;	//�������x[km/h/s]
bool ATSKey[16];	//ATSkey���

SpecPlus Specific;	//�ԗ����\
State Status;	//�ԗ����
State Status_previous;	//�ԗ����(�O�t���[��)
Hand Manual;	//�蓮�n���h���ʒu
Hand Handle;	//�n���h������l