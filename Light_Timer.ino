#include <RCSwitch.h>
#include <IRremote.h>
#include "RTClib.h"

RTC_DS3231 rtc;

RCSwitch mySwitch = RCSwitch();
IRrecv irrecv(8);
decode_results results;
int ovrride = 0;
unsigned long previousMillis = 0; 
unsigned long previousMillis_rd = 0; 
const long interval_poll = 59000;
const long interval_rd = 10800000;
int rd_minute = random(0,59);

void setup() {

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  mySwitch.enableTransmit(10);
    
}

void loop() {

  if (irrecv.decode(&results)) {
    if (results.value == 0x800F8429) {
          mySwitch.switchOn("10000", "01000");
          Serial.print("An");
          ovrride = 1;
          irrecv.resume(); // Receive the next value
        }
        else if (results.value == 0x800F042A)
        {
          mySwitch.switchOff("10000", "01000");
          Serial.print("Aus");
          ovrride = 0;
          irrecv.resume(); // Receive the next value
        }
        else
        irrecv.resume();
  }

 unsigned long currentMillis = millis();
 unsigned long currentMillis_rd = millis();

  if (currentMillis - previousMillis >= interval_poll) {
   
    previousMillis = currentMillis;
    if(!ovrride) {
      void Zeitintervall();
    } 
  }
  
  if (currentMillis_rd - previousMillis_rd >= interval_rd) {
   
    previousMillis_rd = currentMillis_rd;
    
    DateTime now = rtc.now(); //Wechsel random Minute
    if(now.hour() != 18 && now.hour() != 22 && now.hour() != 6 && now.hour() != 8) {
      rd_minute = random(0,59);
    }
   } 
  } 
  
void Zeitintervall() {
       
  DateTime now = rtc.now();
  
    if ( now.hour() == 18 && now.minute() == rd_minute) {
      mySwitch.switchOn("10000", "01000");
    } 
    if ( now.hour() == 22 && now.minute() == rd_minute) {   
      mySwitch.switchOff("10000", "01000");
    }
    if ( now.hour() == 6 && now.minute() == rd_minute) {
      mySwitch.switchOn("10000", "01000");
    }
    if ( now.hour() == 8 && now.minute() == rd_minute) {   
      mySwitch.switchOff("10000", "01000");
    }       
}  


