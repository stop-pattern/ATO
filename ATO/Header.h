#pragma once
#ifndef _HEADER_
#define _HEADER_


#include "AtsPI.h"
#include "ATO/ATO.h"
#include "TASC/TASC.h"

#define LAG	200	//判定ラグ[ms]

extern bool door;	//ドア状態
extern int Signal;	//信号インデックス
extern double Accelaration;	//加減速度[km/h/s]
extern bool ATSKey[16];	//ATSkey状態

extern SpecPlus Specific;	//車両性能
extern StatePlus Status;	//車両状態
extern StatePlus Status_previous;	//車両状態(前フレーム)
extern Hand Manual;	//手動ハンドル位置
extern Hand Handle;	//ハンドル制御値


extern int ATCstatus;	//ATC状態
extern int LimitSpeed;	//制限速度
extern int MasCon_Key;	//マスコンキー
extern int lag_cnt;	//ラグ用カウンター
extern bool isLoad;	//ラグ制御伝達用

extern c_ATO ATO;	//ATO
extern c_TASC TASC;	//TASC

void reload(void);	//駅ジャンプ時再読み込み処理
void SetStatus();	//ATO/TASCスイッチ操作
void setKey(int);	//マスコンキー操作


#endif // !_HEADER_