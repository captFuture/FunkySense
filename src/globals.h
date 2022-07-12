#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERROR true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERROR)Serial

#define DEBUG_WARNING true
#define DEBUG_WARNING_SERIAL if(DEBUG_WARNING)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

struct {
    int sensor;
    int one;
    int two;
    int three;
    int four;
    int five;
    int six;
    int seven;
    int eight;
    int nine;
    int ten;
    float eleven;
} SensorValues;
// SensorValues.one

unsigned long pauseONE = 10000; //10 seconds
unsigned long oldMillisONE = 0;

const char* version = xstr(VERSION);

const char* ssid = "TarantlBros";
const char* password = "chillfumml";
//const char* ssid = "KAJJAR";
//const char* password = "hvstjsr6mrS2";

const char* mqttuser = "captFuture";
const char* mqttpassword = "Che11as!1";

const char payloadFormat[] = "{\"sensor\":%d, \"value1\":%d, \"value2\":%d, \"value3\":%d, \"value4\":%d, \"value5\":%d, \"value6\":%d, \"value7\":%d, \"value8\":%d, \"value9\":%d, \"value10\":%d}";
const char statusFormat[] = "{\"hostname\":\"%s\", \"ipadress\":\"%s\", \"status\":\"ONLINE\"}";
char msg[100];
char message_buff[100];

char ipaddress[20];

#define DEVICE_ID "TheSensor_001"


char outTopic[] = "sensors/evt";
char inTopic[] = "sensors/cmd";
char clientId[] = DEVICE_ID;

char mqtt_will[] = "";
char mqtt_testament[] = "";

char responseTopic[] = "sensors/mgmt/response";
char manageTopic[] = "sensors/mgmt/manage";
const char updateTopic[] = "sensors/mgmt/initiate/device/update";
const char rebootTopic[] = "sensors/mgmt/initiate/device/reboot";