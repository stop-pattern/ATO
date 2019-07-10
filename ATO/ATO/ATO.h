#pragma once
#ifndef _ATO_
#define _ATO_

#include "../AtsPI.h"

#define ATO_CSC_TIME 2500	//ATO�葬���莞��


class c_ATO {
public:
	void Control(State, int *, int *);	//���t���[������
	void CSC(void);	//ATO�葬
	bool Departure(void);	//�o���{�^������
	void SignalChange();	//�����ύX
	void ChangeMode(int);	//�^�]���[�h�ύX
	void setPattern(Beacon); 	//�n��q����
	void inEmergency(void);	//������
	void Forward_Deceleration(int, int);	//���O����

	Hand control;	//�n���h������l
	double Limit;	//�ڕW���x
private:
	bool isFD;	//ATO���O����
	Beacon brake;	//ATO���O�����p�n��q���
	int TargetSpeed;	//�ڕW���x
	double Location;	//�ڕW�ʒu
	double Distance;	//�c����

	bool isCSC;	//ATO�葬
	int CSCspeed;	//�葬�ێ����x
	long int CSCcnt;	//�葬����
	int Mode = 1;	//ATO�^�]���[�h
	int margin;	//�����P�\���x
	int button_buf;	//�{�^�����������O����p

	//ATO�ڕW���x
	const int Reference_Speed[4][256] = {
	{0,25,45,65,100,0,0,0,0,0,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,120,0,30,0,0,0,45,40,35,30,25,20,15,10,5,0,0,0,25,40,65},
	{0,0,0,0,0,0,0,0,0,0,0,5,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,115,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,7,7,12,17,22,27,32,37,42,47,52,57,62,67,72,77,82,87,92,97,102,107,117,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,5,5,10,15,20,20,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	//ATO�^�]���[�h
	enum ATOmode {
		ATC�Ǐ],
		ATO����,
		ATO��,
		ATO�x��,
	};
};

#endif // _ATO_