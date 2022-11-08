#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERRORS true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERRORS)Serial

#define DEBUG_SENSOR true
#define DEBUG_SENSOR_SERIAL if(DEBUG_SENSOR)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

#define DEBUG_NTPClient true

#define SAVE_SD
bool SDinserted = false;
int mqttretries = 10;

int WaveshareUV_Pin = 36;

unsigned long pauseONE = 10000; //10 seconds
unsigned long oldMillisONE = 0;

unsigned long pauseTWO = 10000; //10 seconds
unsigned long oldMillisTWO = 0;

struct Config {
  char city[40] = xstr(CITY);
  char clientId[40] = xstr(CLIENTID);
  char ssid[40] = xstr(SSID);
  char password[40] = xstr(PASSWORD);
  char mqttserver[60] = xstr(MQTTSERVER);
  char mqttuser[60] = xstr(MQTTUSER);
  char mqttpwd[60] = xstr(MQTTPWD);
  char mqttport[5] = xstr(MQTTPORT);
  char ntpserver[40] = xstr(NTPSERVER);
  bool NETworkmode = true;
};
Config config;

const char* version = xstr(VERSION);

float tmp = 0.0;
float hum = 0.0;
float pre = 0.0;

float lux = 0.0;
int ir = 0;
int full = 0;
int visible = 0;

int c2h5oh = 0;
int voc = 0;
int co = 0;
int no2 = 0;

int uv = 0;

int buttonPress;
int timeout = 60;

// const char sdFormat[] = "string datetime, string sensorid, string city,float temp,float humidity,float pressure, int ir,int full,int visible,float lux, int c2h5oh,int voc, int co, int no2, int uv, uint rssi";
const char sdFormat[] = "%s, %s, %s, %2.2f, %2.2f, %2.2f, %u, %u, %u, %2.2f, %u, %u, %u, %u,%u, %d";
/*
https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
*/

const char statusFormat[] = "{\"n\":\"%s\", \"ip\":\"%s\", \"time\":\"%s\", \"rssi\":%d, \"s\":\"ONLINE\"}";
const char encFormat[] = "{\"e\":\"%s\"}";

const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
char measureTime[30];

char msg[1024];
char msg1[1024];
char encmsg[1024];
char sdmsg[2000];

char encTopic[] = "sensors/enc";
char plainTopic[] = "sensors/plain";
char statusTopic[] = "sensors/status";
char inTopic[] = "sensors/cmd";
char clearSDcommand[] = "clearsd";