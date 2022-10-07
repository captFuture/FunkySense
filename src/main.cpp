#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <globals.h>
#include <Arduino.h>

#include <M5Core2.h>

#include <base64.h>

/* time init */
#include <ESP32Time.h>
struct tm timeinfo;
ESP32Time rtc(3600);

/* wifi and ntp */
#include <SPI.h>
#include <time.h>
#include <WiFiUdp.h>
#include <timeclient.h>

/* wifimanager */
#include <WiFiManager.h>
void callback(char* topic, byte* message, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(wifiClient);

/* additional */
#include <sdfunctions.h>
#include <mqttfunctions.h>

/* Sensor Libraries */
#include <M5_ENV.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>
#include <Multichannel_Gas_GMXXX.h>

/* Sensor Inits */
SHT3X sht30;
QMP6988 qmp6988;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
GAS_GMXXX<TwoWire> gas;

#include <sensorfunctions.h>

void showQrcode(int showhide){
  if(showhide == 1){
    M5.lcd.fillScreen(BLACK);
    M5.lcd.setCursor(5, 5);
    M5.Lcd.printf("connect to Wifi: %s", config.clientId);
    M5.Lcd.qrcode("http://192.168.4.1",50,30,200,6);
  }else{
    M5.lcd.fillScreen(BLACK);
  }
}

void setup() {
  M5.begin();            
  M5.lcd.setTextSize(2);  
  Wire.begin();

  initializeSD(); 
  readConfig();
  DEBUG_SENSOR_SERIAL.print("Networkmode: "); DEBUG_SENSOR_SERIAL.println(config.NETworkmode); 
  qmp6988.init();
  tsl.begin();
  gas.begin(Wire, 0x08);
  M5.lcd.println(F("ANNA - ENV"));
  Serial.begin(115200);
  


  if(config.NETworkmode){
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    wm.setDebugOutput(true);
    wm.setConfigPortalTimeout(timeout);
    if(SDinserted == true){
      //wm.preloadWiFi(config.ssid, config.password);
    }
    bool res;
    showQrcode(1);
    res = wm.autoConnect(config.clientId);
    if(!res) {
      DEBUG_SENSOR_SERIAL.println("Failed to connect");
      config.NETworkmode = false;
      showQrcode(0);
    }else {
      DEBUG_SENSOR_SERIAL.println("WiFi connected");
      DEBUG_SENSOR_SERIAL.print("IP address: ");
      DEBUG_SENSOR_SERIAL.println(WiFi.localIP());
      showQrcode(0);
    }
  
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    //configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
    
    if (getLocalTime(&timeinfo)){
      DEBUG_SENSOR_SERIAL.println("Set time from ntp");
      rtc.setTimeStruct(timeinfo); 
    }else{
      DEBUG_SENSOR_SERIAL.println("Setting time locally");
      rtc.setTime(00, 10, 12, 1, 1, 2000);
      DEBUG_SENSOR_SERIAL.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
    }

    client.setServer(config.mqttserver, 1883);
    client.setCallback(callback);
    initManagedDevice();

  }else{     
    DEBUG_SENSOR_SERIAL.println("Setting time locally");
    rtc.setTime(00, 10, 12, 1, 1, 2000);
    DEBUG_SENSOR_SERIAL.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
  }
}

void switchDisplay(int onoff){
  if(onoff == 0){
    M5.Lcd.sleep();
    M5.Lcd.setBrightness(0);
    DEBUG_SENSOR_SERIAL.print("Display off");
  }else{
    M5.Lcd.wakeup();
    M5.Lcd.setBrightness(200);
    DEBUG_SENSOR_SERIAL.print("Display on");
  }
}

void showNetStatus(){
  if(config.NETworkmode == true){
    M5.Lcd.drawRect(295, 5, 20, 20, YELLOW);
    M5.Lcd.fillRect(296, 6, 18, 18, GREEN);
  }else{
    M5.Lcd.drawRect(295, 5, 20, 20, YELLOW);
    M5.Lcd.fillRect(296, 6, 18, 18, RED);
  }
}

void showSDStatus(){
  if(SDinserted == true){
    M5.Lcd.drawRect(295, 30, 20, 20, YELLOW);
    M5.Lcd.fillRect(296, 31, 18, 18, GREEN);
  }else{
    M5.Lcd.drawRect(295, 30, 20, 20, YELLOW);
    M5.Lcd.fillRect(296, 31, 18, 18, RED);
  }
}
  

void loop() {
  M5.update();
  if (millis() - oldMillisONE >= pauseONE) {

    M5.lcd.fillRect(0, 0, 320, 20, BLACK);
    M5.lcd.setCursor(0, 0);
    M5.lcd.println(config.clientId);   

    M5EnvIII();
    AdafruitTSL2591();
    GroveMultiGas();
    printLocalTime();
    writePayload();
    showNetStatus();
    showSDStatus();
    if(config.NETworkmode){
      sendSensors();
    }
    
    oldMillisONE = millis();
  }
  if (millis() - oldMillisTWO >= pauseTWO) {
    // some
    oldMillisTWO = millis();
    buttonPress = buttonPress+1;
  }

  if (M5.BtnA.wasPressed()) {
    config.NETworkmode = !config.NETworkmode;
  }
  if (M5.BtnB.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
  }

  if (M5.BtnC.wasPressed()) {

  }  
  if (M5.BtnC.pressedFor(2000)) {
    WiFiManager wm;
    wm.setConfigPortalTimeout(timeout);
    showQrcode(1);
    if (!wm.startConfigPortal(config.clientId)) {
      DEBUG_SENSOR_SERIAL.println("failed to connect and hit timeout");
      delay(3000);
      ESP.restart();
    }

  }
  
  if(buttonPress >= 2){
    switchDisplay(0);
    buttonPress = 0;
  }

  if(config.NETworkmode){
    if (!client.connected()) {
      DEBUG_INFORMATION_SERIAL.println("Not connected - go to reconnect");
      reconnect();
    }
  }
  client.loop();
}


