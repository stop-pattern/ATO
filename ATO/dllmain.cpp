// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include <Windows.h>
#include <math.h>
#include "AtsPI.h"
#include "header/define.h"
#include "Header.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



DE void SC Load() {
}
DE void SC Dispose() {
}
DE int SC GetPluginVersion() {
	return PI_VERSION;
}
DE void SC SetVehicleSpec(Spec s) {
	Specific.B = s.B;
	Specific.P = s.P;
	Specific.A = s.A;
	Specific.J = s.J;
	Specific.C = s.C;
	Specific.E = s.B + 1;
}
DE void SC Initialize(int b) {
	b = InitialPosition::Service;
	reload();
}
DE Hand SC Elapse(State S, int* panel, int* sound) {

	// ----- initialize -----
	//Status
	Status_previous = Status;
	Status.Z = S.Z;
	Status.V = S.V;
	Status.T = S.T;
	Status.BC = S.BC;
	Status.MR = S.MR;
	Status.ER = S.ER;
	Status.BP = S.BP;
	Status.SAP = S.SAP;
	Status.I = S.I;
	Status.A = (Status.V - Status_previous.V) / (Status.Z - Status_previous.Z);
	//Handle
	Handle = Manual;


	// key
	if (MasCon_Key != panel[static_cast<int>(ATC_Panel::Master_Controller_Key)]) {
		setKey(panel[static_cast<int>(ATC_Panel::Master_Controller_Key)]);
	}


	if (MasCon_Key != static_cast<int>(Key::KeyOff)) {
		if (S.T - lag_cnt >= LAG) {
			isLoad = true;
			lag_cnt = S.T;
		}
		else isLoad = false;
	}


	//ATO
	if (ATCstatus & static_cast<int>(ATC_Status::ATO_ON)) {
		panel[static_cast<int>(ATC_Panel::ATO_power)] = true;

		if (isLoad) {
			ATO.Control(S, panel, sound);	//制御関数
		}

		//ATO動作
		if (ATCstatus & static_cast<int>(ATC_Status::ATO_control)) {

			if (Manual.B == 0 && Manual.P == 0) {
				Handle.P = ATO.control.P;
				panel[static_cast<int>(ATC_Panel::ATO_P)] = ATO.control.P + 1;
				panel[static_cast<int>(ATC_Panel::ATO_controling)] = true;
			}
			else {
				ATO.control.P = 0;
				panel[static_cast<int>(ATC_Panel::ATO_P)] = 0;
			}

			if (Manual.P == 0 && Manual.B < ATO.control.B) {
				Handle.B = ATO.control.B;
				panel[static_cast<int>(ATC_Panel::ATO_B)] = ATO.control.B + 1;
			}
			else {
				panel[static_cast<int>(ATC_Panel::ATO_B)] = 0;
			}
		}
	}
	else {
		panel[static_cast<int>(ATC_Panel::Brake_notches)] = Manual.B;
		panel[static_cast<int>(ATC_Panel::ATO_P)] = 0;
		panel[static_cast<int>(ATC_Panel::ATO_B)] = 0;
		panel[static_cast<int>(ATC_Panel::ATO_power)] = false;
		panel[static_cast<int>(ATC_Panel::ATO_controling)] = false;
	}
	panel[static_cast<int>(ATC_Panel::ATO_debug)] = int(ATO.Limit);


	//TASC
	if (ATCstatus & static_cast<int>(ATC_Status::TASC_ON)) {
		if (isLoad) {
			TASC.Control(S, panel, sound);	//制御関数
		}

		panel[static_cast<int>(ATC_Panel::TASC_release)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_braking)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_noches)] = 0;
		panel[static_cast<int>(ATC_Panel::TASC_failed)] = false;
		MasCon_Key == static_cast<int>(Key::SEB) ? panel[static_cast<int>(ATC_Panel::TASC_power_M)] = true : panel[static_cast<int>(ATC_Panel::TASC_power)] = true;

		if (ATCstatus & static_cast<int>(ATC_Status::TASC_control)) {
			MasCon_Key == static_cast<int>(Key::SEB) ? panel[static_cast<int>(ATC_Panel::TASC_controling_M)] = true : panel[static_cast<int>(ATC_Panel::TASC_controling)] = false;

			//TASC制御灯
			if (TASC.isControl) panel[static_cast<int>(ATC_Panel::TASC_braking)] = true;
			else panel[static_cast<int>(ATC_Panel::TASC_braking)] = false;

			//TASC動作
			if (true && ATCstatus & static_cast<int>(ATC_Status::TASC_doing)) {
				if (TASC.control.B > Handle.B) {
					Handle.P = 0;
					Handle.B = TASC.control.B;
					panel[static_cast<int>(ATC_Panel::TASC_noches)] = TASC.control.B + 1;
				}
			}
		}
	}
	else {
		panel[static_cast<int>(ATC_Panel::TASC_power)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_release)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_braking)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_controling)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_noches)] = 0;
		panel[static_cast<int>(ATC_Panel::TASC_failed)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_power_M)] = false;
		panel[static_cast<int>(ATC_Panel::TASC_controling_M)] = false;
	}
	panel[static_cast<int>(ATC_Panel::TASC_debug)] = int(TASC.Limit);


	//TISunit
	if (S.I > 0) {	//電流+
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_0)] = 1;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_1)] = 1;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_2)] = 1;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_3)] = 1;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_4)] = 1;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_5)] = 1;
	}
	else if (S.I < 0) {	//電流-
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_0)] = 2;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_1)] = 2;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_2)] = 2;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_3)] = 2;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_4)] = 2;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_5)] = 2;
	}
	else {	//電流0
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_0)] = 0;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_1)] = 0;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_2)] = 0;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_3)] = 0;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_4)] = 0;
		if (rand() % 10 == 0) panel[static_cast<int>(ATC_Panel::TIS_unit_5)] = 0;
	}

	//panel
	panel[static_cast<int>(ATC_Panel::Brake_notches)] = Handle.B == Specific.E ? Handle.B + 1 : Handle.B;
	panel[static_cast<int>(ATC_Panel::Brake_notches_unic)] = Handle.B == Specific.E ? Handle.B + 1 : Handle.B;
	panel[static_cast<int>(ATC_Panel::Power_notches)] = Handle.P;

	return Handle;
}
DE void SC SetPower(int p) {
	Manual.P = p;
}
DE void SC SetBrake(int b) {
	Manual.B = b;
	if (b == Specific.E) {
		ATO.inEmergency();
		TASC.inEmergency();
	}
}
DE void SC SetReverser(int r) {
	Manual.R = r;
}
DE void SC DoorOpen() {
	door = true;
	if (ATCstatus & static_cast<int>(ATC_Status::ATC_ON)) {
		ATO.SignalChange();
	}
	if (ATCstatus & static_cast<int>(ATC_Status::ATO_ON)) {
		ATCstatus &= ~static_cast<int>(ATC_Status::ATO_control);
		ATCstatus &= ~static_cast<int>(ATC_Status::ATO_doing);
		ATCstatus |= static_cast<int>(ATC_Status::ATO_stopping);
	}
	if (ATCstatus & static_cast<int>(ATC_Status::TASC_ON)) {
		ATCstatus &= ~static_cast<int>(ATC_Status::TASC_control);
		ATCstatus &= ~static_cast<int>(ATC_Status::TASC_doing);
		ATCstatus |= static_cast<int>(ATC_Status::TASC_stopping);
		TASC.setStatus(false);	//TASC制御解放
	}
}
DE void SC DoorClose() {
	door = false;
}


