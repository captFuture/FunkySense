void askSensors(){
    //DEBUG_INFORMATION_SERIAL.println("Sensorloop");
    #ifdef ESP32
        //DEBUG_INFORMATION_SERIAL.print("askSensors() running on core ");
        //DEBUG_INFORMATION_SERIAL.println(xPortGetCoreID());
    #endif
    SensorValues.sensor = "001";
    SensorValues.one = 1.234; // float
    SensorValues.two = 20; // int
    SensorValues.three = 30; // int
    SensorValues.four = 40; // int
    SensorValues.five = 5; // int
    SensorValues.six = 6; // int
    SensorValues.seven = 7; // int
    SensorValues.eight = 8; // int
    SensorValues.nine = 9; // int
    SensorValues.ten = 10; // int
    SensorValues.rssi = WiFi.RSSI(); 
}

