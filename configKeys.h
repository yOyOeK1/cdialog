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
	{ 0, "?",	0,/*"cmdh"*/	"help\n%s",		"cat ./configKeys.h | grep -e \"^\t{ 0,\"" },
	{ 0, "W",	0,/*"cmdh"*/	"ip's:\n%s",		"ip a | grep 'inet ' | awk '{print $2}'" },
	{ 0, "w",	0,/*"cmdh"*/	"%s",			"whoami" },
	{ 0, "l",	0,/*"cmdh"*/	"load:\n%s",		"cat /proc/loadavg" },
	{ 0, "o",	0,/*"cmdh"*/	"cpu's online:\n%s",	"cd /sys/devices/system/cpu && grep '1' ./cpu*/online" },
	{ 0, "u",	0,/*"cmdh"*/	"uptime:\n%s",		"uptime | awk '{print $1}'" },
	{ 0, "f",	0,/*"cmdh"*/ 	"%s",			"free -h" },
	
	{-1}
};

