#include "AtsPI.h"
#include "Header.h"

bool door;	//ドア状態
int Signal;	//信号インデックス
double Accelaration;	//加減速度[km/h/s]
bool ATSKey[16];	//ATSkey状態

SpecPlus Specific;	//車両性能
State Status;	//車両状態
State Status_previous;	//車両状態(前フレーム)
Hand Manual;	//手動ハンドル位置
Hand Handle;	//ハンドル制御値


int ATCstatus;	//ATC状態
int LimitSpeed;	//制限速度
int MasCon_Key;	//マスコンキー

c_ATO ATO;	//ATO
c_TASC TASC;	//TASC