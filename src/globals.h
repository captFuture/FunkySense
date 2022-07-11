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
} SensorValues;

int period = 1000;
unsigned long time_now = 0;

const char* version = xstr(VERSION);
const char* deviceid = xstr(DEVICEID);
const char* ipaddress = xstr(IPADDRESS);

const char* ssid = "TarantlBros";
const char* password = "chillfumml";

const char* mqttuser = "";
const char* mqttpassword = "";

const char payloadFormat[] = "{\"sensor\":%d, \"value1\":%d, \"value2\":%d, \"value3\":%d, \"value4\":%d, \"value5\":%d, \"value6\":%d, \"value7\":%d, \"value8\":%d, \"value9\":%d, \"value10\":%d}";
const char statusFormat[] = "{\"hostname\":\"%s\", \"ipadress\":\"%s\", \"status\":\"ONLINE\"}";
char msg[100];
char message_buff[100];

char server[20] = "192.168.50.50";
char outTopic[] = "sensors/evt";
char inTopic[] = "sensors/cmd";
//char clientId[9] = deviceid;

char mqtt_will[] = "";
char mqtt_testament[] = "";

char responseTopic[] = "sensors/mgmt/response";
char manageTopic[] = "sensors/mgmt/manage";
const char updateTopic[] = "sensors/mgmt/initiate/device/update";
const char rebootTopic[] = "sensors/mgmt/initiate/device/reboot";