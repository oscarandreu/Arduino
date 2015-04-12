#include "WifiHandler.h"
#include <Arduino.h>

// Constructor
WifiHandler::WifiHandler(uint8_t receivePin, uint8_t transmitPin)
    : wSerial(receivePin, transmitPin)
{
//    _wSerial(3, 2); // RX | TX
//    _wSerial = wSerial;
    wSerial.begin(9600);
    _connected = false;
}

// Desctructor
//WifiHandler::~WifiHandler()
//{
//    //dtor
//}

//region Public Methods

//Connect to a given wifi network
bool WifiHandler::connectToWifi(String ssid, String password, int maxConnectionAttemps)
{
    String command = "AT+CWJAP=\""+ssid+"\",\""+password+"\"";
    int connAttempts = 0;

    do{
        wSerial.print(command);
        connAttempts++;
    }
    while(wSerial.find(WIFI_OK) || connAttempts > maxConnectionAttemps);

    _connected = (connAttempts > maxConnectionAttemps) ? false : true;

    return _connected;
}

String WifiHandler::getIpAddress()
{
    wSerial.print("AT+CIFSR");

    return wSerial.readString();
}

String WifiHandler::getResponse()
{
    String response;
    do
    {
        int c = wSerial.read();
        response += char(c);
        if(c == 13)
            Serial.println(response);

        delay(10);
    }
    while(wSerial.find(WIFI_OK) || wSerial.find(WIFI_ERROR));

    Serial.println(response);

//    int chars = 0;
//    Serial.println("..................");
//    Serial.println(wSerial.available());
//
//    while(wSerial.available() >= chars);
//    {
//      Serial.println(wSerial.available());
//        int c = wSerial.read();
//        response += char(c);
//        chars++;
//    }
//    Serial.println("..................");
//    Serial.println(response);



//    if (wSerial.available() > 0)
//    {
//        char cw = wSerial.read();
//        Serial.print(cw);
//    }

    return response;
}

//bool wifiConnected()
//{
//    *_wSerial.print("AT");
//    return *_wSerial.find(WIFI_OK) ? true : false;
//}

//endregion

//regioni Private Methods

//endregion

