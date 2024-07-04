#ifndef NET_CREDENTIALS_H
#define NET_CREDENTIALS_H

/******* Credentials for the Soft-AP *******/
#define AP_CREDENTIALS      "\"Erika Weather\",\"ErikaRTOS\",1,4\r\n" 
                                                       /*1: channel,
                                                        * 4: WPA,WPA2.PSK Encryption
                                                        */
#define AP_CREDENTIALS_LEN  (sizeof(AP_CREDENTIALS) - 1)

/******* Server Config *****/
#define AP_WITH_SERVER      // Access Point with Server
#define CREDENTIALS_BY_WEP_APP

#endif
