
/*
  The circuit:
  - Arduino Nano 33 BLE Sense
*/

#include <Arduino_LSM9DS1.h>
#include <Arduino_APDS9960.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <ArduinoBLE.h>
#include <MadgwickAHRS.h>
#include <Multichannel_Gas_GMXXX.h>
#include "ServiceData.h"
//#include "Grove_MultichannelGasSensor.h"

///////////////////////////

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
GAS_GMXXX<TwoWire> gas;


Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)



//The nano 33 accel and gyro sample rate is 104 Hz - DONT CHANGE.
const float sampleRate = 104.0;
long lastSecond; //The millis counter to see when a second rolls by

//Sesor Data Varialbes
void(* resetFunc) (void) = 0;

Madgwick filter;

BLEService IMUService(IMU_SERVICE_UUID);
BLEService RGBService(RGB_SERVICE_UUID);
BLEService ENVService(ENV_SERVICE_UUID);
BLEService DISTService(DIST_SERVICE_UUID);
BLEService UVService(UV_SERVICE_UUID);
BLEService TSLService(TSL_SERVICE_UUID);
BLEService GASService(GAS_SERVICE_UUID);

BLEStringCharacteristic IMUCharacter(IMU_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);
BLEStringCharacteristic RGBCharacter(RGB_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);
BLEStringCharacteristic ENVCharacter(ENV_CHAR_UUID, BLERead | BLEWrite|BLENotify,70);
BLEStringCharacteristic DISTCharacter(DIST_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);
BLEStringCharacteristic UVCharacter(UV_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);
BLEStringCharacteristic TSLCharacter(TSL_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);
BLEStringCharacteristic GASCharacter(GAS_CHAR_UUID, BLERead | BLEWrite|BLENotify,50);


BLEDescriptor IMUdescriptor (IMU_CHAR_UUID,"THESE ARE IMU VALS XYZ");
BLEDescriptor RGBdescriptor (RGB_CHAR_UUID,"THESE ARE COLOR VALS RGV");
BLEDescriptor ENVdescriptor (ENV_CHAR_UUID,"THESE ARE ENV VALS PRESURE,TEMP,HUMIDY");
BLEDescriptor DISTdescriptor (DIST_CHAR_UUID,"THESE IS DISTANCE VAL");
BLEDescriptor UVdescriptor (UV_CHAR_UUID,"THESE IS UV LIGHT VAL");
BLEDescriptor TSLdescriptor (TSL_CHAR_UUID,"THESE IS LUMINOSITY LIGHT VAL");
BLEDescriptor GASdescriptor (GAS_CHAR_UUID,"THESE IS GAS PPM VAL");




void PublishIMU()
{
  float AccelX,AccelY,AccelZ ;
  float GyroX,GyroY,GyroZ ;
  float MagX,MagY,MagZ;
  String accelMsg,magMsg,gyroMsg,orientMsg;
  float roll, pitch, heading;
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(AccelX, AccelY, AccelZ);
        accelMsg = String("AccelXYZ") + "   "+ String(AccelX) + "   " + String(AccelY) + "   " + String(AccelZ);
        Serial.println(accelMsg);
    }
    if (IMU.magneticFieldAvailable()) {
        IMU.readMagneticField(MagX, MagY, MagZ);
        magMsg = String("MagXYZ") + "   "+ String(MagX) + "   " + String(MagY) + "   " + String(MagZ);
        Serial.println (magMsg);
    }
    if (IMU.gyroscopeAvailable())
    {
         IMU.readGyroscope(GyroX,GyroY,GyroZ);
         gyroMsg = String("GyroFieldXYZ") + "   "+ String(GyroX) + "   " + String(GyroY) + "   " + String(GyroZ);
         Serial.println (gyroMsg);
    }
      //filter.update( GyroX,GyroY,GyroZ,AccelX,AccelY,AccelZ, MagX,MagY,MagZ);
      filter.updateIMU( GyroX,GyroY,GyroZ,AccelX,AccelY,AccelZ);
      roll = filter.getRoll();
      pitch = filter.getPitch();
      heading = filter.getYaw();
      orientMsg =  String("Yaw|Pitch|Roll (deg)") + "   "+ String(heading) + "   " + String(pitch) + "   " + String(roll);
      IMUCharacter.writeValue(orientMsg);
      Serial.println(orientMsg);
      delay(10);
}
void PublishRGB()
{
  String colorMsg;
  int r, g, b;
  if (APDS.colorAvailable()){
    APDS.readColor(r, g, b);
    colorMsg = String("COLOR_RGB") + "   "+ String(r) + "   " + String(g) + "   " + String(b);
    Serial.println (colorMsg);
    RGBCharacter.writeValue(colorMsg);
  }
}
  
