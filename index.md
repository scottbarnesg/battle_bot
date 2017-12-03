# Building a Battle Bot 
## Design, Electronics, & Software

### Scott Barnes* & Chris Poole** 
*Smart Systems Laboratory  
**Flight Dynamics Laboratory  
The George Washington University  
School of Engineering & Applied Science  


## Introduction:
We present a step-by-step process for creating your own remote-controlled battle bot from scratch, covering all hardware and software used in our design. While the goal of our project was to design a battle bot, the electrical design and software we used can applied to other robotic applications. We have done our best to provide comprehensive explanations of our source code and wiring diagrams, and have included a few unit tests to help you along the way.

We'll walk you through our entire design process. However, if you'd just like to skip to the fully functioning code for the deployed system, feel free to skip to the [end](#4.0-final-implementation-(all-deployed-software)). 

All source code can be found in the project's [GitHub Repository](https://github.com/scottbarnesg/battle_bot). 

## Project Overview:
Our system consists of two major components: the controller and the robot. The controller consists of the input device (a Logitech310 USB controller), a Raspberry Pi for processing the controller inputs, and an Arduino for transmitting the signals to the robot. The robot uses a single Arduino to receive signals from the controller, interpret the signals, and sent commands to the drive motor controller and the weapon (a spinning drum). 

## 1.0: Getting it Moving:
The obvious starting point for our robot is to get it to drive around. We use a simple WASD keyboard controller, which moves the robot for a pre-set amount of time in the direction corresponding to the key pressed. This is the best way to ensure your core electronics are working correctly before we add in the RF communication

### 1.1: Electronics:
Instructions, diagrams, and more coming soon!

### 1.2: Software:
We use the [RadioHead Library](http://www.airspayce.com/mikem/arduino/RadioHead/) to communicate between the "controller" and "reciever" arduinos. Our first implementation was actually with these [433 MHz Transmitters](http://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/), which are cheap, easy to use, but highly limited (only 10-20 foot range). If you're using the 2.4 GHz transmitters we had on our final robot, you'll have to replace the receive and transmit parts of the code (we have an in-depth disucssion on transmitting with these transmitters further down). 

[Download the library](http://www.airspayce.com/mikem/arduino/RadioHead/), unzip it, and add it to your Arduino "libraries" folder. Now its ready for use.

#### Prototype Controller Code
First, import the required header files.
```
#include <RH_ASK.h>
#include <SPI.h>
```
Then we'll define our pins. These correspond to how your motors are wired to your speed controller arduino pins. 
```
#define ENA 8
#define ENB 12
#define L_forward 9
#define L_reverse 10
#define R_reverse 11
#define R_forward 6
```
Then, we create a buffer, which allows the reciever to hold more than one input at a time, enabling improved performance.
```
uint8_t buf[12];
uint8_t buflen = sizeof(buf);
int read_buffer;
```
In the setup function, we set our pins to "output" and establish a serial connection with the computer (so that we can communicate with the robot).
```
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
```
Now for the loop function. First, we check for a new input from the serial port and read those incoming values as an int, which converts the keyboard input to the corresponsing ASCII values. We then write to the pins corresponding to the input.
```
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
```


## 2.0: RF Communication Basics

### Electronics

### Software

#### 1.2.1 Transmitter

First, import the required header files
```
#include <RH_ASK.h>
#include <SPI.h>
```
Then, we name the library's driver struct to something useful (we call it transmitter). We also define a constant char (used by the driver to determine the transmittion bit length) and an int to get the keyboard input.
```
RH_ASK transmitter;
const char *msg = "a";
int inpt;
```
The setup function is pretty standard: we create a serial connection with the computer and initialize the transmitter
```
void setup()
{
    Serial.begin(9600);
    if (!transmitter.init()){
         Serial.println("Failed to Initialized");
    }
    else{
      Serial.println("Successfully Initialized");
    }
}
```
Now for the loop function. First, we check for a new input from the serial port and read those incoming values as an int. However, this library transmits a char - so we cast the input to a char (we will re-cast it on receiver end). Then, we transmit the value using the syntax defined in the library's function and wait for the packets to finish sending.
```
void loop()
{
  if(Serial.available() > 0)
  {
    inpt = Serial.read();
    char t = (char)inpt;
    msg = &t;
    transmitter.send((uint8_t*)msg, strlen(msg));
    transmitter.waitPacketSent();
  }
}
```

## 3.0: Putting it All Together

## 4.0: Final Implementation (All Deployed Software)

# Markdown Reference Material (Delete Later)

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/scottbarnesg/battle_bot/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
