void initializeSD(){

    if (!SD.begin()) {
        SDinserted = false;
        DEBUG_ERROR_SERIAL.println("SDCard failed, or not present"); 
    }else{
        SDinserted = true;
        DEBUG_INFORMATION_SERIAL.println("SDCard present"); 
    }
    if(SDinserted){
        if (SD.exists("sensor.csv")) {
            DEBUG_INFORMATION_SERIAL.println("sensor.csv exists.");
            #ifdef ESP32
                File sensorFile = SD.open("sensor.csv", FILE_APPEND);
            #else
                File sensorFile = SD.open("sensor.csv", FILE_WRITE);
            #endif
            sensorFile.println("exists NEW DATA ----------");
            sensorFile.close();
        } else {
            DEBUG_ERROR_SERIAL.println("sensor.csv doesn't exist.");
            #ifdef ESP32
                File sensorFile = SD.open("sensor.csv", FILE_APPEND);
                int written = sensorFile.println("does not exist NEW FILE ----------");
                DEBUG_INFORMATION_SERIAL.print(written);
                sensorFile.close();
            #else
                File sensorFile = SD.open("sensor.csv", FILE_WRITE);
                int written = sensorFile.println("does not exist NEW FILE ----------");
                DEBUG_INFORMATION_SERIAL.print(written);

                sensorFile.close();

                /* File myFile;
                myFile = SD.open("sensor.csv", FILE_WRITE);
                // if the file opened okay, write to it:
                if (myFile) {
                    Serial.print("Writing sensor.csv...");
                    myFile.println("testing 1, 2, 3.");
                    // close the file:
                    myFile.close();
                    Serial.println("done.");
                } else {
                    // if the file didn't open, print an error:
                    Serial.println("error opening sensor.csv");
                }


                myFile = SD.open("sensor.csv");
                if (myFile) {
                    Serial.println("sensor.csv:");

                    // read from the file until there's nothing else in it:
                    while (myFile.available()) {
                    Serial.write(myFile.read());
                    }
                    // close the file:
                    myFile.close();
                } else {
                    // if the file didn't open, print an error:
                    Serial.println("error opening sensor.csv");
                }*/
            #endif

        }
    }
}

void writePayload(){
    #ifdef ESP32
        File sensorFile = SD.open("sensor.csv", FILE_APPEND);
    #else
        File sensorFile = SD.open("sensor.csv", FILE_WRITE);
    #endif
    //sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues1.one, SensorValues1.two, SensorValues1.three, SensorValues1.four, SensorValues1.five, SensorValues1.six, SensorValues1.seven, SensorValues1.eight, SensorValues1.nine, SensorValues1.ten, SensorValues.rssi );
    DEBUG_INFORMATION_SERIAL.print("Writing Sensordata to SD: ");
    DEBUG_INFORMATION_SERIAL.println(sdmsg);

    int written = sensorFile.println(sdmsg);
    DEBUG_INFORMATION_SERIAL.print(written);
    sensorFile.close();
}

void clearSDcontent(){
    SD.remove("sensor.csv");
    File sensorFile = SD.open("sensor.csv", FILE_WRITE);
    DEBUG_INFORMATION_SERIAL.println("Clearing SDcard");
    sensorFile.close();
}