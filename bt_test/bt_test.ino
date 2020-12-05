#include "SoftwareSerial.h"

#define BUFFER_SIZE 8
#define RXPIN 2
#define TXPIN 3

//Maximum size of char array that is sent
//This is the maximum size of an array I
//can make without a compiler error (2^15 -1)
//#define TEST_SIZE 30000
#define TEST_SIZE 300

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
  char message [TEST_SIZE];
  if(serialConnection.available() > 0){
      inChar = serialConnection.read();//Read one byte
      if(inChar == 's'){
        bt_test(message);
      }
    }
}

void bt_test(char * message){
  unsigned int i;
  char size_message[6];
  char temp;

  //Fills the array
  for(i = 0; i < TEST_SIZE; i++){
    if(i%2 == 0){
        message[i] = '0';
      }
      else{
        message[i] = '1';
      }
  }

  //Sends message of increasing size
  //places null character at end
  for(i = 1; i < TEST_SIZE; i++){
    //set the null character for size
    temp = message[i];
    message[i] = '\0';

    serialConnection.print(message);
    serialConnection.print('x');

    message[i] = temp;
  }
  serialConnection.print('d');
}
