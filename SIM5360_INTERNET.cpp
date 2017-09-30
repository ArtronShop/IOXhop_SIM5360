/* File              : SIM5360_INTERNET.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_INTERNET_CPP__
#define SIM5360_INTERNET_CPP__

#include "SIM5360_INTERNET.h"

bool SIM5360_INTERNET::AutoAPN(String Operator) {
  _APN_NAME = "internet";
  _APN_USERNAME = "";
  _APN_PASSWORD = "";

  Operator.toLowerCase();
  if (Operator == "ais" || Operator == "tot" || Operator == "mybycat") {
    // Use default
  } else if (Operator == "dtac") {
    _APN_NAME = "www.dtac.co.th"; // APN
  } else if (Operator == "true") {
    _APN_USERNAME = "true"; // Username
    _APN_PASSWORD = "true"; // Password
  } else {
    return false;
  }
  
  return true;
}

void SIM5360_INTERNET::SetAPN(String APN, String Username, String Password) {
  _APN_NAME = APN;
  _APN_USERNAME = Username;
  _APN_PASSWORD = Password;
}

bool SIM5360_INTERNET::start() {
  if (!MainObj->SendCMD("AT+CGSOCKCONT=1,\"IP\",\"" + _APN_NAME + "\"")) return false;
  MainObj->SendCMD("AT+CGAUTH=1,1,\"" + _APN_USERNAME + "\",\"" + _APN_PASSWORD + "\"");
  MainObj->SendCMD("AT+CGREG=1");
  return MainObj->findOK(5000);
}

bool SIM5360_INTERNET::stop() {
  if (!MainObj->SendCMD("AT+CGREG=0")) return false;
  return MainObj->findOK();
}

#endif
