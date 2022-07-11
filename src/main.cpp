#include <globals.h>
#include <Arduino.h>
#include <Wire.h>

#ifdef ESP32
  #include <M5Stack.h>
  #include <WiFi.h>
#else
  #include <WiFiNINA.h>
#endif

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <functions.h>

#include <ArduinoJson.h>
#include <PubSubClient.h>

void callback(char *topic, byte *payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  DEBUG_ERROR_SERIAL.println("This is an error message");
  DEBUG_WARNING_SERIAL.println("This is a warning message");
  DEBUG_INFORMATION_SERIAL.print("Some output value");

}

void loop() {
  askSensors();
  time_now = millis();
  while(millis() < time_now + period){    
    // add the code you want to keep running here
    DEBUG_INFORMATION_SERIAL.print("one second passed");
    sendSensors();
   }
}