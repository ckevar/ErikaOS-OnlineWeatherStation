# ErikaOs-OnlineWeatherStation
It drags weather information from OpenWeather.org using location based on ip-api.com.
## Hardware 
It's an _STM32f407-discovery_ using _std_ library mounted over a _dicover-more_ extension board. 
The ESP8266 is connected through UART in the COM1 (USART6 on the _discovery_) on the _std_ library. ESP8266's reset/GPIO0/GIPO2/Enable pin are fixed voltage, meaning they are not connected to any STM32's GPIOS.

## How to run it

### Step 1
Generate files from configuration file _conf.oil_ 

``` bash
$ erika-gen /path/where/Erika-CLI/is/installed/Erika-CLI/ conf.oil .
```

### step 1
add _usr.mk_ inside makefile

``` bash
$ nano makfile
```
in the first line write:

``` bash
$ include usr.mk
```
## step 3
Edit usr.mk, to address where the gcc-arm-none-eabi compiler is installed

