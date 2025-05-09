
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPUpdateServer.h>
#include <arduino-timer.h>
#include <PubSubClient.h>
#include <ArduinoLog.h>

#include "arduino_secrets.h"
#include "configuration.hpp"

#include "device\domeHandler.h"


int status = WL_IDLE_STATUS;
///////enter your sensitive data in the Secret tab/arduino_secrets.h
char hostname[] = _HOSTNAME;
char ssid[] = _SSID;     // your network SSID (name)
char pass[] = _PASSWORD; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;        // your network key Index number (needed only for WEP)

unsigned int localPort = 32227;  // The Alpaca Discovery test port
unsigned int alpacaPort = 11111; // The (fake) port that the Alpaca API would be available on

char packetBuffer[255]; // buffer to hold incoming packet

// MQTT Broker
IPAddress mqtt_server = MQTT_HOST;
const char *topic = MQTT_TOPIC;
const int mqtt_port = MQTT_PORT; //1883;
const char *mqtt_user = MQTT_USER; //"chris";
const char *mqtt_password = MQTT_PASS; // "wandasee2me3";
// end of MQTT

// ----------------------------------------------------------------------

WebServer *server = new WebServer(alpacaPort);

HTTPUpdateServer updater;
WiFiUDP Udp;

// MQTT
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

DomeHandler *device = new DomeHandler(server);

auto timer = timer_create_default();

void IRAM_ATTR openCallback() {
  device->domeDevice->Open();
}

void IRAM_ATTR closeCallback() {
  device->domeDevice->Close();
}

void IRAM_ATTR stopCallback() {
  device->domeDevice->Stop();
}



void CheckForDiscovery()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Log.traceln("Received packet of size: %d" CR, packetSize);
    IPAddress remoteIp = Udp.remoteIP();
    Log.traceln("From %s , on port %d" CR, remoteIp.toString().c_str(), Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      // Ensure that it is null terminated
      packetBuffer[len] = 0;
    }
    Log.traceln("Contents: %s" CR, packetBuffer);

    // No undersized packets allowed
    if (len < 16)
    {
      return;
    }

    if (strncmp("alpacadiscovery1", packetBuffer, 16) != 0)
    {
      return;
    }

    char response[36] = {0};
    sprintf(response, "{\"AlpacaPort\": %d}", alpacaPort);

    uint8_t buffer[36] = "{\"AlpacaPort\": 11111}";

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(buffer, 36);
    Udp.endPacket();
  }
}

// MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "tcn-power-switch";
    // clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.publish(MQTT_TOPIC, "Switch is running");
      // client.subscribe("inTopic");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Log.traceln(F("SSID: %s" CR), WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Log.traceln(F("IP Address: %s" CR), ip.toString().c_str());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Log.traceln("signal strength (RSSI): %l dBm" CR, rssi);
}


void handleMgmtVersions() { device->handlerMgmtVersions(); }
void handleMgmtDescription() { device->handlerMgmtDescription(); }
void handleMgmtConfiguredDevices() { device->handlerMgmtConfiguredDevices(); }

void handleConnected() { device->handlerConnected(); }
void handleDescriptionGet() { device->handlerDescriptionGet(); }
void handleDriverInfoGet() { device->handlerDriverInfoGet(); }
void handleDriverVersionGet() { device->handlerDriverVersionGet(); }
void handleInterfaceVersionGet() { device->handlerInterfaceVersionGet(); }
void handleNameGet() { device->handlerNameGet(); }
void handleSupportedActionsGet() { device->handlerSupportedActionsGet(); }

void handleAction() { device->handleAction(); }
void handleCommandBlind() { device->handleCommandBlind(); }
void handleCommandBool() { device->handleCommandBool(); }
void handleCommandString() { device->handleCommandString(); }

void handleDriver0CanFindHome() { device->handleDriver0CanFindHome(); }
void handleDriver0CanPark() { device->handleDriver0CanPark(); }
void handleDriver0CanSetAltitude() { device->handleDriver0CanSetAltitude(); }
void handleDriver0CanSetAzimuth() { device->handleDriver0CanSetAzimuth(); }
void handleDriver0CanSetPark() { device->handleDriver0CanSetPark(); }
void handleDriver0CanSetShutter() { device->handleDriver0CanSetShutter(); }
void handleDriver0CanSlave() { device->handleDriver0CanSlave(); }
void handleDriver0CanSyncAzimuth() { device->handleDriver0CanSyncAzimuth(); }

