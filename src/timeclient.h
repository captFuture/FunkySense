/* void printLocalTime(){
  //Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
    if (!getLocalTime(&timeinfo)){
      DEBUG_INFORMATION_SERIAL.println("Failed to obtain time");
    }
  int second = rtc.getSecond();
  int minute = rtc.getMinute();
  int hour = rtc.getHour(true)-1;
  int day = rtc.getDay();
  int month = rtc.getMonth() + 1;
  int year = rtc.getYear();
  int weekday = rtc.getDayofWeek() +1;

  sprintf(measureTime, "%i/%i/%i %i:%i:%i", day, month, year, hour,minute, second);
  DEBUG_INFORMATION_SERIAL.print("Time: "); DEBUG_INFORMATION_SERIAL.println(measureTime);

  M5.lcd.fillRect(0, 210, 100, 30, BLACK);
  M5.lcd.setCursor(0, 210);
  M5.lcd.printf("time: %s", measureTime);
}

void SetTime(String str){
  //String str = "00,30,12,21,02,1976";
  String strs[6];
  int StringCount = 0;

  while (str.length() > 0){
    int index = str.indexOf(',');
    if (index == -1)
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  for (int i = 0; i < StringCount; i++)
    {
      Serial.print(i);
      Serial.print(": \"");
      Serial.print(strs[i]);
      Serial.println("\"");
    }
  rtc.setTime(strs[0].toInt(), strs[1].toInt(), strs[2].toInt(), strs[3].toInt(), strs[4].toInt(), strs[5].toInt());
  DEBUG_INFORMATION_SERIAL.println(rtc.getTime("%d/%m/%Y %H:%M:%S"));
}*/

void SetUnitRtcTime(String str){
  //String str = "00,30,12,21,02,1976";
  String strs[6];
  int StringCount = 0;

  while (str.length() > 0){
    int index = str.indexOf(',');
    if (index == -1)
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  for (int i = 0; i < StringCount; i++)
    {
      Serial.print(i);
      Serial.print(": \"");
      Serial.print(strs[i]);
      Serial.println("\"");
    }

  RTCtime.Hours   = strs[2].toInt();
  RTCtime.Minutes =  strs[1].toInt();
  RTCtime.Seconds = strs[0].toInt();

  RTCdate.Month   = strs[4].toInt();
  RTCdate.Date    = strs[3].toInt();
  RTCdate.Year    = strs[5].toInt();

  unitRTC.setTime(&RTCtime);
  unitRTC.setDate(&RTCdate);

  unitRTC.getTime(&RTCtime);
  unitRTC.getDate(&RTCdate);
  DEBUG_INFORMATION_SERIAL.printf("Set RTC Time Now is %02d:%02d:%02d\n", RTCtime.Hours, RTCtime.Minutes, RTCtime.Seconds);
  DEBUG_INFORMATION_SERIAL.printf("Set RTC Date Now is %02d/%02d/%02d\n", RTCdate.Date, RTCdate.Month, RTCdate.Year);
}

void printUnitRtcTime(){
    unitRTC.getTime(&RTCtime);
    unitRTC.getDate(&RTCdate);
    sprintf(measureTime, "%i/%i/%i %i:%i:%i", RTCdate.Date, RTCdate.Month, RTCdate.Year, RTCtime.Hours, RTCtime.Minutes, RTCtime.Seconds);
    DEBUG_INFORMATION_SERIAL.print("Time: "); DEBUG_INFORMATION_SERIAL.println(measureTime);

    M5.lcd.fillRect(0, 210, 100, 30, BLACK);
    M5.lcd.setCursor(0, 210);
    M5.lcd.printf("time: %s", measureTime);
}