#define ENA 8
#define ENB 12
#define L_forward 9
#define L_reverse 10
#define R_reverse 11
#define R_forward 6

int inpt;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(L_forward, OUTPUT);
  pinMode(R_forward, OUTPUT);
  pinMode(L_reverse, OUTPUT);
  pinMode(R_reverse, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(13,LOW);

  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) // Non-blocking
  {
    digitalWrite(13,HIGH);
    inpt = Serial.read();
    switch(inpt) // switch between WASD in ASCII
    {
      case 119: // w
        Serial.println("forward");
        digitalWrite(L_forward, HIGH);
        digitalWrite(R_forward, HIGH);
        delay(100);
        digitalWrite(L_forward,LOW);
        digitalWrite(R_forward, LOW);
        break;
      case 97: //a
        Serial.println("left");
        digitalWrite(L_reverse,HIGH);
        digitalWrite(R_forward,HIGH);
        delay(100);
        digitalWrite(L_reverse,LOW);
        digitalWrite(R_forward,LOW);
        break;
      case 115: //s
        Serial.println("reverse");
        digitalWrite(L_reverse,HIGH);
        digitalWrite(R_reverse,HIGH);
        delay(250);
        digitalWrite(L_reverse,LOW);
        digitalWrite(R_reverse,LOW);
        break;
      case 100: //d
        Serial.println("right");
        digitalWrite(L_forward,HIGH);
        digitalWrite(R_reverse,HIGH);
        delay(100);
        digitalWrite(L_forward,LOW);
        digitalWrite(R_reverse,LOW);
        break;
    }
  }
  digitalWrite(13,LOW);
   
}