void PublicENV()
{ 
    float pressure,temperature,humidity;
    String envMsg;
    temperature = HTS.readTemperature();
    humidity    = HTS.readHumidity();
    pressure = BARO.readPressure();
    

    envMsg = String("TEMP (°C)") + "   " + String(temperature) +  "   "+ "Humidity (%)" + "   " + String(humidity) + "   " + "Presure (kPa)" + "   " + String(pressure);
    Serial.println(envMsg);
    ENVCharacter.writeValue(envMsg);
    
  }
void PublisgDIST()
{
      String distMsg;
      int proximity;
      if (APDS.proximityAvailable()) 
      {
        // read the proximity
        // - 0   => close
        // - 255 => far
        // - -1  => error
        proximity = APDS.readProximity();
        distMsg  = String("PROXOMITY (range)") + String(proximity);
        Serial.println(distMsg);
        DISTCharacter.writeValue(distMsg);
    }
  }
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------UV Sensor--------------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------


 
 void PublishUV()
 {
  
  String uvMsg;
  int UVLight;

  int analogApin = 0; //define OUT signal pin
  
  pinMode (analogApin, INPUT);
  UVLight = analogRead(analogApin);
  uvMsg = String("UV VALUE://") + " " + String (UVLight); 
  
  Serial.println(uvMsg);
  UVCharacter.writeValue(uvMsg);
  
  
  }
  

 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------Light Sensor--------------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

 
  void PublishTSL()
  {
    String TSLMsg;
   
    String Gain;
    String IntegrationTime;
    
//-----------------------------------------------------------------------------------------------------------------
//Configure TSL SENSOR
//-----------------------------------------------------------------------------------------------------------------

    // You can change the gain on the fly, to adapt to brighter/dimmer light situations
    tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
    //tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
    //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
    // Changing the integration time gives you a longer time over which to sense light
    // longer timelines are slower, but are good in very low light situtations!
    tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
    // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

    tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
   {
    case TSL2591_GAIN_LOW:
      Gain = String("1x (LOW)");
      break;
    case TSL2591_GAIN_MED:
      Gain = String("25x (Medium)");
      break;
    case TSL2591_GAIN_HIGH:
      Gain = String("428x (High)");    
      break;
    case TSL2591_GAIN_MAX:
      Gain = String("9876x (Max)");   
      break;
  }
  //-------------------------------------------------------------------------------------------------------------------
  //implementation of simpleRead() function if not used deactivate this code from the file 210308_tsl2591_Light-Sensor
 //--------------------------------------------------------------------------------------------------------------------
    // Simple data read example. Just read the infrared, fullspecrtrum diode 
  // or 'visible' (difference between the two) channels.
  // This can take 100-600 milliseconds! Uncomment whichever of the following you want to read
  //uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
  uint16_t x = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
  uint16_t y = tsl.getLuminosity(TSL2591_INFRARED);

 
  TSLMsg = String("Luminosity: ") + String (x)+ " " + String("Infrared: ") + String (y); 
    Serial.println(TSLMsg);
  TSLCharacter.writeValue(TSLMsg);

  //-------------------------------------------------------------------------------------------------------------------
  //implementation of advancedeRead() function if not used deactivate this code from the file 210308_tsl2591_Light-Sensor
 //--------------------------------------------------------------------------------------------------------------------

   // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  /*
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
  Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
  Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
  Serial.print(F("Lux: ")); Serial.println(tsl.calculateLux(full, ir), 6);
  */
  
  
    
    

  }



  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------Gas Sensor-----------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
   

