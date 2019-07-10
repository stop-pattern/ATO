﻿#pragma once

#define DECELERATION_PATTERN 19.5	//P接近計算用減速定数
#define DECELERATION_BRAKE 20	//常用P計算用減速定数
#define DECELARATION_EMR 25	//非常P計算用減速定数
#define MAX_SPEED 120.0	//ATC最高速度[km/h]
#define DOOR_MARGIN 1	//ドア開閉可能域(停止位置目標より奥)[m]


//信号インデックス
const int SignalLimit[256] = {0,0,0,0,0,0,0,0,0,0,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,0,0,125,130,135,140,145,150,155,160,165,170,175,180,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,25,45,55,65,75,90,100,110,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


enum class ATC_Status : int {
	OFF = 0x0000,	//SW=off
	ON = 0x8000,	//SW=on

	ATC_OFF = 0x0000,
	ATC_ON = 0x0800,
	ATC_brake = 0x0400,

	ATO_OFF = 0x0000,	//SW!=ATO
	ATO_ON = 0x0080,	//SW==ATO
	ATO_control = 0x0040,	//controling
	ATO_doing = 0x0020,
	ATO_stopping = 0x0010,	//stopping & brake

	TASC_OFF = 0x0000,	//SW!=TASC
	TASC_ON = 0x0008,	//SW==TASC
	TASC_control = 0x0004,	//controling
	TASC_doing = 0x0002,	//braking
	TASC_stopping = 0x0001,	//stoppping & brake

	/*
	0b0000
	  ||||
	  ABCD

		A:ON/OFF	0x8	0b1000
		B:control	0x4	0b0100
		C:doing		0x2	0b0010
		D:parking	0x1	0b0001
	*/
};


enum class ATC_Beacon : int {
	notice_force = 7,	//前方予告（強制）
	notice_link = 31,	//前方予告（リアルタイム）
	ORP = 12,	//ORP添線
	TASC_P4 = 21,	//
	TASC_P3 = 22,	//
	TASC_P2 = 23,	//
	TASC_P1 = 24,	//
	TASC_P0 = 25,	//
	TASC_passage = 256,	//TASC停通判定
};


enum class ATC_Panel : int {
	ATC_emergency = 22,	//ATC非常
	ATC_braking,	//ATC常用
	Brake_notches = 51,	//全指令総合B段数(ATC/ATO/TASC)	切0,常用1-7,非常9
	Power_notches = 66,	//全指令総合P段数(ATC/ATO)
	Brake_notches_unic = 67,	//ゆにこんATO全指令総合B段数(ATC/ATO/TASC)
	TASC_SW = 73,	//TASC切替スイッチ	切<=>ATO/TASC
	Master_Controller_Key = 92,	//マスコンキー
	ATC_limit = 100,	//ATC現示
	ATC_notice = 133,	//ATC前方予告
	ORP_speed = 135,	//ORP
	TASC_power = 136,	//TASC灯
	TASC_release,	//TASC解放灯
	TASC_braking,	//TASC制御灯
	TASC_controling,	//TASCブレーキ灯
	TASC_noches,	//TASC制動ノッチ
	TASC_failed,	//TASC故障
	TASC_power_M,	//TASC灯	マスコンキー西武のみ
	TASC_controling_M,	//TASC制御灯	マスコンキー西武のみ
	ATO_P,	//ATO動作P段数
	ATO_B,	//ATO動作B段数
	ATO_power,	//ATO電源灯
	ATO_controling,	//ATO動作
	TASC_debug,	//TASCパターン指針
	ATO_debug,	//ATOパターン指針
	Reservation,	//予約領域

	TIS_send = 194,
	TIS_recieve_VVVF_0,
	TIS_recieve_VVVF_1,
	TIS_recieve_VVVF_2,
	TIS_recieve_VVVF_3,
	TIS_recieve_VVVF_4,
	TIS_recieve_VVVF_5,
	
	TIS_recieve_brake_0 = 215,
	TIS_recieve_brake_1,
	TIS_recieve_brake_2,
	TIS_recieve_brake_3,
	TIS_recieve_brake_4,
	TIS_recieve_brake_5,
	TIS_recieve_brake_6,
	TIS_recieve_brake_7,
	TIS_recieve_brake_8,
	TIS_recieve_brake_9,
	TIS_unit_0,
	TIS_unit_1,
	TIS_unit_2,
	TIS_unit_3,
	TIS_unit_4,
	TIS_unit_5,
};


enum class ATC_Sound : int {
};


enum class ATC_Signal : int {
	ATC_02 = 9,
	ATC_01,
	ATC_05,
	ATC_10,
	ATC_15,
	ATC_20,
	ATC_25,
	ATC_30,
	ATC_35,
	ATC_40,
	ATC_45,
	ATC_50,
	ATC_55,
	ATC_60,
	ATC_65,
	ATC_70,
	ATC_75,
	ATC_80,
	ATC_85,
	ATC_90,
	ATC_95,
	ATC_100,
	ATC_105,
	ATC_110,
	ATC_115,
	ATC_120,
	ATC_ORP = 35,

};


enum class Key : int {
KeyOff = 0,	//off
TRTA = 1,	//TRTA(S)
TOB = 2,	//東武(T)
TKK = 3,	//東急(K) / 横高(Y)
SEB = 4,	//西武(M)
SOT = 5,	//相鉄(？)
JNR = 6,	//JNR(K) / 伊豆急(？)
OER = 7,	//小田急(E)
TOY = 8,	//東葉(？)
};

