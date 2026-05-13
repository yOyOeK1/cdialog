#
# small helper script to compile it as it is...
#

bTarget="cwsS.test.bin"
bSrc="cwsS.c"
#inc=""
#libsDir=""
#libs="-lm"
inc="-I/home/user/Apps/wsServer/include "
wsO=" \
/home/user/Apps/wsServer/src/utf8.o \
/home/user/Apps/wsServer/src/handshake.o \
/home/user/Apps/wsServer/src/ws.o \
/home/user/Apps/wsServer/src/sha1.o \
/home/user/Apps/wsServer/src/base64.o"
libsDir="-L/home/user/Apps/wsServer/src "
libs="-lrt -lm -lpthread -lcurses "

echo "#* ... make last"
mv "$bTarget" "$bTarget"".last"

echo "#* ... build ..."
#	-Wimplicit-function-declaration \
#	-Wno-error=int-conversion \
#gcc  \
#	-DDEBUG -DCPPMACHINE \
#	-fno-builtin \
#-o $bTarget $bSrc $inc $libsDir $libs
#
gcc $inc -c $bSrc && \
gcc $libsDir $wsO cwsS.o -o $bTarget



if test "$?" = "0"; then
	echo "OK------------------------------"
	ls -alh $bTarget
else
	echo "ERROR --------------------------"
	exit 1
fi

time ./"$bTarget" $*

