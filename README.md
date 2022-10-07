# FunkySense
## Sensing the environment in several cities around the world

Microcontroller
M5Stack

Integrated Sensors
Adafruit TSL2591 High Dynamic Range Digital Light Sensor (ADA1980)
Seeed Studio Grove Multichannel Gas Sensor v2
M5EnvIII - Temp/Hum/Pres Sensor

## Settings for getting started and Infos
- prepare a SDcard and put the file config.json from /docs/SD Card/ - change all your desired values in the file and save
- Sensors will use a standard config setup - the values in config.json overwrite the defaults (if defaults are fine, do not put config.json there)
- Sensors will by default log to SDcard if present and create the necessary file (Please always use this as a fallback)
- Network sending mode is ON by default and tries to connect to the default values
- If there is a network connection, the time is synched with the PC running the mqtt server, otherwise 1/1/2000 is used
### Setting wifi (for new sensor)
- Switch on sensor, it will open an access point with the SensorName and connect to it via PC or phone
- navigate to Wifi settings, search for network and connect
- the wifi credentials will be remembered
- The Access point will close after 60 Seconds and sensor will start "offline" operation and only record to sdcard
### Button functions
- Button A - toggle network Mode (indicated by square in the top right display corner)
- Button B - Switch on display for 10Seconds
- Long Press Button C - Wifi connection mode activated for 60 Seconds 

### Sensordata in csv
string datetime, string sensorid, string city,float temp,float humidity,float pressure, int ir,int full,int visible,float lux, int c2h5oh,int voc, int co, int no2, uint rssi

### Indicators on screen
- Top right - Networkmode on
- middle right - Sdcard inserted

Windows Installation needed
- nodejs (https://nodejs.org/en/ - 16.6 LTS)
- node-red (https://nodered.org/docs/getting-started/windows - do not forget to create "Run Node-RED on Startup")

and install https://flows.nodered.org/node/node-red-node-sqlite connector and https://flows.nodered.org/node/node-red-contrib-sqlitedb and https://flows.nodered.org/node/node-red-node-base64 and https://flows.nodered.org/node/thethingbox-node-timestamp

- mosquitto mqtt broker (https://mosquitto.org/download/ - mosquitto-2.0.14-install-windows-x64.exe - and create a startup task like with node red)
IMPORTANT: 
- Deactivate windows firewall or create exception for port 1883
- change mosquitto conf [C:\Program Files\mosquitto\mosquitto.conf] (ADD listener 1883 allow_anonymous true at top of config file)
(for debugging kill mosquitto service and open it in a cmd window manually with mosquitto.exe -v -c mosquitto.conf)

How to test Windows Setup: check images in docs/installfiles

Start Mosquitto (if not activated by task on startup)
Start Node Red (if not activated by task on startup)
Import docs/nodered/flows.json into NodeRed at http://localhost:1880 and deploy

Start MQTT-Explorer and connect to mqtt broker on localhost (without certificate) -> send Payload to sensors/ (see payload above)
You should see an output in nodeRed debug console 


Some Infos:
// https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm

Activate ntp server:
https://itler.net/windows-pc-server-als-ntp-server-konfigurieren-einrichten/