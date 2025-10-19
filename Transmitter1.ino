
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins (pin 7 and 8)
const byte address[6] = "00001";


int potpins[4] = {A0, A1, A2, A3};

int potValue[4] = {0, 0, 0, 0};
int Anglevalue[4]={0, 0, 0, 0};


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  
}

void loop() {
  potValue[0]=analogRead(potpins[0]);
  Anglevalue[0]=map(potValue[0], 0, 1023, 0, 30);
  

  potValue[2]=analogRead(potpins[2]);
  Anglevalue[2]=map(potValue[2], 0, 1023, 0, 30);
  


  potValue[1]=analogRead(potpins[1]);
  Anglevalue[1]=map(potValue[1], 550, 1023, 0, 180);
  
  
  potValue[3]=analogRead(potpins[3]);
  Anglevalue[3]=map(potValue[3], 0, 1023, 0, 30);
  

  radio.write(&Anglevalue, sizeof(Anglevalue));
  for(int i=0;i<4;i++)
   {
     Serial.println(Anglevalue[i]);
   }
  
  
 
}
