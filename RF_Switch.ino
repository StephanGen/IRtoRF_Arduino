#include <RCSwitch.h>
#include <IRremote.h>

RCSwitch mySwitch = RCSwitch();
IRrecv irrecv(8);
decode_results results;


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
          irrecv.resume(); // Receive the next value
        }
        else if (results.value == 0x800F042A)
        {
          mySwitch.switchOff("10000", "01000");
          Serial.print("Aus");
          irrecv.resume(); // Receive the next value
        }
        else
        irrecv.resume();
  }
}
