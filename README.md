

# ccanvash.bin



## dependecies

 - at postmarketOs arm64

gcc, build-base, ncurses-dev, mosquitto-dev, cjson-dev



## asBar start

Starting it as i3bar. Cut out from my .config/sway/config file 

```config
status_command /home/user/Apps/cdialog/ccanvash.bin -asBar -row=1 -col=100
```

## config.h

File `config.h` is a main config file use in building / compiling process.
What you compile depend on target aplication you whant to build.
Current builders have sufix `...BuildN.sh` where N is a number / version / variant.



## modules / files

There is many files in this project. Loking at them in sens of files with extension of *.c . Many of them represent a functionality / work. Example can be file `dogh.c`. It's set of functions and variables alowing to play with watchDog's concept. files, mqtt, cmd, time, ...


### mqttView2

On event / message published at mqtt viewer. It use ccanvas to have `terminal buffor` to draw blocks of text and data. This one now use `config.h` to build it subscription list. How to source / postprocess data is in same place.


To run it:
```bash
./mqttView2.test.bin -chFill=_ -col=60 -row=10
```

Current a.k.a. sceenshot of app running:
![](./examples/screenshot_mqttView2_2504.png)


### cmachine2

Current work is at this file. It's semi node-red a.k.a. c language / hardcoded set of tools. Instade of nice interactive ui interface hosted by node-red. In this case it is puzzle of id and define types of `nodes` / workers. Same like in node-red flow of event:

##### starters

./cnn_config_types.h:#define CNNATSTART 1
./cnn_config_types.h:#define CNNMQTTSUB 5
./cnn_config_types.h:#define CNNKEYBIND 7
./cnn_config_types.h:#define CNNTCPSERVER 24


all of them should have `cnn_Msg` define as there default values on event. 
- CNNMQTTSUB payload is populated with message comming from subscription.

then it builds clone of message with
topic and payload
sends it over to `nudle` to `node`. 

For now some types of `node`s implemended with status:

./cnn_config_types.h:#define CNLIF 17
./cnn_config_types.h:#define CNNADD 3
./cnn_config_types.h:#define CNNDIV 4
./cnn_config_types.h:#define CNNCMD 6
./cnn_config_types.h:#define CNNPRINTF 2
./cnn_config_types.h:#define CNNMQTTPUB 8
./cnn_config_types.h:#define CNNCANVCLEAR 9
./cnn_config_types.h:#define CNNCANVPRINTF 10
./cnn_config_types.h:#define CNNCANVRENDER 11
./cnn_config_types.h:#define CNNTIMESINCE 12
./cnn_config_types.h:#define CNITIMESTAMP 15
./cnn_config_types.h:#define CNITIMENOWTT 16
./cnn_config_types.h:#define CNIKEYMOUSE_ENABLE 21
./cnn_config_types.h:#define CNIKEYMOUSE_DISABLE 22
./cnn_config_types.h:#define CNNPROGRESSBAR 13
./cnn_config_types.h:#define CNNTCPSPUB 25

`cnn_config*` files are to set what you want to build. Now it's a bOnaNzA one big test. I'm thinking to use 
`#define VARIABLES` as main switching mechanizm to decide what to build as binarry.


### build h from c

Bash script to build .h files from .c files.
In cmachine2 there is wrapper to do more ... can do:
- OUTLINE of files with `-v` argument and can be use as
```bash
./cmachine2Build_H.sh -v
```

### building one

To build cmachine2 Build4
```bash
./cmachine2Build4.sh -bh
./cmachine2Build4.sh -b
```
It's a devToy so it's starting after successfully build.


### start nudle - xdev

Nudle can by start from one of build in types (look section cmachine2 - starters).
Or
in code
```c
    int nId = 1;            // node id 
    int channelNo = 1;      // it will emit at channel 1
    cnn_Msg msgT = { -1, "and/myTest/topic", "my payload" };
    msgT.nIndex = 0;        // to look for what entrens in nudle definition
    cm_doWorkAt_byNId( nId, CNNTYPENO, channelNo, &msgT );
```
This will look in `cnnNudles` for chains to start.


### NOTES

sources / reading:
* cJSON:
https://www.geeksforgeeks.org/c/cjson-json-file-write-read-modify-in-c/

### TODO / FIX / KNOWN bugs

[ ] hub node - empty node doing nothing.
[ ] cnn_Msg should have 0/1 if it's as pointer or no
    so if not then it's as not changed
    so as pointer can be use as variable

[ ] mqtth when init2 for nudles can send only after receaving first mesage. then it get's it's mqHeader struct 
[ ] ccanvas don't do correct unicode characters :(



---

If you see that this makes sense [ send me a ☕ ](https://ko-fi.com/B0B0DFYGS) | [Master repository](https://github.com/yOyOeK1/oiyshTerminal) | [About SvOiysh](https://www.youtube.com/@svoiysh)
