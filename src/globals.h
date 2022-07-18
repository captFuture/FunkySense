#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERROR true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERROR)Serial

#define DEBUG_SENSOR false
#define DEBUG_SENSOR_SERIAL if(DEBUG_SENSOR)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

#define SAVE_SD
bool SDinserted = false;
bool NETworkmode = true;
int wifiretries = 10;
int mqttretries = 10;

#ifdef ESP32
    int WaveshareUV_Pin = 36;
#else
    int WaveshareUV_Pin = 14;
#endif
int uvvalue = 0;

struct {
    char *sensor;
    float one;
    float two;
    float three;
    float four;

    int five;
    int six;
    int seven;
    int eight;

    int nine;
    int ten;
    int rssi;
} SensorValues;

struct {
    char *sensor;
    int one;
    int two;
    int three;
    float four;

    int five;
    int six;
    int seven;
    int eight;
    int nine;
    int ten;
    int rssi;
} SensorValues1;

unsigned long pauseONE = 10000; //10 seconds
unsigned long oldMillisONE = 0;

unsigned long pauseTWO = 10000; //10 seconds
unsigned long oldMillisTWO = 0;

//const char* ssid = "TarantlBros";
//const char* password = "chillfumml";
const char* ssid = "KAJJAR";
const char* password = "hvstjsr6mrS2";

//const char* mqttuser = "myUser";
//const char* mqttpassword = "myPassword";

const char* version = xstr(VERSION);
const char* clientId = xstr(CLIENTID);
const char* mqttserver = xstr(MQTTSERVER);

const char payloadFormat[] = "{\"s\":\"%s\",  \"v1\":%f, \"v2\":%f, \"v3\":%f, \"v4\":%f,  \"v5\":%u, \"v6\":%u, \"v7\":%u, \"v8\":%u,  \"v9\":%u, \"v10\":%u, \"rssi\":%d}";
const char payloadFormat1[] = "{\"s\":\"%s\",  \"v1\":%u, \"v2\":%u, \"v3\":%u, \"v4\":%f,  \"v5\":%u, \"v6\":%u, \"v7\":%u, \"v8\":%u,  \"v9\":%u, \"v10\":%u, \"rssi\":%d}";
const char sdFormat[] = "%s, %f,%f,%f,%f, %u,%u,%u,%u, %u,%u,   %u,%u,%u,%f, %u,%u,%u,%u, %u,%u, %d";

const char statusFormat[] = "{\"n\":\"%s\", \"ip\":\"%s\", \"rssi\":%d, \"s\":\"ONLINE\"}";
const char encFormat[] = "{\"e\":\"%s\"}";



char msg[1024];
char msg1[1024];
char encmsg[1024];
char sdmsg[1024];

char outTopic[] = "sensors/evt";
char outTopic1[] = "sensors/evt1";
char encTopic[] = "sensors/enc";
char plainTopic[] = "sensors/plain";
char statusTopic[] = "sensors/status";
char inTopic[] = "sensors/cmd";
char clearSDcommand[] = "clearsd";