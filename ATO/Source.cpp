#include "pch/pch.h"
#include "Header.h"

bool door;	//ドア状態
int Signal;	//信号インデックス
double Speed;	//現在速度[km/h]
double Distance;	//現在位置[m]
double Accelaration;	//加減速度[km/h/s]
bool ATSKey[16];	//ATSkey状態

SpecPlus Specific;	//車両性能
State Status;	//車両状態
State Status_previous;	//車両状態(前フレーム)
Hand Manual;	//手動ハンドル位置
Hand Handle;	//ハンドル制御値