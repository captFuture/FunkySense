void initializeSD(){

    if (!SD.begin()) {
        SDinserted = false;
        DEBUG_ERROR_SERIAL.println("SDCard failed, or not present"); 
    }else{
        SDinserted = true;
        DEBUG_INFORMATION_SERIAL.println("SDCard present"); 
    }
    if(SDinserted){
        if (SD.exists("/sensordata.csv")) {
            DEBUG_INFORMATION_SERIAL.println("sensordata.csv exists.");
            #ifdef ESP32
                File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
            #else
                File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
            #endif
            sensorFile.println("exists NEW DATA ----------");
            sensorFile.close();
        } else {
            DEBUG_ERROR_SERIAL.println("sensordata.csv doesn't exist.");
            #ifdef ESP32
                File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
            #else
                File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
            #endif
            sensorFile.println("does not exist NEW FILE ----------");
            sensorFile.close();
        }
    }
}

void writePayload(){
    #ifdef ESP32
        File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
    #else
        File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
    #endif
    //sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues1.one, SensorValues1.two, SensorValues1.three, SensorValues1.four, SensorValues1.five, SensorValues1.six, SensorValues1.seven, SensorValues1.eight, SensorValues1.nine, SensorValues1.ten, SensorValues.rssi );
    DEBUG_INFORMATION_SERIAL.print("Writing Sensordata to SD: ");
    DEBUG_INFORMATION_SERIAL.println(sdmsg);
    sensorFile.println(sdmsg);
    sensorFile.close();
}

void clearSDcontent(){
    SD.remove("/sensordata.csv");
    File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
    DEBUG_INFORMATION_SERIAL.println("Clearing SDcard");
    sensorFile.close();
}