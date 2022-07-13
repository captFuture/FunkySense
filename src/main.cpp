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

#ifdef ESP32
  #include <sdfunctions.h>
  TaskHandle_t SensorTask;
#endif
#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

#ifdef ESP32
  void SensorTaskCode( void * pvParameters ){

    for(;;){
      //DEBUG_INFORMATION_SERIAL.print("SensorTask running on core ");
      //DEBUG_INFORMATION_SERIAL.println(xPortGetCoreID());
      askSensors();
      delay(1000);
    } 
  }
#endif

void setup() {
  #ifdef ESP32
    M5.begin();
    xTaskCreatePinnedToCore(SensorTaskCode, "SensorTask", 10000, NULL, 1, &SensorTask, 0);         
    delay(500); 
    DEBUG_INFORMATION_SERIAL.print("setup() running on core ");
    DEBUG_INFORMATION_SERIAL.println(xPortGetCoreID());
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

  #ifdef ESP32
  if ((WiFi.status() != WL_CONNECTED) && (millis() - oldMillisTWO >= pauseTWO)) {
    DEBUG_INFORMATION_SERIAL.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
 
    oldMillisTWO = millis();
  }
  #endif
  
  #ifdef ESP32
    //use task instead of loop
  #else
    askSensors();
  #endif

  if (millis() - oldMillisONE >= pauseONE) {
    DEBUG_INFORMATION_SERIAL.println("ten seconds passed");
    sendSensors();
    oldMillisONE = millis();
  }

  client.loop();
}