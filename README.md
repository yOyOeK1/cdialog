

# ccanvash.bin



## dependecies

 - at postmarketOs arm64

gcc, build-base, ncurses-dev, mosquitto-dev



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
./cnn_config_types.h:#define CNNATSTART 1
./cnn_config_types.h:#define CNNMQTTSUB 5
./cnn_config_types.h:#define CNNKEYBIND 7

builds clone of message with
topic and payload

Then sends it over `nudle` to `node`. 

For now some types of `node`s implemended with status:

./cnn_config_types.h:#define CNNADD 3
./cnn_config_types.h:#define CNNDIV 4
./cnn_config_types.h:#define CNNCMD 6
./cnn_config_types.h:#define CNNPRINTF 2
./cnn_config_types.h:#define CNNMQTTPUB 8
[TODO]./cnn_config_types.h:#define CNNCANVCLEAR 9
./cnn_config_types.h:#define CNNCANVPRINTF 10

`cnn_config*` files are to set what you want to build. Now it's a bOnaNzA one big test. I'm thinking to use 
`#define VARIABLES` as main switching mechanizm to decide what to build as binarry.



### TODO / FIX / KNOWN bugs

[ ] mqtth when init2 for nudles can send only after receaving first mesage. then it get's it's mqHeader struct 
[ ] ccanvas don't do correct unicode characters :(



---

If you see that this makes sense [ send me a ☕ ](https://ko-fi.com/B0B0DFYGS) | [Master repository](https://github.com/yOyOeK1/oiyshTerminal) | [About SvOiysh](https://www.youtube.com/@svoiysh)
