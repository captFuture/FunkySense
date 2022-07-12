void connectWifi()
{
  int w = 1;
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.setHostname(clientId);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    w++;
    if (w > 25)
    {
      //ESP.restart();
    }
  }
  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
}

