#ifndef NET_CREDENTIALS_H
#define NET_CREDENTIALS_H

/******* Credentials for the Soft-AP *******/
#define AP_CREDENTIALS      "\"Erika Weather\",\"ErikaRTOS\",2,4\r\n" 
                                                       /* 2: channel,
                                                        * 4: WPA,WPA2.PSK Encryption
                                                        */
#define AP_CREDENTIALS_LEN  33 

/******* Server Config *****/
#define AP_WITH_SERVER      // Access Point with Server
#define CREDENTIALS_BY_WEP_APP

#endif