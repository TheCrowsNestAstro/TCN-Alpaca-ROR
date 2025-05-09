#include "device\domeDevice.h"

DomeDevice::DomeDevice()
{
    
}

void DomeDevice::Setup()
{
    pinMode(OPEN_STOP_RELAY, INPUT_PULLUP);
    pinMode(CLOSE_STOP_RELAY, INPUT_PULLUP);

    pinMode(EN_LR, OUTPUT);

    pinMode(BST_LPWM, OUTPUT);
    pinMode(BST_RPWM, OUTPUT);
}


void DomeDevice::Loop()
{
    digitalWrite(EN_LR,HIGH); // enable BST
    int openSwitchState = digitalRead(OPEN_STOP_RELAY);
    int closeSwitchState = digitalRead(CLOSE_STOP_RELAY);
    // 0 = Triggered
    // 1 = Neutral

    // Serial.println(closeSwitchState);
    
    /*
    if(!slewing && openSwitchState == 0 && closeSwitchState == 1)
    {
        shutterStatus = 0;
    }
    else if(!slewing && openSwitchState == 1 && closeSwitchState == 0)
    {
        shutterStatus = 1;
    }
    else if(!slewing && openSwitchState == 1 && closeSwitchState == 1)
    {
        shutterStatus = 4;
    }
    */
    
    if(!slewing)
    {
        analogWrite(BST_LPWM, 0);
        analogWrite(BST_RPWM, 0);
        return;
    }
    /*
    if(atPark)
    {
        analogWrite(BST_LPWM, 0);
        analogWrite(BST_RPWM, 0);
        return;
    }
    */
    // OPEN
    if(slewing && openSwitchState == 1 && direction == 1)
    {
        analogWrite(BST_LPWM, 128);
        analogWrite(BST_RPWM, 0);
        
    }
    
    else if(slewing && openSwitchState == 0 && direction == 1)
    {
        analogWrite(BST_LPWM, 0);
        analogWrite(BST_RPWM, 0);
        slewing = false;

        shutterStatus = 0;
    }
    

    // CLOSE
    if(slewing && closeSwitchState == 1 && direction == 3)
    {
        analogWrite(BST_LPWM, 0);
        analogWrite(BST_RPWM, 128);
    }
    
    else if(slewing && closeSwitchState == 0 && direction == 3)
    {
        analogWrite(BST_LPWM, 0);
        analogWrite(BST_RPWM, 0);
        slewing = false;

        shutterStatus = 1;
    }

}

void DomeDevice::Open()
{
    Log.traceln("Open Called");
    atPark = false;
    slewing = true;
    direction = 1; // Open
    shutterStatus = 2;

    Serial.println(switchesOff);
    
}

void DomeDevice::Close()
{
    Log.traceln("Close Called");
    slewing = true;
    direction = 3; // Close
    shutterStatus = 3;

    Serial.println(switchesOff);
    
}

void DomeDevice::Stop()
{
    Log.traceln("Stop Called");
    slewing = false;
    direction = 2; // Close
    shutterStatus = 4;

    Serial.println(switchesOff);
    
}