void printLocalTime(){
  //Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
    if (!getLocalTime(&timeinfo)){
      DEBUG_SENSOR_SERIAL.println("Failed to obtain time");
    }
  int second = rtc.getSecond();
  int minute = rtc.getMinute();
  int hour = rtc.getHour(true)-1;
  int day = rtc.getDay();
  int month = rtc.getMonth() + 1;
  int year = rtc.getYear();
  int weekday = rtc.getDayofWeek() +1;

  sprintf(measureTime, "%i/%i/%i %i:%i:%i", day, month, year, hour,minute, second);
  DEBUG_SENSOR_SERIAL.print("Time: "); DEBUG_SENSOR_SERIAL.println(measureTime);

  M5.lcd.fillRect(0, 210, 100, 30, BLACK);
  M5.lcd.setCursor(0, 210);
  M5.lcd.printf("time: %s", measureTime);
}