void handleDriver0Slewing() { device->handleDriver0Slewing(); }
void handleDriver0Altitude() { device->handleDriver0Altitude(); }
void handleDriver0AtHome() { device->handleDriver0AtHome(); }
void handleDriver0AtPark() { device->handleDriver0AtPark(); }
void handleDriver0Azimuth() { device->handleDriver0Azimuth(); }
void handleDriver0Shutterstatus() { device->handleDriver0Shutterstatus(); }
void handleDriver0Slaved() { device->handleDriver0Slaved(); }
void handleDriver0SlewToAltitude() { device->handleDriver0SlewToAltitude(); }
void handleDriver0SlewToAzimuth() { device->handleDriver0SlewToAzimuth(); }
void handleDriver0AbortSlew() { device->handleDriver0AbortSlew(); }
void handleDriver0SyncToAzimuth() { device->handleDriver0SyncToAzimuth(); }
void handleDriver0CloseShutter() { device->handleDriver0CloseShutter(); }
void handleDriver0OpenShutter() { device->handleDriver0OpenShutter(); }
void handleDriver0FindHome() { device->handleDriver0FindHome(); }
void handleDriver0Park() { device->handleDriver0Park(); }
void handleDriver0SetPark() { device->handleDriver0SetPark(); }



/*
void handleDriver0Maxswitch() { device->handlerDriver0Maxswitch(); }
void handleDriver0CanWrite() { device->handlerDriver0CanWrite(); }
void handleDriver0SwitchDescription() { device->handlerDriver0SwitchDescription(); }
void handleDriver0SwitchState() { device->handlerDriver0SwitchState(); }
void handleDriver0SwitchName() { device->handlerDriver0SwitchName(); }
void handleDriver0SwitchValue() { device->handlerDriver0SwitchValue(); }
void handleDriver0MinSwitchValue() { device->handlerDriver0MinSwitchValue(); }
void handleDriver0MaxSwitchValue() { device->handlerDriver0MaxSwitchValue(); }
void handleDriver0SwitchStep() { device->handlerDriver0SwitchStep(); }
*/

/******************************************
 * SETUP
 ******************************************/
