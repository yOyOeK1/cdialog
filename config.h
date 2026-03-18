

int TIME_ZONE_OFFSET = -5 * 60 * 60; // sec

char *mqttHost = "192.168.43.1";
int mqttPort = 10883;
char *mqttClientId = "cDialogTest";

char *mqTopicPrefix = "and/";
char *mqSubs[] = {
	"hu/#",
	"dell/bat/#",
	"dell/cpu/loadavg",
};

char *machineName = "yDell";
