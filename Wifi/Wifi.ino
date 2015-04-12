#include <Arduino.h>
#include <SoftwareSerial.h>
#include <C:\Personal\Arduino\Projects\Wifi\WifiHandler.h>

WifiHandler wifiHandler(3, 2);

//bool wifiConnected()
//{
//    wSerial.print("AT");
//    return wSerial.find(WIFI_OK) ? true : false;
//}

int readFromSerial()
{
    int result = 0;

    if (Serial.available() > 0)
    {
        result = Serial.read();
    }

    return result;
}


void setup()
{
    Serial.begin(9600);
    bool connected = wifiHandler.connectToWifi("__", "dracaenadraco", 3);

    if(connected)
        Serial.println("Wifi status.... OK.");
    else
        Serial.println("Wifi status.... FAIL.");
}

void loop()
{
    if (Serial.available() > 0)
    {
        int code = Serial.read();

Serial.print("-->");
Serial.println(code);


        if(code == 33)
            Serial.println(wifiHandler.getIpAddress());
        else
        {
            wifiHandler.wSerial.print(char(code));
        }

    }
}
