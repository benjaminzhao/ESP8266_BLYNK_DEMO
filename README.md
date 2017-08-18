# ESP8266_BLYNK_DEMO
A demo for generic ESP8266 module with Smart WiFi Config, HTTP OTA and Blynk service.</br>

ESP-12E, ESP-12S, NodeMCU is prefered. </br>

1.  "Smart Config" is a core function of ESP8266 Arduino Library. Using ardroid App to set up WiFi connection. </br>
    Related files: </br>
      ESP8266WiFiSTA.cpp </br>
      ESP8266WiFiSTA.h </br>
    Core functions: </br>
      beginSmartConfig() </br>
      stopSmartConfig() </br>
      smartConfigDone() </br>
    Demo App:
      IOT_Espressif_EspTouch

2.  HTTP OTA uses browser to upload firmware to the ESP8266. The most direct method is enter the LAN ip address of ESP8266 which would be updated.
    
3.  "Blynk" is an open source IoT platform. It provides IoT cloud service and App for remote control from LAN and WAN. A unique feature of Blynk is private cloud which is pretty simple to setup on Raspberry Pi. 
