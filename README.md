# FunkySense

Sensing the environment in several cities around the world

Microcontroller


Integrated Sensors
DC3.3-5V 200nm-370nm Response Wavelength UV Detection Sensor Module Ultraviolet Ray UV Sensor Module for Arduino
Adafruit TSL2591 High Dynamic Range Digital Light Sensor (ADA1980)
Seeed Studio Grove Multichannel Gas Sensor v2
Micro SD Breakout Board für SD/TF Karte für Arduino 3,3V 6Pin
GY-Bme280 High Precision Digital Sensor Barometric Pressure Temperature Humidity and Air Pressure Module Board for Arduino Raspberry Pi DIY I2C SPI 5V

---


Windows Installation needed
- nodejs (https://nodejs.org/en/ - 16.6 LTS)
- node-red (https://nodered.org/docs/getting-started/windows - do not forget to create "Run Node-RED on Startup")

and install https://flows.nodered.org/node/node-red-node-sqlite connector and https://flows.nodered.org/node/node-red-contrib-sqlitedb and https://flows.nodered.org/node/node-red-node-base64 and https://flows.nodered.org/node/thethingbox-node-timestamp

- mosquitto mqtt broker (https://mosquitto.org/download/ - mosquitto-2.0.14-install-windows-x64.exe - and create a startup task like with node red)
IMPORTANT: 
- Deactivate windows firewall or create exception for port 1880
- change mosquitto conf [C:\Program Files\mosquitto\mosquitto.conf] (AND allow_anonymous true AND port 1883 at top of config file)

- SQlite (https://www.sqlite.org/download.html - sqlite-dll-win64-x64-3390000.zip - sqlite-tools-win32-x86-3390000.zip )
  Extract everything to C:\sqlite and add the directory to your path variable

For Development:
- Sqlite browser (https://sqlitebrowser.org/dl/ - Standard installer for 64-bit Windows)
- http://mqtt-explorer.com/


Json Payload to send: DEMO (send to topic sensors/)
{"sensor": 1,"value1": 123,"value2": 123,"value3": 123,"value4": 123,"value5": 123,"value6": 123,"value7": 123,"value8": 123,"value9": 123,"value10": 123}
timestamp is added automatically in UTC 

How to test Windows Setup: check images in docs/installfiles

Start Mosquitto (if not activated by task on startup)
Start Node Red (if not activated by task on startup)
Import docs/nodered/flows.json into NodeRed at http://localhost:1880 and deploy

Start MQTT-Explorer and connect to mqtt broker on localhost (without certificate) -> send Payload to sensors/ (see payload above)
You should see an output in nodeRed debug console 

Start DB Browser for SQlite and open database sqlite/democity_001.sqlite from repository
After Node Red inserted the lines to the DB - you should see records (including insert timestamp in UTC)

Some Infos:
// https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
