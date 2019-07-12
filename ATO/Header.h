#pragma once
#ifndef _HEADER_
#define _HEADER_


#include "AtsPI.h"
#include "ATO/ATO.h"
#include "TASC/TASC.h"

#define LAG	200	//���胉�O[ms]

extern bool door;	//�h�A���
extern int Signal;	//�M���C���f�b�N�X
extern double Accelaration;	//�������x[km/h/s]
extern bool ATSKey[16];	//ATSkey���

extern SpecPlus Specific;	//�ԗ����\
extern StatePlus Status;	//�ԗ����
extern StatePlus Status_previous;	//�ԗ����(�O�t���[��)
extern Hand Manual;	//�蓮�n���h���ʒu
extern Hand Handle;	//�n���h������l


extern int ATCstatus;	//ATC���
extern int LimitSpeed;	//�������x
extern int MasCon_Key;	//�}�X�R���L�[
extern int lag_cnt;	//���O�p�J�E���^�[
extern bool isLoad;	//���O����`�B�p

extern c_ATO ATO;	//ATO
extern c_TASC TASC;	//TASC

void reload(void);	//�w�W�����v���ēǂݍ��ݏ���
void SetStatus();	//ATO/TASC�X�C�b�`����
void setKey(int);	//�}�X�R���L�[����


#endif // !_HEADER_