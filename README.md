# ErikaOs-OnlineWeatherStation
It's a tiny monitor for you local weather and music player, meaning, it shows the current temperature, the feeling like temperature, the temperature description and the time of request, as for the music, the artist and track that are currently being played on your Spotify player (_disclaimer_: it does not play or pause the track). The weather information is fetched from OpenWeatherMap.org using location based on IP-api.com. In case of Spotify, it fetches the code for the app and token (with refreshment once it's expired, 3600 s).

Two web servers were built as well, (1) the WiFi supplicant that allows the user to connect to any Access Point and (2) the Spotify Authenticator to link a Spotify account. These servers run in different modes of the WiFi module, when as a supplicant, the module works as SoftAP and station so, the user can join the WiFi network **Erika Weather**, browse to [http://192.168.4.1/](http://192.168.4.1) and set the SSID and password of the desired network and wait for connection. As Spotify Authenticator, recommended to use only when there's an internet connection and browse to [http://your-esp8266-ip/spotify](), this provides the link that will authenticate the user's Spotify account and later it will automatically fetch the token.   

## Hardware 

The main board is a _STM32f407-discovery_ using _std_ library mounted over a _discover-more_ extension with and LCD _LCD35RT_. The secondary board is an ESP8266 that interfaces through UART in the COM1 (USART6 on the _discovery_ PC6-PC7 pins) on the _std_ library. ESP8266's reset/GPIO0/GIPO2/Enable pin are fixed voltage, meaning they are not connected to any STM32's GPIOS.

## Firmware

On the seconday board, ESP8266, the _ESP8266-IDF-ATV2.2.1.0_ is running, provided by Espressif, you can find in [this link](https://gist.github.com/ckevar/4275573daf5d2d4803346ab56bf4e0fe) how to install this firmware on the ESP8266.

In the main board, the app was built based on ErikaRTOSv2, it's divided in 6 periodic tasks (code: _inc/erika_task_conf.h_):

- _Weather Update_, triggered each 10 minutes, fetches the weather information.
- _LCD In_, triggered each 20 ms, checks if the LCD has beeing touched.
- ESP8266 Poll, triggered each 40 ms, parses the incoming data of the ESP8266.
- Network, triggered each 80ms, runs the web client or the web servers.
- Spotify Update, triggered each 20s, fetches the Spotify player information.



## How to run/flash it
if the hardware is ready, The file _c_mX.bin_ can be flashed as follows:
``` bash
$ st-flash write c_mX.bin 0x8000000
```

## Recompile
In order to recompile you need to download ERIKA2.x-OS from https://www.erika-enterprise.com/index.php/download/erika-v2.x.html
Once Erika is intall, you only need the Erika-CLI not the whole Eclipse to work. So, everything usefull executable you need is under the _evidence_ folder.

### Step 1
Generate files from configuration file _conf.oil_ 

``` bash
$ erika-gen /path/where/Erika-CLI/is/installed/Erika-CLI/ conf.oil .
```

### step 1
add _usr.mk_ inside makefile

``` bash
$ nano makefile
```
in the first line write:

``` bash
$ include usr.mk
```
## step 3
You also need to install _gcc-arm-none-eabi_.
Edit usr.mk, to address where the gcc-arm-none-eabi compiler is installed
``` bash
$ nano usr.mk
```

Locate the line that starts with _GNU_ARM_ROOT_ and change it by the path where your compiler is installed.

## Requirements
- Erika2.x OS (the operating system of the board)
- gcc-arm-none-eabi (to compile the project)
- stlink (to flash the board)

