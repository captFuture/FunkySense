void initSensors(){
    while (!bme.begin(0x76)) {
        DEBUG_ERROR_SERIAL.println("Could not find a valid GY-BME280 sensor, check wiring!");
    }

    /* while (!bmp.begin(0x76)) {
        DEBUG_ERROR_SERIAL.println("Could not find a valid BMP280 sensor, check wiring!");
    }*/

    /*while (!vcnl4040.begin()) {
        Serial.println("Couldn't find VCNL4040 chip");
    }
    Serial.println("Found VCNL4040 chip");
    vcnl4040.setProximityLEDCurrent(VCNL4040_LED_CURRENT_200MA);
    vcnl4040.setProximityLEDDutyCycle(VCNL4040_LED_DUTY_1_40);
    vcnl4040.setAmbientIntegrationTime(VCNL4040_AMBIENT_INTEGRATION_TIME_80MS);
    vcnl4040.setProximityIntegrationTime(VCNL4040_PROXIMITY_INTEGRATION_TIME_8T);
    vcnl4040.setProximityHighResolution(false);
    */

    if (!tsl.begin()) 
    {
        DEBUG_ERROR_SERIAL.println("Could not find a valid Adafruit_TSL2591 sensor, check wiring!");
    } 

}