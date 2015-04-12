#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <SoftwareSerial.h>

#define WIFI_OK      "OK"
//#define WIFI_ERROR      "ERROR"


class WifiHandler
{
    public:
        SoftwareSerial wSerial;

        WifiHandler(uint8_t receivePin, uint8_t transmitPin);
        virtual ~WifiHandler();
//
        bool connectToWifi(String ssid, String password, int maxConnectionAttemps);
//        bool wifiConnected();
        String getResponse();
        bool commandResult(String commandResponse);
        String getIpAddress();
        String sendCommand(String command);

    protected:

    private:
        bool _connected;

};

#endif // WIFIHANDLER_H
