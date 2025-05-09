#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <WiFi.h>
#include <HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "configuration.hpp"
#include "domeDevice.h"

class DomeHandler
{
    WebServer* _server;

    public:
        DomeHandler(WebServer* server);
        DomeDevice* domeDevice;
        
        void handlerMgmtVersions();
        void handlerMgmtDescription();
        void handlerMgmtConfiguredDevices();

        void handlerConnected();
        void handlerDescriptionGet();
        void handlerDriverInfoGet();
        void handlerDriverVersionGet();
        void handlerInterfaceVersionGet();
        void handlerNameGet();
        void handlerSupportedActionsGet();

        void handleAction();
        void handleCommandBlind();
        void handleCommandBool();
        void handleCommandString();

        void handlerDriver0AtHome();

        void handleDriver0CanFindHome();
        void handleDriver0CanPark();
        void handleDriver0CanSetAltitude();
        void handleDriver0CanSetAzimuth();
        void handleDriver0CanSetPark();
        void handleDriver0CanSetShutter();
        void handleDriver0CanSlave();
        void handleDriver0CanSyncAzimuth();



        void handleDriver0Slewing();
        void handleDriver0Altitude();
        void handleDriver0AtHome();
        void handleDriver0AtPark();
        void handleDriver0Azimuth();
        void handleDriver0Shutterstatus();
        void handleDriver0Slaved(); /**/
        void handleDriver0SlewToAltitude();
        void handleDriver0SlewToAzimuth();
        void handleDriver0AbortSlew();
        void handleDriver0SyncToAzimuth();
        void handleDriver0CloseShutter();
        void handleDriver0OpenShutter();
        void handleDriver0FindHome();
        void handleDriver0Park();
        void handleDriver0SetPark();

    
    private:
        uint32_t transID;
        uint32_t clientID;
        uint32_t serverTransactionID = 0;
        String uniqueID = "5b595097-b277-43c2-8ce3-2f5a1afeb62f";

        

        void incrementServerTransID();

        void returnEmpty(String errMsg, int errNr);

        void returnStringValue(String val, String errMsg, int errNr);
        void returnBoolValue(bool val, String errMsg, int errNr);
        void returnIntValue(int val, String errMsg, int errNr);
        void returnFloatValue(float val, String errMsg, int errNr);
        void returnJsonArrayValue(JsonArray val, String errMsg, int errNr);
        void returnDoubleValue(double val, String errMsg, int errNr);

        void debugServerQuery();
        
};
