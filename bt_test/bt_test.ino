#include "SoftwareSerial.h"

#define BUFFER_SIZE 8
#define RXPIN 2
#define TXPIN 3

SoftwareSerial serialConnection(RXPIN, TXPIN);

char inChar=-1;
bool autonomous = true;

void setup(){
  Serial.begin(9600);//Initialize communications to the serial monitor in the Arduino IDE
  serialConnection.begin(9600);//Initialize communications with the bluetooth module
}
void loop(){
  checkBluetooth();
  serialConnection.print("a");
}

void checkBluetooth(){
  if(serialConnection.available() > 0){
    inChar = serialConnection.read();//Read one byte
    Serial.println(inChar);
  }
}
