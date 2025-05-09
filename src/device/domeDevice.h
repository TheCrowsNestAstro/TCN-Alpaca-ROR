#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

class DomeDevice
{
    public:
        DomeDevice();

        bool connected = false;
        
        bool slewing = false;
        bool atHome = true;
        bool atPark = true;
        
        int shutterStatus = 1; // 0 = Open, 1 = Closed, 2 = Opening, 3 = Closing, 4 = Shutter status error
        
        bool slaved = false;

        bool openReached = false;
        bool closeReached = false;

        
        String uniqueID = "";

        void Setup();
        void Loop();

        void Open();
        void Close();
        void Stop();
        
    private:
        int direction = 2; // 1 = Open, 2 = Stop, 3 = Close
        long lastDoTime = 0;

        bool switchesOff = false;
        
};
