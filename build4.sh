#
# small helper script to compile it as it is...
#

bTarget="cdialog.bin"
bSrc="stateMachine.c dogh.c timeh.c cmdh.c fileh.c mainBuild2.c"
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "
libs="-lmosquitto -lrt -lm -lpthread -lcurses -lncurses -lncursesw "

echo "#* ... make last"
mv "$bTarget" "$bTarget"".last"

echo "#* ... build ..."
gcc  \
	-fno-builtin \
	-Wimplicit-function-declaration \
	-Wno-error=int-conversion \
-o $bTarget $bSrc $inc $libsDir $libs

if test "$?" = "0"; then
	echo "OK------------------------------"
	ls -alh $bTarget
else
	echo "ERROR --------------------------"
fi
#./cMqtt2Bar

## changes
# add stateMachine.c

