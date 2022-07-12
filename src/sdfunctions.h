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
            File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
            sensorFile.println("exists NEW DATA ----------");
            sensorFile.close();
        } else {
            DEBUG_ERROR_SERIAL.println("sensordata.csv doesn't exist.");
            File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
            sensorFile.println("does not exist NEW FILE ----------");
            sensorFile.close();
        }
    }
}

void writePayload(){
    File sensorFile = SD.open("/sensordata.csv", FILE_APPEND);
    sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues.rssi );
    DEBUG_INFORMATION_SERIAL.print("Writing Sensordata to SD: ");
    DEBUG_INFORMATION_SERIAL.println(sdmsg);
    sensorFile.println(sdmsg);
    sensorFile.close();
}

void clearSDcontent(){
    File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
    DEBUG_INFORMATION_SERIAL.println("Clearing SDcard");
    sensorFile.close();
}