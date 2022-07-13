#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERROR true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERROR)Serial

#define DEBUG_WARNING true
#define DEBUG_WARNING_SERIAL if(DEBUG_WARNING)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

//#define SAVE_SD
bool SDinserted = false;

struct {
    char *sensor;
    float one;
    float two;
    float three;
    int four;
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
    float one;
    float two;
    float three;
    int four;
    int five;
    int six;
    int seven;
    float eight;
    float nine;
    float ten;
    int rssi;
} SensorValues1;




unsigned long pauseONE = 10000; //10 seconds
unsigned long oldMillisONE = 0;

unsigned long pauseTWO = 10000; //10 seconds
unsigned long oldMillisTWO = 0;

const char* ssid = "TarantlBros";
const char* password = "chillfumml";
//const char* ssid = "KAJJAR";
//const char* password = "hvstjsr6mrS2";

const char* mqttuser = "captFuture";
const char* mqttpassword = "Che11as!1";

const char* version = xstr(VERSION);
const char* clientId = xstr(CLIENTID);
const char* mqttserver = xstr(MQTTSERVER);

const char payloadFormat[] = "{\"s\":\"%s\", \"v1\":%f, \"v2\":%f, \"v3\":%f, \"v4\":%u, \"v5\":%u, \"v6\":%u, \"v7\":%u, \"v8\":%u, \"v9\":%u, \"v10\":%u, \"rssi\":%d}";
const char payloadFormat1[] = "{\"s\":\"%s\", \"v1\":%f, \"v2\":%f, \"v3\":%f, \"v4\":%u, \"v5\":%u, \"v6\":%u, \"v7\":%u, \"v8\":%u, \"v9\":%u, \"v10\":%u, \"rssi\":%d}";
const char sdFormat[] = "%s,%f,%f,%f,%u,%u,%u,%u,%u,%u,%u,%d";

const char statusFormat[] = "{\"n\":\"%s\", \"ip\":\"%s\", \"rssi\":%d, \"s\":\"ONLINE\"}";
char msg[1024];
char msg1[1024];
char sdmsg[1024];

char outTopic[] = "sensors/evt";
char outTopic1[] = "sensors/evt1";
char statusTopic[] = "sensors/status";
char inTopic[] = "sensors/cmd";
char clearSDcommand[] = "clearsd";