#pragma once

//#define ESP32

#define SERVER_NAME "TCN"
#define MANUFACTURER "Christian Kardach"
#define MANUFACTURER_VERSION "1.0"
#define LOCATION "SE"

#define DEVICE_NAME "TCN ROR"
#define DEVICE_TYPE "Dome"
#define DEVICE_NR 0
#define UNIQUE_CLIENT_ID "7c88a14b-934d49f9be546c72715abbe3" // https://www.guidgenerator.com/online-guid-generator.aspx

#define DESCRIPTION "Mount ASCOM Dome"
#define DRIVER_INFO "TCN ASCOM Alpaca ROR"
#define DRIVER_VERSION "1.0"

#define OPEN_BTN 25
#define CLOSE_BTN 27
#define STOP_BTN 26

#define OPEN_STOP_RELAY 33
#define CLOSE_STOP_RELAY 32

#define BST_LPWM 18    // I/O channel setup ESP32 pin 
#define BST_RPWM 19    // I/O chennel setup ESP32 pin
#define EN_LR 22    // I/O pin for BST l_EN & R_EN (enable)
