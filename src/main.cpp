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

#include <ArduinoJson.h>
#include <PubSubClient.h>

void callback(char *topic, byte *payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient client("192.168.50.31", 1883, callback, wifiClient);

#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

void setup() {

  #ifdef ESP32

  #else

  #endif

  Serial.begin(115200);
  while (!Serial);
  DEBUG_ERROR_SERIAL.println("This is an error message");
  DEBUG_WARNING_SERIAL.println("This is a warning message");
  DEBUG_INFORMATION_SERIAL.println("Some output value");
  connectWifi();
  initManagedDevice();
}

void loop() {
  if (!client.connected()) {
    Serial.println("Not connected - go to reconnect");
    reconnect();
  }
  askSensors();

  if (millis() - oldMillisONE >= pauseONE) {
    DEBUG_INFORMATION_SERIAL.println("ten seconds passed");
    sendSensors();
    oldMillisONE = millis();
  }

  client.loop();
}