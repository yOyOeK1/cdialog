#!/bin/sh

echo "Build .h for cmachine files ... "



#./build_h_from_c.sh ./cmTools.c > ./cmTools.h
#./build_h_from_c.sh ./cmInits.c > ./cmInits.h
#./build_h_from_c.sh ./cmachine2.c > ./cmachine2.h 



fList="cmTools cmInits cmachine2 cmTime cmCanvas cmMath"
for f in `echo "$fList"`;do
	echo "//* $f .c to new .h ..."
	
	if [ "$1" = "-v" ]; then
		echo "// file ... [ $f ] "
		./build_h_from_c.sh "./""$f"".c" 
	else

		./build_h_from_c.sh "./""$f"".c" > "./""$f"".h"
		ls -alh "./""$f"".h"

	fi
done


echo "- - - DONE"
