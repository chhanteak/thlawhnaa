#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

#define ESC_PIN 2
Servo esc;


RF24 radio(7, 8); // CE, CSN pins (pin 7 and 8)
const byte address[6] = "00001";
Servo servos[4];
int servoPins[4] = {3, 5, 6, 9};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  radio.setPALevel(RF24_PA_MIN);
  esc.attach(ESC_PIN, 1000, 2000);
    for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
  }
  
}

void loop() {
  
  int Anglevalue[4];
  int servoPos[4];

  if (radio.available()) {
    radio.read(&Anglevalue, sizeof(Anglevalue));

    int speed = map(Anglevalue[1], 0, 180, 0, 180);
    esc.write(speed);
    Serial.println(speed);

    servoPos[0]=map(Anglevalue[0], 0, 30, 0, 60);
    servos[0].write(servoPos[0]);
    Serial.println(servoPos[0]);

    

    servoPos[1]=map(Anglevalue[2], 30, 0, 70, 0);
    servos[1].write(servoPos[1]);
    Serial.println(servoPos[1]);
    servoPos[2]=map(Anglevalue[2], 0, 30, 0, 70);
    servos[2].write(servoPos[2]);
    Serial.println(servoPos[2]);

    servoPos[3]=map(Anglevalue[3], 0, 30, 0, 60);
    servos[3].write(servoPos[3]);
    Serial.println(servoPos[3]);
    
    

  }
  
}
  
