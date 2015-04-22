#include <Arduino.h>
#include <SoftwareSerial.h>
#include <C:\Personal\Arduino\Projects\Wifi\WifiHandler.h>

WifiHandler wifiHandler(3, 2);

String serialImput = "";

//bool wifiConnected()
//{
//    wSerial.print("AT");
//    return wSerial.find(WIFI_OK) ? true : false;
//}
void flushSerial()
{
    serialImput = "";
    Serial.flush();
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
        serialImput += char(code);

        if(code == 33)
        {
            String response;
            bool ok = wifiHandler.getIpAddress(response);
            flushSerial();

            Serial.println(response);
            if(ok)
                Serial.println("OK.................");
            else
            {
                Serial.print("FAIL....................");
            }
        }
        else if(code == '$')
        {
            String response = wifiHandler.getCwMode();
            Serial.println(response);
        }
        else if(code == 10)
        {
            String response;
            Serial.println(wifiHandler.sendCommand(serialImput, response));
            flushSerial();

            bool ok = Serial.println(response);
            if(ok)
                Serial.println("OK.................");
            else
            {
                Serial.print("FAIL....................");
            }
        }
    }
}





/*
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX

void setup()
  {  Serial.begin(9600);
     BT1.begin(9600);
  }

void loop()
  {  String B= "." ;
     if (BT1.available())
         { char c = BT1.read() ;
           Serial.print(c);
         }
     if (Serial.available())
         {  char c = Serial.read();
            BT1.print(c);
         }
   }
//*/
