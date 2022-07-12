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
PubSubClient client(mqttserver, 1883, callback, wifiClient);

#include <sdfunctions.h>
#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

void setup() {
  #ifdef ESP32
    M5.begin();
  #else

  #endif
  Serial.begin(115200);
  while (!Serial);
  //DEBUG_ERROR_SERIAL.println("This is an error message");
  //DEBUG_WARNING_SERIAL.println("This is a warning message");
  //DEBUG_INFORMATION_SERIAL.println("Some output value");
  connectWifi();
  initManagedDevice();

  #ifdef SAVE_SD
    initializeSD();
  #endif
}

void loop() {
  if (!client.connected()) {
    DEBUG_INFORMATION_SERIAL.println("Not connected - go to reconnect");
    reconnect();
  }

  if ((WiFi.status() != WL_CONNECTED) && (millis() - oldMillisTWO >= pauseTWO)) {
    DEBUG_INFORMATION_SERIAL.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    oldMillisTWO = millis();
  }

  askSensors();

  if (millis() - oldMillisONE >= pauseONE) {
    DEBUG_INFORMATION_SERIAL.println("ten seconds passed");
    sendSensors();
    oldMillisONE = millis();
  }

  client.loop();
}