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
	{ 0, "w",	0,/*"cmdh"*/	"%s",	"whioami" },
	{ 0, "f",	0,/*"cmdh"*/ 	"%s",	"free -h" },
	{-1}
};

