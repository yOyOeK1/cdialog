#include <ncurses.h>
#include <stdlib.h>

#include "covenStructs.h"

int main(){

	struct RECIPE recipes[5];
	recipes[0].id = 1;
	strcpy( recipes[0].name, "test static recipe" );
	recipes[0].ok = true;

	recipes[1] = ( struct RECIPE ){ .id=2, .name="from all at once", "", .ok=true };
	recipes[3] = ( struct RECIPE ){ 2, -1, "from all at once", "", true };

	printf("#co ... coven ... test\n");
	printf("recipe[0] ... (%i) id: %i | name: %s\n",   
		recipes[0].ok, 
		recipes[0].id,
		recipes[0].name
	);
	printf("recipe[1] ... (%i) id: %i | name: %s\n",   
		recipes[1].ok, 
		recipes[1].id,
		recipes[1].name
	); 
	printf("#co2 ... coven ... test\n");

	return 0;
}
