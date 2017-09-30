/* File              : POST_with_data.ino
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#include <SoftwareSerial.h>
#include "SIM5360.h"
#include "SIM5360_GENERAL.h"
#include "SIM5360_INTERNET.h"
#include "SIM5360_HTTP.h"

SIM5360 sim(new SoftwareSerial(10, 8));
SIM5360_GENERAL gen(&sim);
SIM5360_INTERNET net(&sim);
SIM5360_HTTP http(&sim);

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  // Power ON
  Serial.println("Power on module");
  gen.power_on(true); // wait module ready

  Serial.println("Start internet");
  net.AutoAPN("true");
  if (!net.start()) {
    Serial.println("Internet can't open!");
    while (1) ;
  }
  Serial.println("Internet opened.");

  SIM5360_HTTP http(&sim);
  if (http.POST("http://httpbin.org/post", "AA=A1&BB=B2&CC=C3")) {
    Serial.println("Http code: " + String(http.http_code()));
    /* for (int i = 0; i < http.header(); i++) {
      Serial.println(http.headerName(i) + ":" + http.headerVaule(i));
    } */
    Serial.println("--------------------------");
    Serial.println(http.content());
    Serial.println("--------------------------");
  } else {
    Serial.println("Error: " + sim.getError());
  }
}

void loop() {

}
