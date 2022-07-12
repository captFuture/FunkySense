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
    if (w > 25)
    {
      #ifdef ESP32
      ESP.restart();
      #else
      NVIC_SystemReset();
      #endif     
    }
  }
  DEBUG_INFORMATION_SERIAL.println("");
  DEBUG_INFORMATION_SERIAL.print("WiFi connected, IP address: ");
  DEBUG_INFORMATION_SERIAL.println(WiFi.localIP());
  DEBUG_INFORMATION_SERIAL.println();
  DEBUG_INFORMATION_SERIAL.print("MAC: ");
  DEBUG_INFORMATION_SERIAL.println(WiFi.macAddress());
}