void setup()
{
  Serial.begin(115200);

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_ERROR, &Serial);

  Log.infoln("Connecting to WIFI...");

  // Some ESP8266 modules broadcast their own network, this turns that off
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);

  // attempt to connect to the Wifi network defined in arduino_secrets.h
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Log.traceln(".");
  }

  Log.infoln("Connected to wifi");
  printWifiStatus();

  // Management API
  server->on("/management/apiversions", HTTP_GET, handleMgmtVersions);
  server->on("/management/v1/description", HTTP_GET, handleMgmtDescription);
  server->on("/management/v1/configureddevices", HTTP_GET, handleMgmtConfiguredDevices);

  server->on("/api/v1/dome/0/connected", HTTP_ANY, handleConnected);
  server->on("/api/v1/dome/0/description", HTTP_GET, handleDescriptionGet);
  server->on("/api/v1/dome/0/driverinfo", HTTP_GET, handleDriverInfoGet);
  server->on("/api/v1/dome/0/driverversion", HTTP_GET, handleDriverVersionGet);
  server->on("/api/v1/dome/0/interfaceversion", HTTP_GET, handleInterfaceVersionGet);
  server->on("/api/v1/dome/0/name", HTTP_GET, handleNameGet);
  server->on("/api/v1/dome/0/supportedactions", HTTP_GET, handleSupportedActionsGet);

  server->on("/api/v1/dome/0/action", HTTP_GET, handleAction);
  server->on("/api/v1/dome/0/commandblind", HTTP_GET, handleCommandBlind);
  server->on("/api/v1/dome/0/commandbool", HTTP_GET, handleCommandBool);
  server->on("/api/v1/dome/0/commandstring", HTTP_GET, handleCommandString);

  server->on("/api/v1/dome/0/canfindhome", HTTP_GET, handleDriver0CanFindHome);
  server->on("/api/v1/dome/0/canpark", HTTP_GET, handleDriver0CanPark);
  server->on("/api/v1/dome/0/cansetaltitude", HTTP_GET, handleDriver0CanSetAltitude);
  server->on("/api/v1/dome/0/cansetazimuth", HTTP_GET, handleDriver0CanSetAzimuth);
  server->on("/api/v1/dome/0/cansetpark", HTTP_GET, handleDriver0CanSetPark);
  server->on("/api/v1/dome/0/cansetshutter", HTTP_GET, handleDriver0CanSetShutter);
  server->on("/api/v1/dome/0/canslave", HTTP_GET, handleDriver0CanSlave);
  server->on("/api/v1/dome/0/cansyncazimuth", HTTP_GET, handleDriver0CanSyncAzimuth);


  server->on("/api/v1/dome/0/slewing", HTTP_GET, handleDriver0Slewing); /**/
  server->on("/api/v1/dome/0/altitude", HTTP_GET, handleDriver0Altitude);
  server->on("/api/v1/dome/0/athome", HTTP_GET, handleDriver0AtHome);
  server->on("/api/v1/dome/0/atpark", HTTP_GET, handleDriver0AtPark);
  server->on("/api/v1/dome/0/azimuth", HTTP_GET, handleDriver0Azimuth);
  server->on("/api/v1/dome/0/shutterstatus", HTTP_GET, handleDriver0Shutterstatus);

  server->on("/api/v1/dome/0/slaved", HTTP_ANY, handleDriver0Slaved); /**/
  server->on("/api/v1/dome/0/slewtoaltitude", HTTP_PUT, handleDriver0SlewToAltitude);
  server->on("/api/v1/dome/0/slewtoazimuth", HTTP_PUT, handleDriver0SlewToAzimuth);
  server->on("/api/v1/dome/0/abortslew", HTTP_PUT, handleDriver0AbortSlew);
  server->on("/api/v1/dome/0/synctoazimuth", HTTP_PUT, handleDriver0SyncToAzimuth);
  server->on("/api/v1/dome/0/closeshutter", HTTP_PUT, handleDriver0CloseShutter);
  server->on("/api/v1/dome/0/openshutter", HTTP_PUT, handleDriver0OpenShutter);
  server->on("/api/v1/dome/0/findhome", HTTP_PUT, handleDriver0FindHome);
  server->on("/api/v1/dome/0/park", HTTP_PUT, handleDriver0Park);
  server->on("/api/v1/dome/0/setpark", HTTP_PUT, handleDriver0SetPark);



  

  /*
  // Switch-specific functions
  server->on("/api/v1/switch/0/maxswitch", HTTP_GET, handleDriver0Maxswitch);
  server->on("/api/v1/switch/0/canwrite", HTTP_GET, handleDriver0CanWrite);
  server->on("/api/v1/switch/0/getswitchdescription", HTTP_GET, handleDriver0SwitchDescription);
  server->on("/api/v1/switch/0/getswitch", HTTP_GET, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/setswitch", HTTP_PUT, handleDriver0SwitchState);
  server->on("/api/v1/switch/0/getswitchname", HTTP_GET, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/setswitchname", HTTP_PUT, handleDriver0SwitchName);
  server->on("/api/v1/switch/0/getswitchvalue", HTTP_GET, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/setswitchvalue", HTTP_PUT, handleDriver0SwitchValue);
  server->on("/api/v1/switch/0/minswitchvalue", HTTP_GET, handleDriver0MinSwitchValue);
  server->on("/api/v1/switch/0/maxswitchvalue", HTTP_GET, handleDriver0MaxSwitchValue);
  server->on("/api/v1/switch/0/switchstep", HTTP_GET, handleDriver0SwitchStep);
  */
  /*
  //Custom
  server.on("/status",                              HTTP_GET, handlerStatus);
  server.on("/restart",                             HTTP_ANY, handlerRestart);
  */

  updater.setup(server);
  server->begin();
  Log.infoln("Alpaca server handlers setup & started...");
  Log.infoln("Listening for Alpaca discovery requests...");

  Udp.begin(localPort);

  // connectToRedis();
  // MQTT

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  /*
  Butoon callbacks
  */

  // Open Button Callback
  pinMode(OPEN_BTN, INPUT_PULLUP);
	attachInterrupt(OPEN_BTN, openCallback, FALLING);

  // Close Button Callback
  pinMode(CLOSE_BTN, INPUT_PULLUP);
	attachInterrupt(CLOSE_BTN, closeCallback, FALLING);

  // Stop Button Callback
  pinMode(STOP_BTN, INPUT_PULLUP);
	attachInterrupt(STOP_BTN, stopCallback, FALLING);

  device->domeDevice->Setup();
}

void loop()
{

  server->handleClient();
  CheckForDiscovery();
  timer.tick();
  device->domeDevice->Loop();
}