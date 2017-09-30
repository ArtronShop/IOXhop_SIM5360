/* File              : Answer_the_phone.ino
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#include <SoftwareSerial.h>
#include "SIM5360.h"
#include "SIM5360_GENERAL.h"
#include "SIM5360_CALL.h"

SIM5360 sim(new SoftwareSerial(7, 8));
SIM5360_GENERAL gen(&sim);
SIM5360_CALL call(&sim);

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  // Power ON
  Serial.println("Power on module");
  gen.power_on(true); // wait module ready

  Serial.println("Waiting for a call");
}

void loop() {
  if (sim.readString(0, 100).indexOf("RING") >= 0) {
    call.answer();
    Serial.println("Answer the phone");
    delay(10000);
    call.hangUp();
    Serial.println("End call");
  }
}