void PublishGAS()
{
  String gasMsg;
  

  unsigned int no2, c2h5ch, voc, co;

  if (millis() - lastSecond >= 1000)
  {  co = gas.getGM702B();
     no2 = gas.getGM102B();
     c2h5ch = gas.getGM302B();
     voc = gas.getGM502B();
     gasMsg = String("CO: ")+ " " + String(co)+ " " + String("NO2: ")+ " " + String(no2) + " " + String("Alc: ")+ " " + String(c2h5ch)+ " " + String("VOC: ")+ " " + String(voc)  ;
   Serial.println(gasMsg);
   GASCharacter.writeValue(gasMsg);
  
    
    }

  
   

 
   
  
  
  }






void SetupBLE()
{
  while (!BLE.begin()) 
  {Serial.println("starting BLE ");}
  BLE.setLocalName(DEVICE_NAME);

  BLE.setAdvertisedService(IMUService);
  BLE.setAdvertisedService(RGBService);
  BLE.setAdvertisedService(ENVService);
  BLE.setAdvertisedService(DISTService);
  BLE.setAdvertisedService(UVService);
  BLE.setAdvertisedService(TSLService);
  BLE.setAdvertisedService(GASService);

  IMUCharacter.addDescriptor(IMUdescriptor);
  RGBCharacter.addDescriptor(RGBdescriptor);
  ENVCharacter.addDescriptor(ENVdescriptor);
  DISTCharacter.addDescriptor(DISTdescriptor);
  UVCharacter.addDescriptor(UVdescriptor);
  TSLCharacter.addDescriptor(TSLdescriptor);
  GASCharacter.addDescriptor(GASdescriptor);

  IMUService.addCharacteristic(IMUCharacter);
  RGBService.addCharacteristic(RGBCharacter);
  ENVService.addCharacteristic(ENVCharacter);
  DISTService.addCharacteristic(DISTCharacter);
  UVService.addCharacteristic(UVCharacter);
  TSLService.addCharacteristic(TSLCharacter);
  GASService.addCharacteristic(GASCharacter);

  BLE.addService(IMUService);
  BLE.addService(RGBService);
  BLE.addService(ENVService);
  BLE.addService(DISTService);
  BLE.addService(UVService);
  BLE.addService(TSLService);
  BLE.addService(GASService);

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");

  BLE.advertise();  
}
BLEDevice ConnectToCentral()
{
  BLEDevice central = BLE.central();
  while (!central.connected())
  {
    central = BLE.central();
    Serial.println(BLE.address());
    BLE.setDeviceName(DEVICE_NAME);
    BLE.setLocalName("Arduino Nano 33 BLE (Vibrant_Fields)");
    BLE.advertise();
    Serial.println("- Discovering central device...");
    delay(500);
  }
  return central;
  
}

bool BoardSesorsStartup()
{
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");

  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" uT");
  Serial.println();
  Serial.println("Magnetic Field in uT");
  Serial.println("X\tY\tZ");
  return true;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  BoardSesorsStartup();
  SetupBLE();
  filter.begin(sampleRate);
  gas.begin(Wire,0x08);
  
}

void loop() {
  
  BLEDevice central = ConnectToCentral();
  while (central.connected())
  {
    PublishIMU();
    PublicENV();
    PublishRGB();
    PublisgDIST();
    PublishUV();
    
    PublishTSL();
    PublishGAS();
    Serial.println("************************************************");
    delay(500);
  }
  Serial.println("Dev Disconnected");
  resetFunc();
}
