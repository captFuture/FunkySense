void M5EnvSensor(){
    #ifdef ESP32
        while (!bme.begin(0x76)) {
            DEBUG_ERROR_SERIAL.println("Could not find a valid BMP280 sensor, check wiring!");
        }
        SensorValues.one = dht12.readTemperature(); // float temperature
        SensorValues.two = dht12.readHumidity();    // float humidity
    SensorValues.three = bme.readPressure();    // float pressure
    #endif
    }

void GroveMultiGas(){
    uint8_t len = 0;
    uint8_t addr = 0;
    uint8_t i;
    uint32_t val = 0;
    SensorValues.four = gas.measure_NO2();     // float NO2
    SensorValues.five = gas.measure_C2H5OH();      // float C2H5OH
    SensorValues.six = gas.measure_VOC();      // float VOC
    SensorValues.seven = gas.measure_CO();   // float CO

    //DEBUG_INFORMATION_SERIAL.println(gas.measure_NO2());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_C2H5OH());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_VOC());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_CO());

} 


void askSensors(){
    //DEBUG_INFORMATION_SERIAL.println("Sensorloop");
    SensorValues.sensor = "001";
    SensorValues.one = 0.0; // float temperature
    SensorValues.two = 0.0;    // float humidity
    SensorValues.three = 0.0;  // float pressure
    SensorValues.four = 0.0;     // int NO2
    SensorValues.five = 0.0;      // int C2H5OH
    SensorValues.six = 0.0;       // int VOC
    SensorValues.seven = 0.0;     // int CO
    SensorValues.eight = 0.0;     // float 
    SensorValues.nine = 0.0;      // float 
    SensorValues.ten = 0.0;      // float 
    SensorValues.eleven = 0;   // long 
    
    SensorValues.rssi = WiFi.RSSI();

    #ifdef ESP32
        M5EnvSensor();
        GroveMultiGas();
    #else
        GroveMultiGas();
    #endif
}
