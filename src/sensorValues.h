void M5EnvSensor(){
    #ifdef ESP32
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
    SensorValues.five = gas.measure_C2H5OH();  // float C2H5OH
    SensorValues.six = gas.measure_VOC();      // float VOC
    SensorValues.seven = gas.measure_CO();     // float CO

    //DEBUG_INFORMATION_SERIAL.println(gas.measure_NO2());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_C2H5OH());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_VOC());
    //DEBUG_INFORMATION_SERIAL.println(gas.measure_CO());

} 

void AdafruitVCNL4040(){
    #ifdef ESP32
        SensorValues.eight = vcnl4040.getProximity();
        SensorValues.nine = vcnl4040.getLux();
        SensorValues.ten = vcnl4040.getWhiteLight();

        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getProximity());
        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getLux());
        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getWhiteLight());
    #endif
}


void askSensors(){
    SensorValues.sensor = "001";
    SensorValues.one = 0.0;     // float temperature
    SensorValues.two = 0.0;     // float humidity
    SensorValues.three = 0.0;   // float pressure
    SensorValues.four = 0.0;    // int NO2
    SensorValues.five = 0.0;    // int C2H5OH
    SensorValues.six = 0.0;     // int VOC
    SensorValues.seven = 0.0;   // int CO
    SensorValues.eight = 0;     // int Proximity
    SensorValues.nine = 0;      // int lux
    SensorValues.ten = 0;       // int whitelight
    SensorValues.rssi = WiFi.RSSI();

    SensorValues1.sensor = "001";
    SensorValues1.one = 0.0;     // float
    SensorValues1.two = 0.0;     // float 
    SensorValues1.three = 0.0;   // float 
    SensorValues1.four = 0.0;    // int 
    SensorValues1.five = 0.0;    // int
    SensorValues1.six = 0.0;     // int
    SensorValues1.seven = 0.0;   // int 
    SensorValues1.eight = 0;     // int 
    SensorValues1.nine = 0;      // int 
    SensorValues1.ten = 0;       // int 

    #ifdef ESP32
        M5EnvSensor();
        GroveMultiGas();
        AdafruitVCNL4040();
    #else
        GroveMultiGas();
    #endif
}
