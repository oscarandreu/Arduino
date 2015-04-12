#include "WifiHandler.h"
#include <Arduino.h>

// Constructor
WifiHandler::WifiHandler(uint8_t receivePin, uint8_t transmitPin)
    : wSerial(receivePin, transmitPin)
{
    wSerial.begin(9600);
    _connected = false;
}

// Desctructor
WifiHandler::~WifiHandler()
{
    wSerial.end();
}

//region Public Methods

//Connect to a given wifi network
bool WifiHandler::connectToWifi(String ssid, String password, int maxConnectionAttemps)
{
    String command = "AT+CWJAP=\""+ssid+"\",\""+password+"\"";
    int connAttempts = 0;

    do
    {
        wSerial.print(command);
        connAttempts++;
    }
    while(wSerial.find(WIFI_OK) || connAttempts > maxConnectionAttemps);

    _connected = !(connAttempts > maxConnectionAttemps);

    return _connected;
}

String WifiHandler::getIpAddress()
{
    sendCommand("AT+CIFSR");

    return getResponse();
}

String WifiHandler::sendCommand(String command)
{
    wSerial.print(command);

    return getResponse();
}

String WifiHandler::getResponse()
{
    String response;
    int c = wSerial.read();

    while( c > 0)
    {
        response += char(c);
        c = wSerial.read();
    }

    Serial.print("-> ");
//    Serial.println(commandResult(response));
    Serial.println(response);

    return response;
}

// returns true if response have OK and false if not
bool WifiHandler::getCommandResult(String commandResponse)
{
    return commandResponse.endsWith(WIFI_OK);
}

//bool wifiConnected()
//{
//    *_wSerial.print("AT");
//    return *_wSerial.find(WIFI_OK) ? true : false;
//}

//endregion

//regioni Private Methods

//endregion


