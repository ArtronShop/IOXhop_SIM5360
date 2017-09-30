/* File              : SIM5360.h
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_H__
#define SIM5360_H__

#include "Arduino.h"
#include <SoftwareSerial.h>

static int timeOut = 500;
#define CTRL_Z 0x1A

class SIM5360 {
  public:
	SIM5360() { }
    SIM5360(SoftwareSerial* obj) : GSMSerial(obj) { }

    void begin(int speed) ;
    bool SendCMD(String cmd, bool newLine = true, int timeout = 0) ;
    String readString(int len = 0, int timeout = 0, String find = "") ;
    bool findOK(int timeout = 1000) ;
    void clsBuffer() ;
	String getError() ;
	
	SoftwareSerial* GSMSerial;
	String _error_msg = "";

}
;

#endif
