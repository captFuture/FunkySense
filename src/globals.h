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
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    int eight;
    int nine;
    int ten;
    long rssi;
} SensorValues;

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

const char payloadFormat[] = "{\"sensor\":\"%s\", \"value1\":%f, \"value2\":%d, \"value3\":%d, \"value4\":%d, \"value5\":%d, \"value6\":%d, \"value7\":%d, \"value8\":%d, \"value9\":%d, \"value10\":%d, \"rssi\":%d}";
const char sdFormat[] = "%s,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

const char statusFormat[] = "{\"hostname\":\"%s\", \"ipadress\":\"%s\", \"rssi\":%d, \"status\":\"ONLINE\"}";
char msg[256];
char sdmsg[256];

char outTopic[] = "sensors/evt";
char statusTopic[] = "sensors/status";
char inTopic[] = "sensors/cmd";
char clearSDcommand[] = "clearsd";