#include <globals.h>
#include <Arduino.h>
#include <Wire.h>

#ifdef ESP32
  #include <M5Stack.h>
  #include <WiFi.h>
  
#else
  #include <WiFiNINA.h>
#endif

/* Sensor Libraries */
#ifdef ESP32
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP280.h>
  #include <M5_ENV.h>
  #include <Multichannel_Gas_GMXXX.h>
  DHT12 dht12;
  Adafruit_BMP280 bme;
  GAS_GMXXX<TwoWire> gas;
  static uint8_t recv_cmd[8] = {};
#else
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BMP280.h>
  #include <Multichannel_Gas_GMXXX.h>
  GAS_GMXXX<TwoWire> gas;
  static uint8_t recv_cmd[8] = {};
#endif

#include <ArduinoJson.h>
#include <PubSubClient.h>

void callback(char *topic, byte *payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(mqttserver, 1883, callback, wifiClient);

#ifdef ESP32
  #include <sdfunctions.h>
#endif
#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

void setup() {
  Wire.begin();
  
  #ifdef ESP32
    M5.begin();
    /* Start Grove multichannel Gas sensor */
    gas.begin(Wire, 0x08);
  #else
    gas.begin(Wire, 0x08);
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

  #ifdef ESP32
  if ((WiFi.status() != WL_CONNECTED) && (millis() - oldMillisTWO >= pauseTWO)) {
    DEBUG_INFORMATION_SERIAL.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
 
    oldMillisTWO = millis();
  }
  #endif
  
  askSensors();

  if (millis() - oldMillisONE >= pauseONE) {
    DEBUG_INFORMATION_SERIAL.println("ten seconds passed");
    sendSensors();
    oldMillisONE = millis();
  }

  client.loop();
}