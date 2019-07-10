#include "../pch/pch.h"
#include "../header/define.h"
#include "../Header.h"
#include "ATO.h"

#define ATO_LAG 500	//ÉâÉO[ms]


void c_ATO::Control(State S, int * panel, int * sound) {
	//ì]ìÆñhé~
	if (ATCstatus & static_cast<int>(ATC_Status::ATO_stopping)) {
		if (Manual.B > control.B) {
			ATCstatus &= ~static_cast<int>(ATC_Status::ATO_stopping);
		}
		else {
			this->control.P = 0;
			this->control.B = Specific.E / 2;
		}
	}

	//î≠é‘îªíË
	if (!(ATCstatus & static_cast<int>(ATC_Status::ATO_control))) {
		if (this->Departure()) {
			ATCstatus |= static_cast<int>(ATC_Status::ATO_control);
		}
	}

	//ATOêßå‰
	if (ATCstatus & static_cast<int>(ATC_Status::ATO_control)) {
		//íËë¨îªíË
		if (this->Limit > Status.V && LimitSpeed * 0.9 < Status.V) {
			this->CSCcnt = S.T;
		}
		else {
			if (S.T - this->CSCcnt > ATO_CSC_TIME) {
				this->isCSC = true;
				this->CSCspeed = int(Status.V);
			}
		}

		//å∏ë¨êßå‰
		if (this->Limit + this->margin < Status.V) {
			this->isCSC = false;
			if (this->control.B < Specific.B) {
				if (rand() % 2) {
					this->control.P = 0;
					this->control.B++;
				}
			}
		}
		//â¡ë¨êßå‰
		else if (this->Limit > Status.V) {
			this->isCSC = false;
			if (this->control.P < Specific.P) {
				if (rand() % 2) {
					this->control.P++;
					this->control.B = 0;
				}
			}
		}
		//ëƒçsêßå‰
		else {
			if (this->isCSC) {	//ATOíËë¨
				this->CSC();
			}
			this->control.P = 0;
			this->control.B = 0;
			//isCSC = true;
		}

		//éñëOå∏ë¨
		if (this->isFD) {
			if (this->Location > S.Z || this->TargetSpeed < Status.V) {
				this->Distance = this->Location - Status.Z;
				double lim = sqrt(this->Distance * DECELERATION_BRAKE) * 10;	//FDâ∫ç~P
				if (isnan(lim)) lim = MAX_SPEED;
				if (lim < this->Limit) {
					this->Limit = lim;
				}
			}
			else isFD = false;
		}
	}

	/*
	if (abs(accelaration) > 10) {
		handle.B = Specific.E;	//
	}
	*/
}


void c_ATO::CSC() {
	if (Accelaration > 0.5) {
		this->control.B += 1;
		this->control.P = 0;
	}
	else if (Accelaration < -0.5) {
		this->control.B = 0;
		this->control.P += 1;
	}
	else {
		//íËë¨à€éù
	}

	//îÕàÕäOîªíË
	if (this->control.B < 0) {
		this->control.B = 0;
	}
	if (this->control.P < 0) {
		this->control.P = 0;
	}
}


bool c_ATO::Departure() {
	if (ATSKey[ATSKeys::A1] == true && (ATSKey[ATSKeys::A2] == true || ATSKey[ATSKeys::B1] == true)) {
		if (door == false && Status.V == 0 && Manual.B == 0 && Manual.P == 0 && Manual.R == 1 && LimitSpeed >= 25) {
			this->control.P = 0;
			this->control.B = 0;
			return true;
		}
	}
	return false;
}

void c_ATO::SignalChange() {
	this->Limit = this->Reference_Speed[this->Mode][Signal];
	this->margin = int((LimitSpeed - this->Limit) * 10) % 10 > 5 ? int(LimitSpeed - this->Limit) : int(LimitSpeed - this->Limit) + 1;
	this->isFD = false;
}


void c_ATO::ChangeMode(int in) {
	if (Status.V == 0 && Manual.B > 0 && Manual.P == 0) {
		if (this->Mode > 0 && this->Mode < 3) {
			this->Mode += in;
			this->SignalChange();
		}
		else if (this->Mode >= 3) {
			this->Mode = 3;
		}
		else {
			this->Mode = 1;
		}
	}

}

void c_ATO::setPattern(Beacon b) {
	brake = b;
}

void c_ATO::inEmergency(void) {
	ATCstatus &= ~static_cast<int>(ATC_Status::ATO_control);
	ATCstatus &= ~static_cast<int>(ATC_Status::ATO_doing);
	ATCstatus &= ~static_cast<int>(ATC_Status::ATO_stopping);
	this->control.P = 0;
	this->control.B = 0;
	this->isCSC = false;
}

void c_ATO::Forward_Deceleration(int sig, int dist) {
	if (this->isFD == false || (this->isFD == true && this->TargetSpeed)) {
	}
	this->TargetSpeed = this->Reference_Speed[this->Mode][sig];
	if (this->TargetSpeed < LimitSpeed) {
		this->Location = Status.Z + dist;
		this->isFD = true;
	}
}
