#!/bin/sh

## config
# look in src directory for ./cdiologer_*.sh as template
xtermT="alacritty"
#
#


echo "#* ... install"

#chk if build
if test -f ./cdialog.bin; then
	echo " - bin in OK"
else
	echo " - bin not in place ... build"
	. ./build3.sh
	if test "$?" = "0"; then
		echo " build ... DONE"
	else
		echo "EE ... build faild"
		exit 1
	fi

fi


# chk PATH's
fTemp=$HOME"/.local/bin"
echo "#* ... chk PATH's "
echo $PATH | grep "$fTemp" 
if test "$?" = "0"; then
	echo " ... OK"
else
	echo "EE ... no [ $fTemp ] in your PATH"
	exit 2
fi


# chk binds and links in ~ bin ...
echo "#* ... chek .bin ..."
if test -f "$fTemp""/cdialog.bin"; then
	echo " cdialog.bin ... OK"
else
	echo " cdialog.bin ... make link"
	ln -s `pwd`"/cdialog.bin" "$fTemp""/cdialog.bin"
fi


# TODO FIX
echo "#* ... will use terminal bind to [ $xtermT ]" 
if test -f "$fTemp""/cdialoger.sh"; then
	echo " ... OK"
else
	echo " ... making link as [ cdialoger.sh ] @ [ $xtermT ]"
	if test -f `pwd`"/cdialoger_""$xtermT"".sh"; then
		ln -s `pwd`"/cdialoger_""$xtermT"".sh" "$fTemp""/cdialoger.sh"
	else
		echo " I I I  III iii ......

	no target  "`pwd`"/cdialoger_"$xtermT".sh 

	so skipping :(

		....  ... iii III  I I I"

	fi
fi


echo "#* ... mk it runnable ..."
chmod +x "$fTemp""/cdialoger.sh"
chmod +x "$fTemp""/cdialog.bin"

echo "#* ... chk templates in configs ...

------ TEMPLATE FOR $HOME/.config/i3/config START -------------
...
for_window [title="cdialoger"] floating enable, border none, move position 0 20
...
bindsym $mod+Shift+d exec $HOME/.local/bin/cdialoger.sh
...
------ TEMPLATE FOR $HOME/.config/i3/config END -------------


"


echo "#* ... DONE"
