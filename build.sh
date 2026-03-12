echo "#* ... buisg with dialog ..."

fIn="$1"
test "$#" != "1" && echo "EE need arg as main.c" && exit 1



gcc -DBUILDBEBUG  "$fIn" -lcurses -lncurses -ldialog -lncursesw -lm -o "$fIn"".bin"
#gcc main.c -lcurses -lncurses -ldialog -lm -o cdialog001_2
#gcc main.c -lm -o cdialog001_3
#gcc main.c -ldialog -lm -o cdialog001_4
#gcc main.c -lncursesw -ldialog -lm -o cdialog001_5
#gcc main.c -lcurses -lncurses -ldialog -lncursesw -lm -o cdialog001

echo "#* .. DONE [ $fIn"".bin ]"
