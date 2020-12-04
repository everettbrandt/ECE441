#include "SoftwareSerial.h"

#define BUFFER_SIZE 8
#define RXPIN 2
#define TXPIN 3

SoftwareSerial serialConnection(RXPIN, TXPIN);

char inChar=-1;
bool autonomous = true;
bool start = false;
unsigned int message_size = 0;

void setup(){
  Serial.begin(9600);//Initialize communications to the serial monitor in the Arduino IDE
  serialConnection.begin(9600);//Initialize communications with the bluetooth module
}

void loop(){
  if(start == true){
    bt_write();
    if(message_size > 15){
      message_size = 0;
      start = false;
    }
    //Serial.println("Started");
    //serialConnection.print("hello world");
  }
  else{
    if(serialConnection.available() > 0){
      inChar = serialConnection.read();//Read one byte
      if(inChar == ' '){
        start = true;
      }
    }
  }
}

void bt_write(){
  message_size += 1;
  char message [message_size];
  for(unsigned int i = 0; i < message_size; i++){
    if(i%2 == 0){
      message[i] = '0';
    }
    else{
      message[i] = '1';
    }
  }
  message[message_size] = '\0';
  serialConnection.print(message_size);
  Serial.print(message_size);
  Serial.println(message);
}
