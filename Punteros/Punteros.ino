#include <Arduino.h>


void setup()
{
	Serial.begin(9600);
}

void loop()
{
    int v = 100 ;
    Serial.println( (long)&v);
    v = NULL;

    int *ptr_test;
    *ptr_test = 8;
    Serial.println(*ptr_test);
    delay(3000);
}
