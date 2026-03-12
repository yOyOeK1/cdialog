
#include <dialog.h>

int main(void){

	int status;
	init_dialog( stdin, stdout );
	status = dialog_yesno(
			"hello this is dialog",
			"happy?",
			0,0
			);
	end_dialog();
	return status;


}
