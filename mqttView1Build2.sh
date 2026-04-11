#
# small helper script to compile it as it is...
#

bTarget="mqttView1.test.bin"
bSrc="cargs.c cpostprocess.c mqttView1.c"
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "
libs="-lmosquitto -lrt -lm -lpthread -lcurses -lncurses -lncursesw "

echo "#* ... make last"
mv "$bTarget" "$bTarget"".last"

echo "#* ... build ..."
#	-Wimplicit-function-declaration \
#	-Wno-error=int-conversion \
gcc -DDEBUG \
	-fno-builtin \
-o $bTarget $bSrc $inc $libsDir $libs

if test "$?" = "0"; then
	echo "OK------------------------------"
	ls -alh $bTarget
else
	echo "ERROR --------------------------"
fi

echo "#* ... for debugging run"
echo '# mosquitto_sub -t "and/#" -h "hu" -p 10883 -V mqttv311 -d'
echo "#"

#./cMqtt2Bar
