#pragma once
#include "pch.h"

extern bool door;	//ドア状態
extern int Signal;	//信号インデックス
extern double Speed;	//現在速度[km/h]
extern double Distance;	//現在位置[m]
extern double Accelaration;	//加減速度[km/h/s]
extern bool ATSKey[16];	//ATSkey状態

extern Spec Specific;	//車両性能
extern State Status;	//車両状態
extern State Status_previous;	//車両状態(前フレーム)
extern Hand Manual;	//手動ハンドル位置
extern Hand Handle;	//ハンドル制御値