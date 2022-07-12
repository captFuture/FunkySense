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
PubSubClient client("192.168.0.26", 1883, callback, wifiClient);

#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);
  DEBUG_ERROR_SERIAL.println("This is an error message");
  DEBUG_WARNING_SERIAL.println("This is a warning message");
  DEBUG_INFORMATION_SERIAL.println("Some output value");
  connectWifi();
  initManagedDevice();
}

void loop() {
  //time_now = millis();
  
  askSensors();
  
  //ARNO: WHILE IS BLOCKING, IF IS NOT BLOCKING
  //ARNO: =====================================
  //while(millis() < time_now + period){    
    // add the code you want to keep running here
    //DEBUG_INFORMATION_SERIAL.print("one second passed");
    //sendSensors();
  // }
   

  if(millis() >= time_now + period)
  {
    sendSensors();
    time_now += period;
    DEBUG_INFORMATION_SERIAL.println("one second passed");
  }
}