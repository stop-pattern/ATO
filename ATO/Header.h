#pragma once
#include "pch.h"

extern bool door;	//�h�A���
extern int Signal;	//�M���C���f�b�N�X
extern double Speed;	//���ݑ��x[km/h]
extern double Distance;	//���݈ʒu[m]
extern double Accelaration;	//�������x[km/h/s]
extern bool ATSKey[16];	//ATSkey���

extern Spec Specific;	//�ԗ����\
extern State Status;	//�ԗ����
extern State Status_previous;	//�ԗ����(�O�t���[��)
extern Hand Manual;	//�蓮�n���h���ʒu
extern Hand Handle;	//�n���h������l