void connectWifi()
{
  int w = 1;
  DEBUG_INFORMATION_SERIAL.print("Connecting to ");
  DEBUG_INFORMATION_SERIAL.print(ssid);
  WiFi.setHostname(clientId);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    DEBUG_INFORMATION_SERIAL.print(".");
    w++;
    if (w > 10)
    {
      DEBUG_INFORMATION_SERIAL.print("No connect Possible - Disabling WiFi");
      wifiretries = wifiretries - 1;
      return;
      /*#ifdef ESP32
      ESP.restart();
      #else
      NVIC_SystemReset();
      #endif
      */
    }
  }
  DEBUG_INFORMATION_SERIAL.println("");
  DEBUG_INFORMATION_SERIAL.print("WiFi connected, IP address: ");
  DEBUG_INFORMATION_SERIAL.println(WiFi.localIP());
  DEBUG_INFORMATION_SERIAL.println();
  #ifdef ESP32
    DEBUG_INFORMATION_SERIAL.print("MAC: ");
    DEBUG_INFORMATION_SERIAL.println(WiFi.macAddress());
    DEBUG_INFORMATION_SERIAL.print("RSSI: ");
    DEBUG_INFORMATION_SERIAL.println(WiFi.RSSI());
  #endif
}

String ip2Str(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++) {
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}