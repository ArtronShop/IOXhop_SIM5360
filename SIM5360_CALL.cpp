/* File              : SIM5360_CALL.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_CALL_CPP__
#define SIM5360_CALL_CPP__

#include "SIM5360_CALL.h"

bool SIM5360_CALL::call(String phone) {
	MainObj->SendCMD("ATD" + phone + ";");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "call fail";
		return false;
	}
	return true;
}

bool SIM5360_CALL::answer() {
	MainObj->SendCMD("ATA");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "answer the phone fail";
		return false;
	}
	return true;
}

bool SIM5360_CALL::hangUp() {
	MainObj->SendCMD("AT+CVHU=0");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "set mode fail";
		return false;
	}
	
	MainObj->SendCMD("ATH");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "set hang up fail";
		return false;
	}
	
	return true;
}

#endif