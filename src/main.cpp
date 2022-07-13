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

#ifdef ESP32
  #include <sdfunctions.h>
#endif
#include <setupwifi.h>
#include <mqttfunctions.h>
#include <sensorValues.h>
#include <sensorinit.h>

void setup() {
  Wire.begin();
  
  #ifdef ESP32
    M5.begin();
  #else
    
  #endif

  gas.begin(Wire, 0x08);

  Serial.begin(115200);
  while (!Serial) { delay(1); }

  connectWifi();
  initManagedDevice();

  #ifdef SAVE_SD
    initializeSD();
  #endif
  
  initSensors();
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