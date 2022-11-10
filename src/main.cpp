#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <globals.h>
#include <Arduino.h>
#include <M5Stack.h>
#include <base64.h>

/* time init - INTERNAL TIME - not used at the moment*/
#include <ESP32Time.h>
struct tm timeinfo;
ESP32Time rtc(3600);

/* time init - unitRTC */
#include "Unit_RTC.h"
Unit_RTC unitRTC;
rtc_time_type RTCtime;
rtc_date_type RTCdate;
char str_buffer[64];

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

#include <LTR390.h>
#define I2C_ADDRESS 0x53
LTR390 ltr390(I2C_ADDRESS);

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
    M5.lcd.setCursor(5, 30);
    M5.Lcd.print("Then open 192.1168.4.1 in Browser");
    //M5.Lcd.qrcode("http://192.168.4.1",50,30,200,6);
  }else{
    M5.lcd.fillScreen(BLACK);
  }
  
}

void setup() {
  M5.begin();            
  M5.Power.begin();       
  M5.lcd.setTextSize(2);  
  Wire.begin();
  unitRTC.begin();
  initializeSD(); 
  readConfig();
  DEBUG_INFORMATION_SERIAL.print("Networkmode: "); DEBUG_INFORMATION_SERIAL.println(config.NETworkmode); 
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
    wm.preloadWiFi(config.ssid, config.password);
    bool res;
    showQrcode(1);
    res = wm.autoConnect(config.clientId);
    if(!res) {
      DEBUG_INFORMATION_SERIAL.println("Failed to connect");
      config.NETworkmode = false;
      showQrcode(0);
    }else {
      DEBUG_INFORMATION_SERIAL.println("WiFi connected");
      DEBUG_INFORMATION_SERIAL.print("IP address: ");
      DEBUG_INFORMATION_SERIAL.println(WiFi.localIP());
      showQrcode(0);
    }
  
    /*configTime(gmtOffset_sec, daylightOffset_sec, config.ntpserver);
    
    if (getLocalTime(&timeinfo)){
      DEBUG_INFORMATION_SERIAL.println("Set time from ntp");
      rtc.setTimeStruct(timeinfo); 
    }else{
      DEBUG_INFORMATION_SERIAL.println("Setting time locally");
      rtc.setTime(00, 00, 00, 1, 1, 2000);
      DEBUG_INFORMATION_SERIAL.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
    }*/
    
    unitRTC.getTime(&RTCtime);
    unitRTC.getDate(&RTCdate);
    DEBUG_INFORMATION_SERIAL.printf("RTC Time Now is %02d:%02d:%02d\n", RTCtime.Hours, RTCtime.Minutes, RTCtime.Seconds); 
    DEBUG_INFORMATION_SERIAL.printf("RTC Date Now is %02d/%02d/%02d\n", RTCdate.Date, RTCdate.Month, RTCdate.Year); 
    
    int mqttport = atoi(config.mqttport);
    client.setServer(config.mqttserver, mqttport);
    client.setCallback(callback);
    initManagedDevice();

  }else{     
    /*
    DEBUG_INFORMATION_SERIAL.println("Setting time locally");
    rtc.setTime(00, 00, 00, 1, 1, 2000);
    DEBUG_INFORMATION_SERIAL.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
    */
    unitRTC.getTime(&RTCtime);
    unitRTC.getDate(&RTCdate);
    DEBUG_INFORMATION_SERIAL.printf("RTC Time Now is %02d:%02d:%02d\n", RTCtime.Hours, RTCtime.Minutes, RTCtime.Seconds); 
    DEBUG_INFORMATION_SERIAL.printf("RTC Date Now is %02d/%02d/%02d\n", RTCdate.Date, RTCdate.Month, RTCdate.Year); 
  }
}

void switchDisplay(int onoff){
  if(onoff == 0){
    M5.Lcd.sleep();
    M5.Lcd.setBrightness(0);
    DEBUG_INFORMATION_SERIAL.print("Display off");
  }else{
    M5.Lcd.wakeup();
    M5.Lcd.setBrightness(200);
    DEBUG_INFORMATION_SERIAL.print("Display on");
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
  pauseONE = atoi(config.pausesend);
  if (millis() - oldMillisONE >= pauseONE) {

    M5.lcd.fillRect(0, 0, 320, 20, BLACK);
    M5.lcd.setCursor(0, 0);
    M5.lcd.println(config.clientId);   

    M5EnvIII();
    AdafruitTSL2591();
    GroveMultiGas();
    //ltr390();
    //printLocalTime();
    printUnitRtcTime();
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
    switchDisplay(1);
    buttonPress = 0;
  }

  if (M5.BtnB.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
  }

  if (M5.BtnC.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
  }

  if (M5.BtnA.pressedFor(5000)) {
    config.NETworkmode = !config.NETworkmode;
    DEBUG_INFORMATION_SERIAL.print("Networkmode: ");
    DEBUG_INFORMATION_SERIAL.println(config.NETworkmode);
    buttonPress = 0;
    delay(2000);
  }

  /*if (M5.BtnC.pressedFor(2000)) {
    WiFiManager wm;
    wm.setConfigPortalTimeout(timeout);
    showQrcode(1);
    if (!wm.startConfigPortal(config.clientId)) {
      DEBUG_INFORMATION_SERIAL.println("failed to connect and hit timeout");
      delay(3000);
      ESP.restart();
    }

  }*/
  
  if (M5.BtnB.pressedFor(5000)) {
    clearSDcontent();
    buttonPress = 0;
    delay(2000);
  }

  if (M5.BtnC.pressedFor(5000)) {
    writeSDcontent();
    buttonPress = 0;
    delay(2000);
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


