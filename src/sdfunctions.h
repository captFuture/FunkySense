void initializeSD(){

    if (!SD.begin()) {
        SDinserted = false;
        DEBUG_ERROR_SERIAL.println("SDCard failed, or not present"); 
    }else{
        SDinserted = true;
        DEBUG_INFORMATION_SERIAL.println("SDCard present"); 
    }
    if(SDinserted){
        if (SD.exists("/sensor.csv")) {
            DEBUG_INFORMATION_SERIAL.println("sensor.csv exists.");
            File sensorFile = SD.open("/sensor.csv", FILE_APPEND);
            sensorFile.println("exists NEW DATA ----------");
            sensorFile.close();
        } else {
            DEBUG_ERROR_SERIAL.println("sensor.csv doesn't exist.");
            File sensorFile = SD.open("/sensor.csv", FILE_WRITE);
            int written = sensorFile.println("does not exist NEW FILE ----------");
            DEBUG_INFORMATION_SERIAL.println(written);
            sensorFile.close();
        }
    }
}

void readConfig(){
    if(SDinserted == true){
        File configFile = SD.open("/config.json", FILE_READ);
        DEBUG_INFORMATION_SERIAL.print("Reading config from SD: ");

        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, configFile);
        if (error){
            Serial.println(F("Failed to read file, using default configuration"));      
        }
            
        strlcpy(config.city, doc["city"] | xstr(CITY), sizeof(config.city));
        strlcpy(config.clientId, doc["clientid"] | xstr(CLIENTID), sizeof(config.clientId));
        strlcpy(config.ssid, doc["ssid"] | xstr(SSID), sizeof(config.ssid));
        strlcpy(config.password, doc["password"] | xstr(PASSWORD), sizeof(config.password));
        strlcpy(config.mqttserver, doc["mqttserver"] | xstr(MQTTSERVER), sizeof(config.mqttserver));
        config.NETworkmode = doc["networkmode"] | true;

        configFile.close();
    }else{
        DEBUG_INFORMATION_SERIAL.println("SD not present - config not readable");
    }
    
}

void writePayload(){
    if(SDinserted == true){
        File sensorFile = SD.open("/sensor.csv", FILE_APPEND);
        sprintf(sdmsg,sdFormat, measureTime, config.clientId, config.city, tmp, hum, pre, ir, full, visible, lux, c2h5oh, voc, co, no2, WiFi.RSSI());
        DEBUG_INFORMATION_SERIAL.print("Writing Sensordata to SD: ");
        int written = sensorFile.println(sdmsg);
        DEBUG_INFORMATION_SERIAL.println(written);
        sensorFile.close();
    }else{
        sprintf(sdmsg,sdFormat, measureTime, config.clientId, config.city, tmp, hum, pre, ir, full, visible, lux, c2h5oh, voc, co, no2, WiFi.RSSI());
        DEBUG_INFORMATION_SERIAL.println(sdmsg);
        DEBUG_INFORMATION_SERIAL.println("SD not present - not writing");
    }
    
}

void clearSDcontent(){
    if(SDinserted == true){
        SD.remove("/sensor.csv");
        File sensorFile = SD.open("/sensor.csv", FILE_WRITE);
        DEBUG_INFORMATION_SERIAL.println("SDcard cleared - new sensors.csv added");
        sensorFile.close();
    }else{
        DEBUG_INFORMATION_SERIAL.println("SD not present - not clearing");
    }
}