# ErikaOs-OnlineWeatherStation
![image](data/img/ui_figma.png "Design on Figma")

It's a tiny monitor for you local weather and music player, meaning, it shows the current temperature, the feeling like temperature, the temperature description and the time of request, as for the music, the artist and track that are currently being played on your Spotify player (_disclaimer_: it does not play or pause the track). The weather information is fetched from [OpenWeatherMap.org](openweathermap.org) using location based on [IP-API.com](ip-api.com). In case of [Spotify](https://developer.spotify.com/), it fetches the code for the app and token (with refreshment once it's expired, 3600 s).

Two web servers were built as well, (1) the WiFi supplicant that allows the user to connect to any Access Point and (2) the Spotify Authenticator to link a Spotify account. These servers run in different modes of the WiFi module, when as a supplicant, the module works as SoftAP and station so, the user can join the WiFi network **Erika Weather**, browse to [http://192.168.4.1/](http://192.168.4.1) and set the SSID and password of the desired network and wait for connection. As Spotify Authenticator, recommended to use only when there's an internet connection and browse to [http://your-esp8266-ip/spotify](), this provides the link that will authenticate the user's Spotify account and later it will automatically fetch the token.   

You can skip this documentation and jump straight to the [compile](#Compile) section.

## Hardware 

The main board is a _STM32f407-discovery_ using _std_ library mounted over a _discover-more_ extension with and LCD _LCD35RT_. The secondary board is an ESP8266 that interfaces through UART in the COM1 (USART6 on the _discovery_ PC6-PC7 pins) on the _std_ library. ESP8266's reset/GPIO0/GIPO2/Enable pin are fixed voltage, meaning they are not connected to any STM32's GPIOS.

## Firmware

On the seconday board, ESP8266, the _ESP8266-IDF-ATV2.2.1.0_ is running, provided by Espressif, you can find in [this link](https://gist.github.com/ckevar/4275573daf5d2d4803346ab56bf4e0fe) how to install this firmware on the ESP8266. This firmware version is important in order to establish SSL connections, the ATv1.6.x supports SSL, but from tests, it's seen that [*.spotify.com:443]() is virtually hosted on Google, so the SSL uses SNI and the ATv1.6.x does not support SNI.

---

In the main board, the app was built based on ErikaRTOSv2, which is divided in 6 periodic tasks (code: _inc/erika_task_conf.h_): Weather Update, Spotify Update, ESP8266 Poll, LCD In and Network.

- __Weather Update__

  Triggered each 10 minutes, it triggers an internal event that invokes a change in the client of the task _Network_ to update the weather information. From experiments, the temperature information doesn't get updated faster than 10 minutes. So, the server only gives repetitive information when requested every 45s or 180s.

    

- __Spotify Update__

  Triggered each 20s, it triggers an internal event that invokes a change in the client of the task _Network_ in order to fetch the Spotify player information. It's being seen that establishing a SSL connection to [api.spotify.com:443](https://api.spotify.com) on the ESP8266 takes 5 seconds + 2 seconds of transmitting the data through UART to the STM32 and parsing it. Spotify replies a minimum of ~7Kbytes: 1Kbytes of HTTP/1.1 header + 6Kbytes of JSON data. So, it's 7 seconds only one request. This can be reduce by not closing the SSL connection, unfortunately this option wasn't not explore in this project. The other option is to speed the UART, but it was not a good idea because the ESP8266 got "bricked".

  

- __ESP8266 Poll__

  Triggered each 40 ms, parses the incoming data of the ESP8266. 40ms has being chosen because initially the circular buffer where the DMA is placing the incoming data was 1024 bytes size, and at 115200 bauds with 1 start bit  and 1 end bit on the UART, 10240 bits will fill the buffer in 88ms, to avoid overlapping data, it's better to empty it as soon as possible,  so (by Nyquist) 40ms will do the job. that buffer dimension works perfect when fetching weather information because the data barely reaches 1Kbytes. It's a different story for Spotify where sometimes it throws 13Kbytes for a song. So, the initial buffer dimension isn't enough. But choosing a larger period will make other processes slowly, like when settings up the ESP8266,  are average 14 bytes size (~1.2ms). So, the current mechanism doesnt try to empty the buffer but just wait for the content of the HTTP, the header containing larger amount of cookies is discarded.  

   

- __LCD In__

  Triggered each 20 ms, it checks if the LCD has being touched. An event-triggered filter was implemented in order to reduce the noise of the coordinates when touched. The following figure shows the raw data on the x axis when touched. Y axis does not need to be filtered because our icon size are 30 pixels and the standard deviation of the Y axis is smaller than that.

  

- __Network__, triggered each 80ms, runs the web client or the web servers upon request of the previous tasks.

  The Fig 1. shows the overall FSM of the network 

```mermaid
---
title: Fig 1. Network Overall FSM
---
stateDiagram-v2 

[*] --> SuperState
SuperState --> ON_HOLD
ON_HOLD --> SuperState : esp8_status == OK
ON_HOLD --> ERROR : esp8_status == ERROR
ERROR --> SuperState : f(prev_state)
SuperState --> READY : 
READY --> SuperState : x_update | wifi_supplicant | spotify
note left of SuperState : = INITIAL_SETUP, NETSTATUS, CLIENT, SERVER, AP

```

 ## Future Improvements

1.  Not close the SSL connection with Spotify, it takes 5 seconds.

## How to run/flash it
if the hardware is ready, The file _c_mX.bin_ can be flashed as follows:
``` bash
$ st-flash write c_mX.bin 0x8000000
```

## Compile
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
- ESP8266-IDF-ATV2.2.1 firmware
- Erika2.x OS (the operating system of the board)
- gcc-arm-none-eabi (to compile the project)
- stlink (to flash the board)

