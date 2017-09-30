/* File              : IMEI.ino
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#include <SoftwareSerial.h>
#include "SIM5360.h"
#include "SIM5360_GENERAL.h"

SIM5360 sim(new SoftwareSerial(7, 8));
SIM5360_GENERAL gen(&sim);

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  // Power ON
  Serial.println("Power on module");
  gen.power_on(true); // wait module ready
  
  Serial.println("IMEI: " + gen.imei());

  // Power OFF
  Serial.println("Power off module");
  gen.power_off();
}

void loop() {
  
}
