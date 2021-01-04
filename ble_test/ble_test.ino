
#include <SoftwareSerial.h>
#define RXPIN 3
#define TXPIN 2

SoftwareSerial btSerial(RXPIN, TXPIN);

/* There is data waiting to be read from the HM-10 device. */
static void HandleRxDataIndication(void)
{
  char c = btSerial.read();
  
  /* Just echo the character for now. */
  Serial.write(c);
}

/* There is data waiting to be sent to the HM-10 device. */
static void HandleTxDataIndication(void)
{
  char c = Serial.read();
  
  /* Echo the character just been sent. */
  Serial.write(c);
  
  /* We don't send carriage return or line feed. */
  if (c == 0x0A || c == 0x0D)
  {
    return;
  }
  
  btSerial.write(c);
}

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop()
{
  if (btSerial.available())
  {
    char c = btSerial.read();
    Serial.print(c);
  }
  
  if (Serial.available())
  {
    char c = Serial.read();  
    Serial.print(c);
    if (c == 0x0A || c == 0x0D)
    {
      return;
    }
    btSerial.write(c);
  }
}
