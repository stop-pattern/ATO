// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
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
	Specific.A = s.A;
	Specific.B = s.B;
	Specific.C = s.C;
	Specific.E = s.B + 1;
	Specific.J = s.J;
	Specific.P = s.P;
}
DE void SC Initialize(int b) {
}
DE Hand SC Elapse(State S, int* p, int* s) {
	Status_previous = Status;
	Status = S;
	Status.A = (Status.V - Status_previous.V) / (Status.Z - Status_previous.Z);

	//todo : add code here

	// ----- example -----
	//* 
	Handle = Manual;
	if (!door) {
		Manual.P = 0;	//ドアが開いていたら力行禁止
	}
	//*/

	return Handle;
}
DE void SC SetPower(int p) {
	Manual.P = p;
}
DE void SC SetBrake(int b) {
	Manual.B = b;
}
DE void SC SetReverser(int r) {
	Manual.R = r;
}
DE void SC DoorOpen() {
	door = true;
}
DE void SC DoorClose() {
	door = false;
}


DE void SC KeyDown(int k) {
	ATSKey[k] = true;
}
DE void SC KeyUp(int k) {
	ATSKey[k] = false;
}
DE void SC HornBlow(int k) {
}
DE void SC SetSignal(int a) {
	Signal = a;
}
DE void SC SetBeaconData(Beacon b) {
}