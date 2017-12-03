#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK transmitter;
const char *msg = "a";
int inpt;

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!transmitter.init()){
         Serial.println("init failed");
    }
    else{
      Serial.println("Successfully Initialized");
    }
}

void loop()
{
  if(Serial.available() > 0) // >0 New. Remove if Issues Occur
  {
    inpt = Serial.read();
    char t = (char)inpt;
    msg = &t;
    transmitter.send((uint8_t*)msg, strlen(msg));
    transmitter.waitPacketSent();
  }
}
