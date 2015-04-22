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

    do{
        wSerial.print(command);
        connAttempts++;
    }
    while(wSerial.find(WIFI_OK) || connAttempts > maxConnectionAttemps);

    _connected = !(connAttempts > maxConnectionAttemps);

    return _connected;
}

bool WifiHandler::getIpAddress(String &response)
{
    return sendCommand("AT+CIFSR", response);
}

bool WifiHandler::sendCommand(String command, String &response)
{
    wSerial.print(command);

    response = getResponse();
    return commandResult(response);
}

String WifiHandler::getCwMode()
{
    String response;
    sendCommand("AT+CWMODE=3", response);

    return response;//(String)response.charAt(response.indexOf(':') + 1);
}


//void http(String output)
//  {  Serial3.print("AT+CIPSEND=0,");   // AT+CIPSEND=0, num
//     Serial3.println(output.length());
//     if (Serial3.find(">"))            // Si recibimos la peticion del mensaje
//        { Serial.println(output);
//          Serial3.println(output);     //Aqui va el string
//          delay(10);
//          while( Serial3.available() > 0)    // Busca el OK en la respuesta
//            { if (  Serial3.find("SEND OK")  )  break;
//            }
//         }
//  }

bool WifiHandler::SendMessage(String message)
{
    String response;
    String command = "AT+CIPSEND=0, " + message.length();
    sendCommand(command, response);

    return commandResult(response);
}

bool WifiHandler::ConnectToServer(String ip, int port)
{
    String response;
    String command = "AT+CPISTART=\"TCP\",\"" + ip + "\"," + port;
    sendCommand(command, response);

    return commandResult(response);
}

bool WifiHandler::listen(int port)
{
    String response;
    sendCommand("AT+CIPMUX=1", response);
    sendCommand("AT+CIPSERVER=1," + port, response);

    return commandResult(response);
}


//endregion

//regioni Private Methods

// returns true if response have OK and false if not
bool WifiHandler::commandResult(String response)
{
    return response.endsWith(WIFI_OK);
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
    response.trim();

//    for(int i = 0; i < response.length(); i++ )
//    {
//        Serial.print(response.charAt(i));
//        Serial.print(" - ");
//        Serial.println((int)response.charAt(i));
//    }
//    Serial.println("#####################################");

    return response;
}
//endregion


