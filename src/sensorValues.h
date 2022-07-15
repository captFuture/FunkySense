void AdafruitBME280(){
        SensorValues.one = bme.readTemperature();           // float temperature
        SensorValues.two = bme.readPressure() / 100;        // float pressure
        SensorValues.three = bme.readHumidity();            // float humidity
        SensorValues.four = bme.readAltitude(1013.25);      // float altitude

        DEBUG_SENSOR_SERIAL.print("Temp: "); DEBUG_SENSOR_SERIAL.println(bme.readTemperature());
        DEBUG_SENSOR_SERIAL.print("Pres: "); DEBUG_SENSOR_SERIAL.println(bme.readPressure()/100);
        DEBUG_SENSOR_SERIAL.print("Hum: "); DEBUG_SENSOR_SERIAL.println(bme.readHumidity());
        DEBUG_SENSOR_SERIAL.print("Alt: "); DEBUG_SENSOR_SERIAL.println(bme.readAltitude(1013.25));

    }    

void GroveMultiGas(){
    uint8_t len = 0;
    uint8_t addr = 0;
    uint8_t i;
    uint32_t val = 0;
    
    SensorValues.five = gas.measure_C2H5OH();  // int C2H5OH
    SensorValues.six = gas.measure_VOC();      // int VOC
    SensorValues.seven = gas.measure_CO();     // int CO
    SensorValues.eight = gas.measure_NO2();     // int NO2

    DEBUG_SENSOR_SERIAL.print("C2H5OH: "); DEBUG_SENSOR_SERIAL.println(gas.measure_C2H5OH());
    DEBUG_SENSOR_SERIAL.print("VOC: "); DEBUG_SENSOR_SERIAL.println(gas.measure_VOC());
    DEBUG_SENSOR_SERIAL.print("CO: "); DEBUG_SENSOR_SERIAL.println(gas.measure_CO());
    DEBUG_SENSOR_SERIAL.print("NO2: "); DEBUG_SENSOR_SERIAL.println(gas.measure_NO2());

} 

void WaveshareUV(){
    uvvalue = analogRead(WaveshareUV_Pin);
    SensorValues.nine = uvvalue;                             // int uv
    DEBUG_SENSOR_SERIAL.print("UV: ");DEBUG_SENSOR_SERIAL.println(analogRead(36));

}  


void AdafruitTSL2591(){
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full, visible;
    ir = lum >> 16;
    full = lum & 0xFFFF;
    visible = full -ir;

    SensorValues1.one = ir;                             // int ir
    SensorValues1.two = full;                           // int full
    SensorValues1.three = visible;                      // int visible
    SensorValues1.four = tsl.calculateLux(full, ir);    // float LUX

     DEBUG_SENSOR_SERIAL.print("IR: ");DEBUG_SENSOR_SERIAL.println(ir);
     DEBUG_SENSOR_SERIAL.print("Full: ");DEBUG_SENSOR_SERIAL.println(full);
     DEBUG_SENSOR_SERIAL.print("visible: ");DEBUG_SENSOR_SERIAL.println(visible);
     DEBUG_SENSOR_SERIAL.print("LuX: ");DEBUG_SENSOR_SERIAL.println(tsl.calculateLux(full, ir));

    }

void askSensors(){
    SensorValues.sensor = "001";
    SensorValues.one = 0.000000;     // float temperature
    SensorValues.two = 0.000000;     // float pressure
    SensorValues.three = 0.000000;   // float humidity
    SensorValues.four = 0.000000;    // float altitude

    SensorValues.five = 0;    // int C2H5OH
    SensorValues.six = 0;     // int VOC
    SensorValues.seven = 0;   // int CO
    SensorValues.eight = 0;   // int NO2

    SensorValues.nine = 0;      // FREI
    SensorValues.ten = 0;       // FREI 
    SensorValues.rssi = WiFi.RSSI();

    SensorValues1.sensor = "001";
    SensorValues1.one = 0;             // int infrared
    SensorValues1.two = 0;             // int full
    SensorValues1.three = 0;           // int visible
    SensorValues1.four = 0.000000;     // float LUX

    SensorValues1.five = 0;    // FREI
    SensorValues1.six = 0;     // FREI
    SensorValues1.seven = 0;   // FREI 
    SensorValues1.eight = 0;     // FREI 
    
    SensorValues1.nine = 0;      // FREI 
    SensorValues1.ten = 0;       // FREI 
    SensorValues1.rssi = WiFi.RSSI();

    #ifdef ESP32
        //M5EnvSensor();        // not on actual project
        //AdafruitVCNL4040();   // not on actual project   
        GroveMultiGas();        
        AdafruitBME280();
        AdafruitTSL2591();
        WaveshareUV();
    #else
        GroveMultiGas();
        AdafruitBME280();
        AdafruitTSL2591();
    #endif
}


/*void AdafruitVCNL4040(){
    #ifdef ESP32
        SensorValues.eight = vcnl4040.getProximity();
        SensorValues.nine = vcnl4040.getLux();
        SensorValues.ten = vcnl4040.getWhiteLight();

        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getProximity());
        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getLux());
        //DEBUG_INFORMATION_SERIAL.println(vcnl4040.getWhiteLight());
    #endif
}*/

/*void M5EnvSensor(){
    #ifdef ESP32
        SensorValues.one = dht12.readTemperature(); // float temperature
        SensorValues.two = dht12.readHumidity();    // float humidity
        SensorValues.three = bmp.readPressure();    // float pressure
    #endif
    }*/