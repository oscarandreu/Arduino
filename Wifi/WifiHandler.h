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

        bool connectToWifi(String ssid, String password, int maxConnectionAttemps);
        bool sendCommand(String command, String &response);
        bool getIpAddress(String &response);
        String getCwMode();
        bool SendMessage(String message);
        bool ConnectToServer(String ip, int port);
        bool listen(int port);

    protected:

    private:
        bool _connected;

        String getResponse();
        bool commandResult(String commandResponse);
};

#endif // WIFIHANDLER_H
