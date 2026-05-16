#
# small helper script to compile it as it is...
#

bTarget="cmachine2.test.bin"
mainConfigData="cnn_config_data"



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

elif test "$1" = "-a";then
	echo "# ... Do all ..."
	./cmachine2Build4.sh -c
	./cmachine2Build4.sh -bh
	./cmachine2Build4.sh -b
	echo "# ... Do all ... DONE"
	exit 0

elif test "$1" = "-h";then
	echo "# ... help
 -h 	- this help
 
 -a	- do all clean, build .h, build all, run
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


gccFlagsExtra=""
if test "$CMCONFIG" = "";then
	echo "# EE no env variable CMCONFIG exit 1"
	exit 1
else
	echo "# ... will do config [ $CMCONFIG ]"
	cPath="./cnn_config_""$CMCONFIG""_data.c"
	if test -f "$cPath";then
		echo " file OK"
		mainConfigData="./cnn_config_""$CMCONFIG""_data"
	else
		echo "EE config file not there [ $cPath ]"
		exit 1
	fi
	mods=`grep '#FOR_COMPILER_MODULES_DO ' "$cPath"`
	mList=""
	mItem="0"
	for m in `echo "$mods"`;do
		if test "$mItem" = "0";then
			echo "skip first"
		else
			mList="$mList ""-D""$m=\"1\""
		fi
		mItem="1"
	done
	echo "# do modules ... [ $mList ]"
	gccFlagsExtra="$mList"


	fTarget=`grep '*cnn_target' "$cPath" | awk '{print $4}'`
	fLen=`expr length "$fTarget"`
	fLen=`expr "$fLen" - "3"`
	fTrim=`expr substr "$fTarget" 2 $fLen`
	echo "# fTarget [ $fTarget ] trim [$fTrim]"
	bTarget="$fTrim"".test.bin"

fi




bMod_mqS=`echo "$mList" | grep "CM_DO_INIT_MQTT" >> /dev/null && echo "1" || echo "0"`
echo "# ... build mqS [ $bMod_mqS ]"
#bMod_mqS="1"
bMod_wsS=`echo "$mList" | grep "CM_DO_INIT_WSSERVER" >> /dev/null && echo "1" || echo "0"`
echo "# ... build wsS [ $bMod_wsS ]"
#bMod_wsS="1"
bMod_tcpS=`echo "$mList" | grep "CM_DO_INIT_TCPSERVER" >> /dev/null && echo "1" || echo "0"`
echo "# ... build tcpS [ $bMod_tcpS ]"
#bMod_tcpS="1"
bMod_ccanvS=`echo "$mList" | grep "CM_DO_INIT_CANVAS" >> /dev/null && echo "1" || echo "0"`
echo "# ... build ccanvas [ $bMod_ccanvS ]"
#bMod_ccanvS="1"
bMod_ncurS=`echo "$mList" | grep "CM_DO_INIT_NCURSES" >> /dev/null && echo "1" || echo "0"`
echo "# ... build ncurses [ $bMod_ncurS ]"
#bMod_ncurS="1"
bMod_mouKeyS=`echo "$mList" | grep "CM_DO_MOUSEKEYS" >> /dev/null && echo "1" || echo "0"`
echo "# ... build mouse key events [ $bMod_mouKeyS ]"
#bMod_mouKeyS="1"
bMod_keyS=`echo "$mList" | grep "CM_DO_INIT_KEYBIND" >> /dev/null && echo "1" || echo "0"`
echo "# ... build ncurses [ $bMod_keyS ]"
#bMod_keyS="1"
bMod_tcpc=`echo "$mList" | grep "CM_DO_TCPCLIENT" >> /dev/null && echo "1" || echo "0"`
echo "# ... build tcpc [ $bMod_tcpc ]"
#bMod_tcpc="1"



bSrc="$mainConfigData cmCore cmTools cmInits cmMath cmAs cmLogic cmTime timeh cmdh ctermh cargs cpostprocess cmachine2"
inc=""
libsDir=""
libs="-lm"
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "
libs="-lrt -lm -lpthread"
gccFlags="-g -O3 -DDEBUG -DCPPMACHINE -DMQTT_FROM_MQNODES2 $gccFlagsExtra" 


if test "$bMod_tcpc" = "1";then
	echo "# addind module tcp client"
	#libs="$libs "
	bSrc="ctcpC $bSrc"
fi
if test "$bMod_keyS" = "1";then
	echo "# addind module keyBinds"
	#libs="$libs "
	bSrc="ckeyh $bSrc"
fi
if test "$bMod_ncurS" = "1";then
	echo "# addind module ncurses"
	libs="$libs -lcurses -lncurses -lncursesw"
	#bSrc=" $bSrc"
fi
if test "$bMod_ccanvS" = "1";then
	echo "# addind module ccanvas"
	#libs="$libs "
	bSrc="cmCanvas ccanvas $bSrc"
fi
if test "$bMod_tcpS" = "1";then
	echo "# addind module tcpS"
	#libs="$libs "
	bSrc="ctcpS ctcpS_v2 $bSrc"
fi

if test "$bMod_mqS" = "1";then
	echo "# addind module mqS"
	libs="$libs -lmosquitto"
	bSrc="mqtth $bSrc"
fi


if test "$bMod_wsS" = "1";then
	echo "# addind module wsS"
	wsLibs="../wsServer/src/*.o"
	wsInc="../wsServer/include "
	libsDir="$libsDir $wsLibs"
	inc="$inc -I""$wsInc"
	bSrc="cwsS $bSrc"
fi



oStr=" "

for f in `echo "$bSrc"`;do
	echo -n "* file [ $f ] "
	if test -f "$f"".o"; then
		echo "file exists"
	else
		echo " build ..."
		gcc $inc $gccFlags -c "$f"".c"
	

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

