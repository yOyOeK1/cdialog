
#define OVEN_NAME_MAX 512


struct OvenRecipe{
	int dirId;// = -1;	
	char mediumProtocal;// = "cmd";
    	char topicAddress[OVEN_NAME_MAX];// = "echo 'Pwd: [ '`pwd`' ] ';";
    	char rName[OVEN_NAME_MAX];// = "Home of script - pwd";
    	char valType[OVEN_NAME_MAX];// = "raw";
    	char wrapType[OVEN_NAME_MAX];// = "toast";
    	bool liveSes [OVEN_NAME_MAX];// = false;
    	float intervalEverySec[OVEN_NAME_MAX];//  = -1.0;
    	//"iterator" = -1;
    	bool sharedSession[OVEN_NAME_MAX];//  = true;
    	bool onlyWhenImOnline[OVEN_NAME_MAX];//  = false;

};

struct OvenDir{
	int id;
	char pathBase[OVEN_NAME_MAX];
	char ovenDir[OVEN_NAME_MAX];
	char dirPathScan[OVEN_NAME_MAX];
	char layout[OVEN_NAME_MAX];// = "default" ;
	//OvenRecipe *recipes;
	int *recipes;
	int recipesCount;// = 0;
};

struct RECIPE {
	int id;
	int cookBook_id;
	char name[256];
	char fPath[1024];
	bool ok;

};

