#
# small helper script to compile it as it is...
#

bTarget="cmachine2.test.bin"
bSrc="cnn_config_data.c cmTools.c cmInits.c timeh.c ckeyh.c cmdh.c ctermh.c ccanvas.c cargs.c cpostprocess.c mqtth.c cmachine2.c"
inc=""
libsDir=""
libs="-lm"
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "
libs="-lmosquitto -lrt -lm -lpthread -lcurses -lncurses -lncursesw "

echo "#* ... make last"
mv "$bTarget" "$bTarget"".last"

echo "#* ... build ..."
#	-Wimplicit-function-declaration \
#	-Wno-error=int-conversion \
gcc  \
	-DDEBUG -DCPPMACHINE -DMQTT_FROM_MQNODES2 \
	-fno-builtin \
-o $bTarget $bSrc $inc $libsDir $libs

if test "$?" = "0"; then
	echo "OK------------------------------"
	ls -alh $bTarget
else
	echo "ERROR --------------------------"
	exit 1
fi

time ./"$bTarget" $*

