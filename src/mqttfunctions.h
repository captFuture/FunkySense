void sendDeviceStatus()
{
  sprintf(msg, statusFormat, clientId, ip2Str(WiFi.localIP()), SensorValues.rssi);
  if (client.publish(statusTopic, msg))
  {
  }
}

void saveSensors(){
  sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues1.one, SensorValues1.two, SensorValues1.three, SensorValues1.four, SensorValues1.five, SensorValues1.six, SensorValues1.seven, SensorValues1.eight, SensorValues1.nine, SensorValues1.ten, SensorValues.rssi );
  DEBUG_INFORMATION_SERIAL.println(sdmsg);
  #ifdef SAVE_SD
    DEBUG_INFORMATION_SERIAL.print("3SDinserted: ");
    DEBUG_INFORMATION_SERIAL.println(SDinserted);
    DEBUG_INFORMATION_SERIAL.println(SDinserted ? "YES" : "NO");
    if(SDinserted){
      writePayload();
    }
  #endif
}

void sendSensors(){
  sprintf(sdmsg,sdFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues1.one, SensorValues1.two, SensorValues1.three, SensorValues1.four, SensorValues1.five, SensorValues1.six, SensorValues1.seven, SensorValues1.eight, SensorValues1.nine, SensorValues1.ten, SensorValues.rssi );
  DEBUG_INFORMATION_SERIAL.println(sdmsg);
  #ifdef ESP32
  String encoded = base64::encode(sdmsg);
  DEBUG_INFORMATION_SERIAL.println(encoded);

  if (client.publish(encTopic, encoded.c_str())){
    DEBUG_INFORMATION_SERIAL.println("Publish ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish failed");
  }

  #else
    unsigned char string[] = sdmsg;
    unsigned char base64[1024]; 

    // encode_base64() places a null terminator automatically, because the output is a string
    unsigned int base64_length = encode_base64(sdmsg, strlen((char *) sdmsg), base64);

    printf("%d\n", base64_length); // Prints "20"
    printf((char *) base64); // Prints "U3RyaW5nIGV4YW1wbGU="


    //String encoded = base64::encode(sdmsg);
    String encoded = "lalalalala";
    DEBUG_INFORMATION_SERIAL.println(encoded);
    if (client.publish(encTopic, encoded.c_str())){
      DEBUG_INFORMATION_SERIAL.println("Publish ok");
    } else {
      DEBUG_ERROR_SERIAL.println("Publish failed");
    }
  #endif

  /* get some values and send this shit */
  sprintf(msg,payloadFormat, SensorValues.sensor, SensorValues.one, SensorValues.two, SensorValues.three, SensorValues.four, SensorValues.five, SensorValues.six, SensorValues.seven, SensorValues.eight, SensorValues.nine, SensorValues.ten, SensorValues.rssi);
  DEBUG_INFORMATION_SERIAL.print("Sending payload: ");
  DEBUG_INFORMATION_SERIAL.println(msg);
  if (client.publish(outTopic, msg)) {
    DEBUG_INFORMATION_SERIAL.println("Publish ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish failed");
  }

  sprintf(msg1,payloadFormat1, SensorValues1.sensor, SensorValues1.one, SensorValues1.two, SensorValues1.three, SensorValues1.four, SensorValues1.five, SensorValues1.six, SensorValues1.seven, SensorValues1.eight, SensorValues1.nine, SensorValues1.ten);
  DEBUG_INFORMATION_SERIAL.print("Sending payload1: ");
  DEBUG_INFORMATION_SERIAL.println(msg1);
  if (client.publish(outTopic1, msg1)) {
    DEBUG_INFORMATION_SERIAL.println("Publish1 ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish1 failed");
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

  // Decode JSON request
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &doc = jsonBuffer.parseObject((char *)json);
  if (!doc.success())
  {
    DEBUG_INFORMATION_SERIAL.println("parseObject() failed");
    return;

  }
    int command = doc["command"]; // 
    DEBUG_INFORMATION_SERIAL.print("COMMAND: ");
    DEBUG_INFORMATION_SERIAL.println(command);

    if(command == 1){
     DEBUG_INFORMATION_SERIAL.println("Clearing SD content");
     if(SDinserted){
      #ifdef ESP32
        clearSDcontent();
      #endif
     }
    }
    if(command == 2){
     DEBUG_INFORMATION_SERIAL.println("Rebooting device");
     #ifdef ESP32
      ESP.restart();
     #else
      NVIC_SystemReset();
     #endif   
    }

    if(command == 3){
      DEBUG_INFORMATION_SERIAL.println("Sending device Status");
      sendDeviceStatus();
    }
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

  if (client.subscribe(statusTopic))
  {
    sendDeviceStatus();
    DEBUG_INFORMATION_SERIAL.println("device statusTopic Manage ok");
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
    DEBUG_INFORMATION_SERIAL.println(mqttserver);

    //if (client.connect(clientId, mqttuser, mqttpassword))
    if (client.connect(clientId))
    {
      DEBUG_INFORMATION_SERIAL.println("connected");
      DEBUG_INFORMATION_SERIAL.print("state:");
      DEBUG_INFORMATION_SERIAL.println(client.state());
      client.setBufferSize(512);
      delay(1000);
      initManagedDevice();
    }
    else
    {
      DEBUG_ERROR_SERIAL.print("failed, rc=");
      DEBUG_ERROR_SERIAL.print(client.state());
      DEBUG_ERROR_SERIAL.println(" trying fallback");
      delay(5000);

      client.setServer(mqttserver, 1883);
      if (client.connect(clientId))
      {
        DEBUG_INFORMATION_SERIAL.println("fallback connected");
        client.setBufferSize(512);
        delay(1000);
        initManagedDevice();
      }else{
        DEBUG_ERROR_SERIAL.print("failed, rc=");
        DEBUG_ERROR_SERIAL.print(client.state());
        DEBUG_ERROR_SERIAL.println(" back to server");
        client.setServer(mqttserver, 1883);
        delay(5000);
      }
    }
  }
}

