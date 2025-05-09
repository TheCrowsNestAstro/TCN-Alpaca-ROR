#include "device\domeHandler.h"


DomeHandler::DomeHandler(WebServer *server)
{
    _server = server;
    domeDevice = new DomeDevice();
    serverTransactionID = 0;
}

void DomeHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.traceln("%d" CR, i);
        Log.traceln("%s" CR, _server->argName(i));
        Log.traceln("%s" CR, _server->arg(i));
        Log.traceln("--------------------------");
    }
}

void DomeHandler::incrementServerTransID()
{
    serverTransactionID++;
}

void DomeHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    //Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnIntValue(int val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void DomeHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    // Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}
/************************************
 * ALPACA DEVICE MANAGEMENT
**********************************/

void DomeHandler::handlerMgmtVersions()
{
    // .traceln("handlerMgmtVersions called...");
    incrementServerTransID();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "application/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void DomeHandler::handlerMgmtDescription()
{
    // Log.traceln("handlerMgmtDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "application/json", output);
        
    }
}

void DomeHandler::handlerMgmtConfiguredDevices()
{
    // Log.traceln("handlerMgmtConfiguredDevices called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "application/json", output);
        
    }
}

void DomeHandler::handlerConnected()
{
    // Log.traceln("handlerConnected called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");

        // String deviceType = _server->arg("device_type");
        // uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        // returnBoolValue(switchDevice->connected, "", 0);
        returnBoolValue(domeDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        debugServerQuery();
        Log.traceln("handlerConnected PUT called");

        if(_server->arg("Connected") == "False")
        {
            domeDevice->connected = false;
        }
        else if(_server->arg("Connected") == "True")
        {
            domeDevice->connected = true;
        }
        returnEmpty("", 0);
    }
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void DomeHandler::handlerDescriptionGet()
{
    // Log.traceln("handlerDescriptionGet called");
    returnStringValue(DESCRIPTION, "", 0);
}

void DomeHandler::handlerDriverInfoGet()
{
    // Log.traceln("handlerDriverInfoGet called");
    returnStringValue(DRIVER_INFO, "", 0);
}

void DomeHandler::handlerDriverVersionGet()
{
    // Log.traceln("handlerDriverVersionGet called");
    returnStringValue(DRIVER_VERSION, "", 0);
}

void DomeHandler::handlerInterfaceVersionGet()
{
    // Log.traceln("handlerInterfaceVersionGet called");
    returnIntValue(1, "", 0);
}

void DomeHandler::handlerNameGet()
{
    // Log.traceln("handlerNameGet called");
    returnStringValue(DEVICE_NAME, "", 0);
}

void DomeHandler::handlerSupportedActionsGet()
{
    // Log.traceln("handlerSupportedActionsGet called");

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");
    /*
    array.add("maxswitch");
    array.add("canwrite");
    array.add("getswitchdescription");
    array.add("getswitch");
    array.add("getswitchname");
    array.add("getswitchvalue");
    array.add("minswitchvalue");
    array.add("maxswitchvalue");
    array.add("switchstep");
    */
    returnJsonArrayValue(array, "", 0);
    
}

void DomeHandler::handleAction()
{
    // Log.traceln("handleAction called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void DomeHandler::handleCommandBlind()
{
    // Log.traceln("handleCommandBlind called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnEmpty("", 0);
}

void DomeHandler::handleCommandBool()
{
    // Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void DomeHandler::handleCommandString()
{
    // Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command.c_str());
    Log.traceln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

/***********************************
 * ASCOM DOME
 **********************************/

void DomeHandler::handleDriver0CanFindHome()
{
    // Log.traceln("handleDriver0CanFindHome called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}

void DomeHandler::handleDriver0CanPark()
{
    // Log.traceln("handleDriver0CanPark called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}

void DomeHandler::handleDriver0CanSetAltitude()
{
    // Log.traceln("handleDriver0CanSetAltitude called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}

void DomeHandler::handleDriver0CanSetAzimuth()
{
    // Log.traceln("handleDriver0CanSetAzimuth called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}

void DomeHandler::handleDriver0CanSetPark()
{
    // Log.traceln("handleDriver0CanSetPark called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(true, "", 0);
}

void DomeHandler::handleDriver0CanSetShutter()
{
    // Log.traceln("handleDriver0CanSetShutter called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(true, "", 0);
}

void DomeHandler::handleDriver0CanSlave()
{
    // Log.traceln("handleDriver0CanSlave called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}

void DomeHandler::handleDriver0CanSyncAzimuth()
{
    // Log.traceln("handleDriver0CanSyncAzimuth called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(false, "", 0);
}


void DomeHandler::handleDriver0Slewing()
{
    // Log.traceln("handleDriver0CanSyncAzimuth called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(domeDevice->slewing, "", 0);
}

void DomeHandler::handleDriver0Altitude()
{
    // Log.traceln("handleDriver0Altitude called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnDoubleValue(0.0, "", 0);
}

void DomeHandler::handleDriver0AtHome() 
{
    // Log.traceln("handleDriver0AtHome called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(domeDevice->atHome, "", 0);
}

void DomeHandler::handleDriver0AtPark() 
{
    // Log.traceln("handleDriver0AtHome called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(domeDevice->atPark, "", 0);
}

void DomeHandler::handleDriver0Azimuth() 
{
    //Log.traceln("handleDriver0Azimuth called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnDoubleValue(0.0, "", 0);
}

void DomeHandler::handleDriver0Shutterstatus() {
    // 0 = Open, 1 = Closed, 2 = Opening, 3 = Closing, 4 = Shutter status error

     // Log.traceln("handleDriver0Shutterstatus called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnIntValue(domeDevice->shutterStatus, "", 0);
}

void DomeHandler::handleDriver0Slaved() 
{

    // Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");
        returnBoolValue(domeDevice->slaved, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        returnEmpty("Not Implemented", 1024);
    }

    //returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0SlewToAltitude() 
{
    //Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0SlewToAzimuth() 
{
    // Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0AbortSlew()
{
    Log.traceln("handleDriver0AbortSlew called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    
    domeDevice->Stop();
    
    returnEmpty("", 0);
}

void DomeHandler::handleDriver0SyncToAzimuth() 
{
    // Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0CloseShutter() 
{
    Log.traceln("handleDriver0CloseShutter called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    //domeDevice->shutterStatus = 3; // Closing
    domeDevice->Close();

    returnEmpty("", 0);
}

void DomeHandler::handleDriver0OpenShutter()
{
    Log.traceln("handleDriver0OpenShutter called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    
    domeDevice->Open();
    // domeDevice->shutterStatus = 2; // Opening

    returnEmpty("", 0);
}

void DomeHandler::handleDriver0FindHome() {
    // Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0Park() {
    // Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}

void DomeHandler::handleDriver0SetPark()
{
    //Log.traceln("handleDriver0Slaved called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    returnEmpty("Not Implemented", 1024);
}



/***********************************
 * ASCOM SWITCH
 **********************************/
/*
void DomeHandler::handlerDriver0Maxswitch()
{
    Log.traceln("handlerDriver0Maxswitch called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(NR_OF_RELAYS, "", 0);
}

void DomeHandler::handlerDriver0CanWrite()
{
    Log.traceln("handlerDriver0CanWrite called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true, "", 0);
}

void DomeHandler::handlerDriver0SwitchDescription()
{
    Log.traceln("handlerDriver0SwitchDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("Id").toInt();
    
    switch (id)
    {
    case 0:
        returnStringValue(RELAY_0_DESC, "", 0);
        break;
    case 1:
        returnStringValue(RELAY_1_DESC, "", 0);
        break;
    case 2:
        returnStringValue(RELAY_2_DESC, "", 0);
        break;
    case 3:
        returnStringValue(RELAY_3_DESC, "", 0);
        break;
    case 4:
        returnStringValue(RELAY_4_DESC, "", 0);
        break;
    case 5:
        returnStringValue(RELAY_5_DESC, "", 0);
        break;
    case 6:
        returnStringValue(RELAY_6_DESC, "", 0);
        break;
    case 7:
        returnStringValue(RELAY_7_DESC, "", 0);
        break;
    default:
        returnStringValue("None", "", 0);
        break;
    }
    
}

void DomeHandler::handlerDriver0SwitchState()
{
    Log.traceln("handlerDriver0SwitchState called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("Id").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchState called");

        returnBoolValue(switchDevice->relayStateBool[id], "", 0);
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchState called");
        bool val = (bool)_server->arg("State");

        switchDevice->setRelayState(id, val);
        returnEmpty("", 0);
    }
}

void DomeHandler::handlerDriver0SwitchName()
{
    Log.traceln("handlerDriver0SwitchName called");

    // debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("Id").toInt();

    switch (id)
    {
    case 0:
        returnStringValue(RELAY_0_NAME, "", 0);
        break;
    case 1:
        returnStringValue(RELAY_1_NAME, "", 0);
        break;
    case 2:
        returnStringValue(RELAY_2_NAME, "", 0);
        break;
    case 3:
        returnStringValue(RELAY_3_NAME, "", 0);
        break;
    case 4:
        returnStringValue(RELAY_4_NAME, "", 0);
        break;
    case 5:
        returnStringValue(RELAY_5_NAME, "", 0);
        break;
    case 6:
        returnStringValue(RELAY_6_NAME, "", 0);
        break;
    case 7:
        returnStringValue(RELAY_7_NAME, "", 0);
        break;
    
    default:
        break;
    }
    
}

void DomeHandler::handlerDriver0SwitchValue()
{
    Log.traceln("handlerDriver0SwitchValue called");
    //debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("Id").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchValue called");
        returnDoubleValue(switchDevice->relayStateValue[id], "", 0);
        
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchValue called");
        double val = (double)_server->arg("Value").toDouble();
        
        switchDevice->setRelayValue(id, val);
        returnEmpty("", 0);
    }


}

void DomeHandler::handlerDriver0MinSwitchValue()
{
    Log.traceln("handlerDriver0MinSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(0.0, "", 0);
}

void DomeHandler::handlerDriver0MaxSwitchValue()
{
    Log.traceln("handlerDriver0MaxSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}

void DomeHandler::handlerDriver0SwitchStep()
{
    Log.traceln("handlerDriver0SwitchStep called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}
*/