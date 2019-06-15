//Headder for ATS Plugin
//Author Tetsu Otter
#pragma once
#include "./pch.h"

//DLL import��Z�k
#define DE extern "C" __declspec(dllexport)
//���̂��߂��Y�ꂽ���Ǔ���Ƃ�
#define SC __stdcall
//�v���O�C���̃o�[�W����
#define PI_VERSION 0x00020000

struct Spec		//��Ԃ̃X�y�b�N�Ɋւ�����
{
	int B = 0;	//�u���[�L�i��
	int P = 0;	//�m�b�`�i��
	int A = 0;	//ATS�m�F�i��
	int J = 0;	//��p�i��67�x����
	int C = 0;	//�Ґ��ԗ���
	int E = 0;	//���i��
};
struct State		//��ԏ�ԂɊւ�����
{
	double Z = 0;	//��Ԉʒu[m]
	double V = 0;	//��ԑ��x[km/h]
	int T = 0;		//0������̌o�ߎ���[ms]
	double BC = 0;	//BC����[kPa]
	double MR = 0;	//MR����[kPa]
	double ER = 0;	//ER����[kPa]
	double BP = 0;	//BP����[kPa]
	double SAP = 0;	//SAP����[kPa]
	double I = 0;	//�d��[A]
	double A = 0;	//�������x[km/h/s]
};
struct Hand		//�n���h���ʒu�Ɋւ�����
{
	int B = 0;	//�u���[�L�n���h���ʒu
	int P = 0;	//�m�b�`�n���h���ʒu
	int R = 0;	//���o�[�T�[�n���h���ʒu
	int C = 0;	//�葬������
};
struct Beacon		//Beacon�Ɋւ�����
{
	int Num = 0;	//Beacon�̔ԍ�
	int Sig = 0;	//�Ή�����ǂ̌����ԍ�
	double X = 0;	//�Ή�����ǂ܂ł̋���[m]
	int Data = 0;	//Beacon�̑�O�����̒l
};

enum Reverser	//���o�[�T�[�ʒu
{
	Back = -1,	//��i
	Neutral,	//����
	Forward		//�O�i
};
enum ConstSPInfo//�葬����̏��
{
	Continue,	//�O��̏�Ԃ��p������
	Enable,		//�L��������
	Disable		//����������
};
enum HornInfo	//�x�J�̔ԍ�
{
	Horn1,		//Primary Horn
	Horn2,		//Secondary Horn
	MusicHorn	//Horn Music
};
enum SoundInfo	//�T�E���h�̑�����
{
	PlayLoop,	//�J��Ԃ��Đ�����
	PlayOnce,	//1�x�����Đ�����
	PlayContinue,	//�O��̏�Ԃ��p������
	Stop = -1000//�Đ����~����
};
enum InitialPosition	//�n���h���̏����ʒu�ݒ�
{
	Service,			//��p�u���[�L(B67?)
	Emergency,			//���u���[�L(EB)
	Removed				//�������ʒu
};
enum ATSKeys	//�L�[�������
{
	S,	//space
	A1,	//home
	A2,	//end
	B1,	//insert
	B2,	//delete
	C1,	//page up
	C2,	//page down
	D,	//2
	E,	//3
	F,	//4
	G,	//5
	H,	//6
	I,	//7
	J,	//8
	K,	//9
	L,	//0
};



DE void SC Load(void);
DE void SC Dispose(void);
DE int SC GetPluginVersion(void);
DE void SC SetVehicleSpec(Spec);
DE void SC Initialize(int);
DE Hand SC Elapse(State, int*, int*);
DE void SC SetPower(int);
DE void SC SetBrake(int);
DE void SC SetReverser(int);
DE void SC KeyDown(int);
DE void SC KeyUp(int);
DE void SC HornBlow(int);
DE void SC DoorOpen(void);
DE void SC DoorClose(void);
DE void SC SetSignal(int);
DE void SC SetBeaconData(Beacon);