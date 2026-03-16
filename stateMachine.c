
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "cmdh.h"
#include "covenStructs.h"

char SM_Now[512] = "root";


struct SMNode{
	int id;
	int parentId;
	char name[512];
	char action[512];
	char opts[512];

};

int smclLine = 1;
void SM_cl( char *msg ){
	mvprintw( 2+(smclLine%3), 2, "%03iSM] %s\n", smclLine, msg );
	smclLine++;
}

char* SM_getState(){
	return SM_Now;
}

int SM_setState( char *nState ){
	strcpy( SM_Now, nState );
	SM_cl("set new state !");
	SM_cl( nState );
}



char lastChar = ' ';
bool SM_chkCh( char ch ){
	if( ch == 's' && lastChar == 's' && strcmp( SM_Now, "root" ) == 0 ){
		clear();
		SM_cl("SM magig spell ...\n");
		SM_setState( "settings" );
		return true;
	}else if( strcmp( SM_Now, "settings" ) == 0 ){
		if( ch == 'q' ){ 
			clear();
			SM_cl("SM magig spell ... quit\n");
			SM_setState( "root" );
		} else if ( ch == 'c' ){
			clear();
		} else if ( ch == 'C' ){
			clear();
			mvprintw( 1,5, "[cpusInfo] [%s]", cmd_to_chars(
				"/home/yoyo/.viteyss/oven/oMachine/cpusInfo.sh"
				) );
		} else if ( ch == '2' ){
			clear();
			mvprintw( 1,5, "[power save] [%s]", cmd_to_chars(
				"sudo /home/yoyo/.viteyss/oven/oMachine/powerSave.sh"
				) );
		} else if( ch == '3' ){
			clear();
			mvprintw( 1,5, "[power FULL] [%s]", cmd_to_chars(
				"sudo /home/yoyo/.viteyss/oven/oMachine/powerFull.sh"
				) );

		} else if ( ch == '1' ){
			clear();
			mvprintw( 1,5, "[wifi 1] [%s]", cmd_to_chars(
				"sudo /home/yoyo/.viteyss/oven/oMachine/wifiSet.sh 1"
				) );
		} else if( ch == '0' ){
			clear();
			mvprintw( 1,5, "[wifi 0] [%s]", cmd_to_chars(
				"sudo /home/yoyo/.viteyss/oven/oMachine/wifiSet.sh 0"
				) );
		}else{
			//clear();
		}
		return true;
	}
	
	lastChar = ch;
	return false;
}

struct SMNode SMN_getByName( char *nname ){
	

}

int sms = 10;
struct SMNode SMNs[10];


char *SM_children( int parentId ){
	for( int n=0; n<sms; n++ ){
		if( SMNs[n].parentId == parentId )
			mvprintw( 2+n, 2, "%i. pId:[%i] name [%s]", n+1, SMNs[n].parentId, SMNs[n].name );
	}

	return NULL;
}


struct SMNode SMRoot = { 1, -1, "root" };
int SM_init( char *blameWho ){

	char tDeb[512];
	snprintf( tDeb, sizeof(tDeb), "blame init:[%s] current state:[%s]\n", blameWho, SM_Now);
	SM_cl( tDeb );

	SMNs[0] = SMRoot;
	struct SMNode ktct = { 1, 1, "key to console true", "setBool", true };
	SMNs[1] = ktct;
	struct SMNode ktcf = { 2, 1, "key to console false", "setBool", false };
	SMNs[2] = ktcf;
	//SMRoot.id = 0;
	//SMRoot.parentId = -1;
	//SMRoot.name = "default";

}
/*
int main(int argc, char* argv[]) {






	printf("#* ... state machine test TEST START\n");


	printf("#* ... state machine test TEST END\n");

	return 0;

}
*/
