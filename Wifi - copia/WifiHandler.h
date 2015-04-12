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

        String getResponse();
        bool getCommandResult(String commandResponse);

        bool connectToWifi(String ssid, String password, int maxConnectionAttemps);
        String getIpAddress();
        String sendCommand(String command);

    protected:

    private:
        bool _connected;

};

#endif // WIFIHANDLER_H
