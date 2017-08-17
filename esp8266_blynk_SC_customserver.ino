
// INCLUDE EXTRA LIBs
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// INCLUDE ESP WIFI lIBs
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#define BLYNK_PRINT Serial      // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266_SSL.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// char auth[] = "fa84fec03a0f4e83aba9f14de37d5f4f";  //admin@blynk.cc
const char auth[] = "3fe82a943ab541feba566418e96a9045";     //user acount
const char domain[] = "bbhh.dlinkddns.com";
uint16_t port = 8441;
const char fingerprint[] = "B3 62 6B BC A0 90 65 EA 1B 62 14 3A 54 51 14 C1 D1 2D AF F9";

BlynkTimer timer;

static const char* Mdns_Host = "esp8266";
const char* update_username = "admin";
const char* update_password = "admin";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater(true);

// PIN DEFINE
#define LED_G_PIN     12
#define LED_B_PIN     13
#define LED_R_PIN     15
#define BUTTON_PIN    4
#define ADC_PIN       A0
#define BUILTIN_LED   2


void setup() {
    Serial.begin(115200);

    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    
    if (!SPIFFS.begin()){
        Serial.println("Failed to mount file system");
    }
    WiFi.mode(WIFI_STA);

    int cnt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        status_blink();
        delay(100);
        status_blink();
        delay(400);
        Serial.print(".");
        if (cnt++ >= 10) {
            WiFi.beginSmartConfig();
            while (1) {
                status_blink();
                delay(500);
                status_blink();
                delay(500);
                if (WiFi.smartConfigDone()) {
                    Serial.println();
                    Serial.println("[WIFI] SmartConfig: Success");
                    break;
                }
                Serial.print("|");
            }
        }
        digitalWrite(BUILTIN_LED, HIGH);
    }
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

    WiFi.printDiag(Serial);
    httpUpdater.setup(&httpServer, update_username, update_password);
    //Serial.println(BLYNK_DEFAULT_FINGERPRINT);
    // Start TCP (HTTP) server
    httpServer.begin();
    
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);

    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
    
    Blynk.config(auth, domain, port, fingerprint);
}

void loop(){
    Blynk.run();
    timer.run(); // Initiates SimpleTimer
    httpServer.handleClient();
}

void status_blink(){
    digitalWrite(BUILTIN_LED, LOW);
    delay(50);
    digitalWrite(BUILTIN_LED, HIGH);
}

void myTimerEvent_1(){
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    int sensorValue = analogRead(ADC_PIN);
    Blynk.virtualWrite(V5, sensorValue);
}

void myTimerEvent(){
    status_blink();
    delay(50);
    status_blink();
    ESP.getFreeHeap();
    Serial.print(F("[ESP] Free heap: "));
    Serial.println(ESP.getFreeHeap());
}
