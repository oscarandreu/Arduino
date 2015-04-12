#include <Arduino.h>


void alarm(int rounds, int interval, int wait)
{
    for(int i = 0; i < rounds-1; i++)
    {
      digitalWrite(13, HIGH);
      delay(interval);
      digitalWrite(13, LOW);
      delay(interval);
    }
    delay(wait);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
}


void setup()
{
	Serial.begin(9600);
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(4, INPUT);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	delay(3000);        
        alarm(6, 50, 500);
}
  
void loop()
{
    delay(500);
    int state = digitalRead(4);
    if(state == HIGH){
        alarm(4, 100, 2000);
    };
}
