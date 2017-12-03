#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK receiver;
uint8_t buf[10];
uint8_t buflen = sizeof(buf);

void setup()
{
    Serial.begin(9600);
    if (!receiver.init())
         Serial.println("Failed to Initialive Reciever");
    else{
      Serial.println("Receiver Successfully Initialized");
    }
    
}

void loop()
{
    if (receiver.recv(buf, &buflen))
    {
      Serial.println((char*)buf);
      Serial.println((int)*buf);
    }
}