DE void SC KeyDown(int k) {
	ATSKey[k] = true;
	switch (k) {
	case ATSKeys::E:
		ATO.ChangeMode(-1);
		break;
	case ATSKeys::F:
		ATO.ChangeMode(+1);
		break;
	case ATSKeys::G:
		if (ATSKey[ATSKeys::S]) {
			ATCstatus &= ~static_cast<int>(ATC_Status::ON);
			SetStatus();
		}
		break;
	case ATSKeys::H:
		if (ATSKey[ATSKeys::S]) {
			ATCstatus |= static_cast<int>(ATC_Status::ON);
			SetStatus();
		}
		break;
	default:
		break;
	}
}
DE void SC KeyUp(int k) {
	ATSKey[k] = false;
}
DE void SC HornBlow(int k) {
}
DE void SC SetSignal(int a) {
	Signal = a;
	LimitSpeed = SignalLimit[a];

	ATO.SignalChange();
}
DE void SC SetBeaconData(Beacon b) {
	switch (b.Num) {
		case static_cast<int>(ATC_Beacon::ORP):
			break;
		case static_cast<int>(ATC_Beacon::TASC_P0):
			TASC.setBeacon(0, b);
			break;
		case static_cast<int>(ATC_Beacon::TASC_P1):
			TASC.setBeacon(1, b);
			break;
		case static_cast<int>(ATC_Beacon::TASC_P2):
			TASC.setBeacon(2, b);
			break;
		case static_cast<int>(ATC_Beacon::TASC_P3):
			TASC.setBeacon(3, b);
			break;
		case static_cast<int>(ATC_Beacon::TASC_P4):
			TASC.setBeacon(4, b);
			break;
		case static_cast<int>(ATC_Beacon::TASC_passage):
			TASC.setBeacon(-1, b);
		default:
			break;
	}
}