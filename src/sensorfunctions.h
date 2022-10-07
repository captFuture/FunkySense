void GroveMultiGas(){
  uint8_t len = 0;
  uint8_t addr = 0;
  uint8_t i;
  uint32_t val = 0;

  c2h5oh = gas.measure_C2H5OH();  // int C2H5OH
  voc = gas.measure_VOC();      // int VOC
  co = gas.measure_CO();     // int CO
  no2 = gas.measure_NO2();     // int NO2

  M5.lcd.fillRect(0, 140, 100, 60, BLACK);
  M5.lcd.setCursor(0, 140);
  M5.lcd.printf("c2h5oh: %d  \r\nvoc: %d  \r\nco: %d \r\nno2: %d", c2h5oh, voc, co, no2);

  DEBUG_SENSOR_SERIAL.print("C2H5OH: "); DEBUG_SENSOR_SERIAL.println(gas.measure_C2H5OH());
  DEBUG_SENSOR_SERIAL.print("VOC: "); DEBUG_SENSOR_SERIAL.println(gas.measure_VOC());
  DEBUG_SENSOR_SERIAL.print("CO: "); DEBUG_SENSOR_SERIAL.println(gas.measure_CO());
  DEBUG_SENSOR_SERIAL.print("NO2: "); DEBUG_SENSOR_SERIAL.println(gas.measure_NO2());
} 

void AdafruitTSL2591(){
  uint32_t lum = tsl.getFullLuminosity();
  ir = lum >> 16;
  full = lum & 0xFFFF;
  visible = full -ir;

  ir = ir;                               // int ir
  full = full;                           // int full
  visible = visible;                     // int visible
  lux = tsl.calculateLux(full, ir);      // float LUX

  M5.lcd.fillRect(0, 70, 100, 60, BLACK);
  M5.lcd.setCursor(0, 70);
  M5.lcd.printf("IR: %d  \r\nFull: %d  \r\nvisible: %d \r\nlux: %f", ir, full, visible, lux);

  DEBUG_SENSOR_SERIAL.print("IR: ");DEBUG_SENSOR_SERIAL.println(ir);
  DEBUG_SENSOR_SERIAL.print("Full: ");DEBUG_SENSOR_SERIAL.println(full);
  DEBUG_SENSOR_SERIAL.print("visible: ");DEBUG_SENSOR_SERIAL.println(visible);
  DEBUG_SENSOR_SERIAL.print("LuX: ");DEBUG_SENSOR_SERIAL.println(lux);
}

void M5EnvIII(){
    pre = qmp6988.calcPressure();
    if (sht30.get() == 0) {
        tmp = sht30.cTemp;
        hum = sht30.humidity;
    } else {
        tmp = 0, hum = 0;
    }
    M5.lcd.fillRect(0, 20, 100, 60, BLACK);
    M5.lcd.setCursor(0, 20);
    M5.lcd.printf("Temp: %2.1f  \r\nHum: %2.0f%%  \r\nPres: %2.0fPa\r\n", tmp, hum, pre);

    DEBUG_SENSOR_SERIAL.print("Temp: ");DEBUG_SENSOR_SERIAL.println(tmp);
    DEBUG_SENSOR_SERIAL.print("Humi: ");DEBUG_SENSOR_SERIAL.println(hum);
    DEBUG_SENSOR_SERIAL.print("Pressur: ");DEBUG_SENSOR_SERIAL.println(pre);

}