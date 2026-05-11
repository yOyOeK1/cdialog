#
# small helper script to compile it as it is...
#

if test "$1" = "-c";then
	echo "# ... clean *.o"
	rm ./*.o
	exit 0

elif test "$1" = "-bh";then
	echo "# ... build new *.h"
	./cmachine2Build_H.sh
	exit 0

elif test "$1" = "-vh";then
	echo "# ... view *.h"
	./cmachine2Build_H.sh -v
	exit 0

elif test "$1" = "-b";then
	echo "# ... build ..."

elif test "$1" = "-h";then
	echo "# ... help
 -h 	- this help

 -b	- build all
 -c	- as clean *.o
 -bh	- build new *.h
 -vh	- viem *.h

	"
	exit 0

else
	echo "no arg set try -h"
	exit 0
fi




bTarget="cmachine2.test.bin"
bSrc="cnn_config_data cmTools cmInits cmCanvas ctcpS ctcpS_v2 cmMath cmAs cmLogic cmTime timeh ckeyh cmdh ctermh ccanvas cargs cpostprocess mqtth cmachine2"
inc=""
libsDir=""
libs="-lm"
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "
libs="-lmosquitto -lrt -lm -lpthread -lcurses -lncurses -lncursesw "
gccFlags="-g -O3 -DDEBUG -DCPPMACHINE -DMQTT_FROM_MQNODES2" 

oStr=" "

for f in `echo "$bSrc"`;do
	echo -n "* file [ $f ] "
	if test -f "$f"".o"; then
		echo "file exists"
	else
		echo " build ..."
		gcc $gccFlags -c "$f"".c"
	

		if test "$?" = "0"; then
			echo "OK"
		else 
			echo "faild ERROR"
			exit 1
		fi
	fi
	oStr="$oStr ""$f"".o"
done

echo "oStr ... [$oStr]"


echo "#* ... make last"
mv "$bTarget" "$bTarget"".last"

echo "#* ... build ..."
###	-Wimplicit-function-declaration \
###	-Wno-error=int-conversion \
##gcc -O0 \
##	-DDEBUG -DCPPMACHINE -DMQTT_FROM_MQNODES2 \
##	-fno-builtin \
##-o $bTarget $bSrc $inc $libsDir $libs
##
echo "making maing link build ..."

echo " $gccFlags -o $bTarget $oStr $inc $libsDir $libs"
gcc $gccFlags -o $bTarget $oStr $inc $libsDir $libs
#gcc $gccFlags $oStr -o "$bTarget"".bin5678"

if test "$?" = "0"; then
	echo "OK------------------------------"
	ls -alh $bTarget
else
	echo "ERROR --------------------------"
	exit 1
fi

time ./"$bTarget" $*

