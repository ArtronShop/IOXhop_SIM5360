/* File              : SIM5360_SMS.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_SMS_CPP__
#define SIM5360_SMS_CPP__

#include "SIM5360_SMS.h"

bool SIM5360_SMS::begin() {
	MainObj->SendCMD("AT+CMGF=1");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "Send AT+CMGF=1 error";
		return -1;
	}
	_isBegin = true;
	return true;
}

bool SIM5360_SMS::send(String phone_number, String msg) {
	if (!_isBegin) {
		MainObj->_error_msg = "Not begin";
		return -1;
	}

	MainObj->SendCMD("AT+CMGS=\"" + phone_number + "\"");
	MainObj->SendCMD(msg, false);
	MainObj->GSMSerial->write(CTRL_Z);
	String ros = MainObj->readString(0, 5000, "\r\nOK\r\n");

	return ros.indexOf("+CMGS") >= 0;
}

int SIM5360_SMS::length() {
	if (!_isBegin) {
		MainObj->_error_msg = "Not begin";
		return -1;
	}
	
	MainObj->SendCMD("AT+CNMI=2,1");
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "Send AT+CNMI=2,1 error";
		return -1;
	}
	
	MainObj->SendCMD("AT+CPMS=\"SM\"");
	String ros = MainObj->readString(0, 3000, "+CPMS: ");
	if (ros.indexOf("+CPMS: ") < 0) {
		MainObj->_error_msg = "read sms index count error";
		return -1;
	}
	String countWithEnd = MainObj->readString(0, 500, ",");
	return countWithEnd.substring(0, countWithEnd.length() - 1).toInt();
}

bool SIM5360_SMS::read(int index) {
	_from = _date = _msg = "";
	
	if (!_isBegin) {
		MainObj->_error_msg = "Not begin";
		return -1;
	}

	if (!MainObj->SendCMD("AT+CMGR=" + String(index), 1000)) {
		MainObj->_error_msg = "Send AT+CMGR=" + String(index) + " error. :: " + MainObj->readString(0, 500);
		return false;
	}
	
	String ros = MainObj->readString(0, 3000, "+CMGR: \"");
	if (ros.indexOf("+CMGR: ") < 0) {
		MainObj->_error_msg = "not respond message";
		return false;
	}
	
	MainObj->readString(0, 100, "\","); // remove first parameter
	_from = MainObj->readString(0, 100, ",");
	_from = _from.substring(1, _from.length() - 2);
	MainObj->readString(0, 100, "\","); // remove third parameter
	_date = MainObj->readString(0, 100, "\r\n");
	_date = _date.substring(1, _date.length() - 3);
	_msg = MainObj->readString(0, 100, "\r\nOK\r\n");
	_msg = _msg.substring(0, _msg.length() - 8);
	
	/*char bufPhone[15], bufDate[22], bufMsg[255];
	sscanf(ros.c_str(), "+CMGR: \"REC READ\",\"%[^\"]\",\"\",\"%[^\"]\"\r\n%s", &bufPhone, &bufDate, &bufMsg);
	_from = bufPhone;
	_date = bufDate;
	_msg = bufMsg;*/
	return true;
}

bool SIM5360_SMS::remove(int index) {
	if (!_isBegin) {
		MainObj->_error_msg = "Not begin";
		return false;
	}
	
	MainObj->SendCMD("AT+CMGD=" + String(index));
	if (!MainObj->findOK()) {
		MainObj->_error_msg = "delete fail, module not respond OK";
		return false;
	}
	
	return true;
}

#endif