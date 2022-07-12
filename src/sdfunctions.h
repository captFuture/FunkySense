void initializeSD(){

    if (!SD.begin()) {
        SDpresent = false;
        DEBUG_ERROR_SERIAL.println("SDCard failed, or not present"); 
    }else{
        SDpresent = true;
        DEBUG_INFORMATION_SERIAL.println("SDCard present"); 
    }
    
    if (SD.exists("/sensordata.csv")) {
        DEBUG_INFORMATION_SERIAL.println("sensordata.csv exists.");
        File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
    } else {
        DEBUG_ERROR_SERIAL.println("sensordata.csv doesn't exist.");
        File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
        sensorFile.println("NEW DATA ----------");
        //myFile.close();
    }

}

void writePayload(){
    File sensorFile = SD.open("/sensordata.csv", FILE_WRITE);
    sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues.rssi );
    DEBUG_INFORMATION_SERIAL.println("Writing Sensordata to SD");
    DEBUG_INFORMATION_SERIAL.println(sdmsg);
    sensorFile.println(sdmsg);
}