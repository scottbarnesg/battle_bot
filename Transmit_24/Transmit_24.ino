#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 transmitter(7, 8); // CE, CSN

const byte address[6] = "00001";
const char *msg = "a";
int inpt;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  transmitter.begin();
  transmitter.openWritingPipe(address);
  transmitter.setPALevel(RF24_PA_MIN);
  transmitter.stopListening();
}
void loop() {
  if(Serial.available() > 0){
    inpt = Serial.read();
    char t = (char)inpt;
    msg = &t;
    transmitter.write(&t, sizeof(t));    
  }
}
