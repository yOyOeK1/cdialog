
#include <dialog.h>
#include <stdio.h>
//#include <unistd.h>

//#define SCREEN_BG	COLOR_BLACK

int main(void){

	int status;
	init_dialog( stdin, stdout );
	status = dialog_yesno(
			"hello this is dialog",
			"happy?",
			0,0
			);

	char msgStr[100];
	snprintf( msgStr, 100, "Was selected [ %i ]", status );
	dialog_msgbox(
			msgStr,
			"Nice ! PaPa", 
			//"Main papa message",
			6,30,10
			);

	end_dialog();
	return status;


}
