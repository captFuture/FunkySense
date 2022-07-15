#include <globals.h>
#include <Arduino.h>
#include <Wire.h>

#ifdef ESP32
  #include <M5Stack.h>
  #include <WiFi.h>
  #include <base64.h>
#else
  #include <WiFiNINA.h>
  #include <SD.h>
  #include "base64.hpp"
#endif

/* Sensor Libraries */
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>
  #include <Adafruit_TSL2591.h>
  #include <Multichannel_Gas_GMXXX.h>
  

  Adafruit_BME280 bme;
  GAS_GMXXX<TwoWire> gas;
  static uint8_t recv_cmd[8] = {};
  Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
  

  //#include <M5_ENV.h>
  //#include <Adafruit_BMP280.h>
  //DHT12 dht12;
  //Adafruit_BMP280 bmp;
  //#include <Adafruit_VCNL4040.h>
  //Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();


#include <ArduinoJson.h>
#include <PubSubClient.h>

void callback(char *topic, byte *payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(mqttserver, 1883, callback, wifiClient);

#include <sdfunctions.h>
#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>
#include <sensorinit.h>

void setup() {
  Wire.begin();
  
  #ifdef ESP32
    M5.begin();
    M5.Lcd.writecommand(ILI9341_DISPOFF);
    M5.Lcd.setBrightness(0);          
  #else
    
  #endif

  gas.begin(Wire, 0x08);

  Serial.begin(115200);
  while (!Serial) { delay(1); }

  if(NETworkmode){
    connectWifi();
    initManagedDevice();
  }
  
  #ifdef SAVE_SD
    initializeSD();
  #endif
  
  initSensors();
  pinMode(WaveshareUV_Pin,INPUT);
}

void loop() {
  if(NETworkmode){
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
  }
  
  askSensors();

  if (millis() - oldMillisONE >= pauseONE) {
    if(NETworkmode){
      sendSensors();
    }
    saveSensors();
    oldMillisONE = millis();
  }

  client.loop();
}