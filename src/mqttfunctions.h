void sendDeviceStatus()
{
  sprintf(msg, statusFormat, clientId, ip2Str(WiFi.localIP()));
  if (client.publish(manageTopic, msg))
  {
  }
  else
  {
  }
}

void sendSensorsArnoTest() {
  //get_gass();
  //get_temphum();
  //get_light()
}

void sendSensors(){
  
  /* get some values and send this shit */
  sprintf(msg,payloadFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten );
  // "{\"sensor\":%d, \"value1\":%d, \"value2\":%d, \"value3\":%d, \"value4\":%d, \"value5\":%d, \"value6\":%d, \"value7\":%d, \"value8\":%d, \"value9\":%d, \"value10\":%d}";
  // https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
  
  DEBUG_INFORMATION_SERIAL.print("Sending payload: ");
  DEBUG_INFORMATION_SERIAL.println(msg);

  if (client.publish(outTopic, msg)) {
    DEBUG_INFORMATION_SERIAL.println("Publish ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish failed");
  }
}

void callback(char *topic, byte *payload, unsigned int length){
  DEBUG_INFORMATION_SERIAL.println("Message arrived");
  char json[length + 1];
  strncpy(json, (char *)payload, length);
  json[length] = '\0';

  DEBUG_INFORMATION_SERIAL.print("Topic: ");
  DEBUG_INFORMATION_SERIAL.println(topic);
  DEBUG_INFORMATION_SERIAL.print("Message: ");
  DEBUG_INFORMATION_SERIAL.println(json);

  if (strcmp(rebootTopic, topic) == 0)
  {
    DEBUG_INFORMATION_SERIAL.println("Rebooting...");
    //restart();
  }

  if (strcmp(updateTopic, topic) == 0)
  {
    DEBUG_INFORMATION_SERIAL.println("Updating firmware");
    //checkOTA();
  }

  // Decode JSON request
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &doc = jsonBuffer.parseObject((char *)json);
  if (!doc.success())
  {
    DEBUG_INFORMATION_SERIAL.println("parseObject() failed");
    return;

  }
    //const char* name = doc["name"]; // 
    //const char* ssid = doc["ssid"]; // 
    //const char* passwd = doc["passwd"]; // 
    
}

void initManagedDevice()
{
  if (client.subscribe(inTopic))
  {
    DEBUG_INFORMATION_SERIAL.println("subscribe to inTopic OK");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("subscribe to inTopic FAILED");
  }

  if (client.subscribe(responseTopic))
  {
    DEBUG_INFORMATION_SERIAL.println("subscribe to responses OK");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("subscribe to responses FAILED");
  }

  if (client.subscribe(rebootTopic))
  {
    DEBUG_INFORMATION_SERIAL.println("subscribe to reboot OK");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("subscribe to reboot FAILED");
  }

  if (client.subscribe(updateTopic))
  {
    DEBUG_INFORMATION_SERIAL.println("subscribe to update OK");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("subscribe to update FAILED");
  }

  if (client.subscribe(manageTopic))
  {
    sendDeviceStatus();
    DEBUG_INFORMATION_SERIAL.println("device Manage ok");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("device Manage failed");
  }
}

void reconnect()
{
  while (!client.connected())
  {
    DEBUG_INFORMATION_SERIAL.print("Attempting MQTT connection...");
    //if (client.connect(clientId, mqttuser, mqttpassword))
    if (client.connect(clientId))
    {
      DEBUG_INFORMATION_SERIAL.println("connected");
      DEBUG_INFORMATION_SERIAL.print("state:");
      DEBUG_INFORMATION_SERIAL.println(client.state());
      delay(1000);
      initManagedDevice();
    }
    else
    {
      DEBUG_ERROR_SERIAL.print("failed, rc=");
      DEBUG_ERROR_SERIAL.print(client.state());
      DEBUG_ERROR_SERIAL.println(" trying fallback");
      delay(5000);

      client.setServer(server, 1883);
      if (client.connect(clientId))
      {
        DEBUG_INFORMATION_SERIAL.println("fallback connected");
        delay(1000);
        initManagedDevice();
      }else{
        DEBUG_ERROR_SERIAL.print("failed, rc=");
        DEBUG_ERROR_SERIAL.print(client.state());
        DEBUG_ERROR_SERIAL.println(" back to server");
        client.setServer(server, 1883);
        delay(5000);
      }
    }
  }
}

