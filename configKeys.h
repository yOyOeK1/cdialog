// Keys Root

// now in ccanvas.c file :(
//
struct keyBind {
	int parentId;
	char ch[51];
	int doWhat; 
	char parser[512];
	char args[512];
};
struct keyBind keyBinds[] = {
	/*	key,	cmdh,			*/	
	{ 0, 	"?",	0,		"help\n%s",		"cat ./configKeys.h | grep -e \"^\t{ 0,\"" },
	{ 0, 	"W",	0,		"ip's:\n%s",		"ip a | grep 'inet ' | awk '{print $2}'" },
	{ 0,    "w",	0,		"%s",			"whoami" },
	{ 0,    "l",	0,		"load:\n%s",		"cat /proc/loadavg" },
	{ 0,    "o",	0,		"cpu's online:\n%s",	"cd /sys/devices/system/cpu && grep '1' ./cpu*/online" },
	{ 0,    "\"",	0,		"brightnes +",		"sudo ~/.viteyss/oven/oMachine/brightness.sh +" },
	{ 0,    ":",	0,		"brightnes -",		"sudo ~/.viteyss/oven/oMachine/brightness.sh -" },
	{ 0,    "u",	0,		"uptime:\n%s",		"uptime | awk '{print $1}'" },
	{ 0,    "f",	0,		"%s",			"free -h" },
	
	{ 0,    "hh",	0,		"test hh\n\t%s",	"echo HH" },
	{ 0,    "mp",	1,		"and/test/perc",	"11.11" },
	
	{-1}
};

