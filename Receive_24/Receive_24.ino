#include <nRF24L01.h>
#include <RF24.h>

RF24 receiver(7, 8); // CE, CSN

const byte address[6] = "00001";
char type[1] = "";
char cat[1] = "";
char val[1]  = "";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  receiver.begin();
  receiver.openReadingPipe(0, address);
  receiver.setPALevel(RF24_PA_MIN);
  receiver.startListening();
  Serial.println("Receiver Ready");
}
void loop() {
  for (int i = 0; i <= 2; i++) {
    if (receiver.available()) {
      switch (i) {
        case 0:
          receiver.read(&type, sizeof(type));
          break;
        case 1:
          receiver.read(&cat, sizeof(cat));
          break;
        case 2:
          receiver.read(&val, sizeof(val));
          break;
      }
    }
    else {
      i--;
    }
    if (i == 2) {
      Serial.println(val);
    }
  }
}
