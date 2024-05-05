
/*

  Copyright 2019, 5G HUB

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
  associated documentation files (the "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
  following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial
  portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
  TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

#include <board.h>
#include "wiring_private.h"

//#define DSerial Serial
#define DSerial SerialUSB
#define ATSerial Serial1

// it is importatn to define this var
// because it defines and give the program the 
// ability to use the certificate
#define USE_CERT

#ifdef USE_CERT
// **********************************new *******************************

// this is the amazon root 1 CA certificate
 char pem_CA[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n" };

// **********************************new *******************************

//this is the device certificate from aws
/* Fill your certificate.pem.crt wiht LINE ENDING */
 char pem_cert[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUZPN4eHjWKsyvBzVx+n9eqtgq2+UwDQYJKoZIhvcNAQEL\n\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDIxMTE2MjEy\n\
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANjBgMOyyPh1GjSp+Vli\n\
IUPxceit19bY/7C8IrvKOy5fEHMXDk3x912PGm9AzMh60WbZDwaR86AZq8tNN+ri\n\
ujz9eHrpZPWfrmvtM+zgRoKPwH/aM8On+3NrWBsOkMCnzRSbrYYtas5vJ4WxijTn\n\
YJ2mBaeXF7bg1OEJnZsRaqcTZVzXqrddlUWiX5bhtltA51W0M25XapWKF8gASpqr\n\
DMaB9IyRiaM7W3+5TPN8DVCR331ahuZUuHuzRWVkewBWnCxCXhilSL7qZTM0OAWF\n\
b2y23yww5nT0ZSgQ93OG0A5tNpvmJZSUltD7wlsRuHsCcdWAMtedRj4iPWCP6o14\n\
VisCAwEAAaNgMF4wHwYDVR0jBBgwFoAUF3O0vJjrTr8vaCA+p9HjvIXON7gwHQYD\n\
VR0OBBYEFEvby02nhRJ4tP/tbqe47dMLMhnAMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCIN7T3HRSOGN3aGz/nwsdqsnUZ\n\
IyW9PhSTB+eris9kdQIh8UWxJOIEXJnsFIcNInraS+c+TPoX6+r+UGeD4MxHRlCJ\n\
86gIU4HNvPQaFsMH9Sb/T49QZnPfgCcDu+/iwkK2I2RTQswxW0r7iVB3AvmEuy3G\n\
cRZ2athy9exG6wnWIjODTa74TQjhCZ8/3IlzgdJ0gUb8dZ8JCLEnJqpknw+7pe51\n\
YYdh2HQ6hR0Pdj0mkibYAIAXHK5z8s1cLZsNhJIciG97ui9bdR9o8OXgUJRylSW5\n\
AaF/2Au3VRMlFNKPrc05/Gz7Ea+X9Cf1O5YeyDoY21WTyh5i9A5DS+1/2O4a\n\
-----END CERTIFICATE-----\n" };


// **********************************new *******************************
/* Fill your private.pem.key wiht LINE ENDING */
// this is the private key certificate from aws

 char pem_pkey[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEpAIBAAKCAQEA2MGAw7LI+HUaNKn5WWIhQ/Fx6K3X1tj/sLwiu8o7Ll8QcxcO\n\
TfH3XY8ab0DMyHrRZtkPBpHzoBmry0036uK6PP14eulk9Z+ua+0z7OBGgo/Af9oz\n\
w6f7c2tYGw6QwKfNFJuthi1qzm8nhbGKNOdgnaYFp5cXtuDU4QmdmxFqpxNlXNeq\n\
t12VRaJfluG2W0DnVbQzbldqlYoXyABKmqsMxoH0jJGJoztbf7lM83wNUJHffVqG\n\
5lS4e7NFZWR7AFacLEJeGKVIvuplMzQ4BYVvbLbfLDDmdPRlKBD3c4bQDm02m+Yl\n\
lJSW0PvCWxG4ewJx1YAy151GPiI9YI/qjXhWKwIDAQABAoIBAGeCADtz5QTA5wK/\n\
KJPGiJwpcHvsiGXQuklrjiqfKCO8wd4z5GDUa4wCCl2WVDRochbrEIHSsMSDfcZX\n\
2ZwRKV52rFIFonCpEGH5pBI6B3HRs9taF94XGbzERg6lpfpaJ1TwAq1QgvCRpA3z\n\
+kvJMhoWbhzZyjlKpF3SebDTYFrnxoqpxKPI/61sefg/x+gFoy7pu3cZ9rGeTM/R\n\
M2tAGx05er72YjEonz6TjOaEEkVRb0NQNQcIePeC3KI5QdOds+9pCYhevFYIX6iX\n\
iz37c6etfXB5pI/OMTV2pZVQNXyArheh0g416+fXIcZ0NF5BlG+64MeOPk+VyH7B\n\
u+R6pgECgYEA/0gIRwqM1t0l7d3lSCV0+QWiSvAjm4mv1maRFAiDYYTgbE86z01U\n\
XNBiYAbe4n8AC4YnPzc+eEmhOJtsP1dtaDWzyQyKdWJmmZU9fU4iD8ti8XrOMEvD\n\
eIXpe7YXK6GFYT7PfauP+vx3s94RsMzrzLv6cYdWaKUIP+Y/PXY5lj8CgYEA2V21\n\
FpttgkgwvEkBJBGQKIRQ6DlyQZoT2urfvjDh/TVr7/U3C65JzjNfuz0YxsAAYjFQ\n\
qN45U5DcfISvsViODJeQNeLw597VBl+8t+w1a+hBTUBg+Av7hGxt79zuPsJRwlFw\n\
4ia6UT9J3hUp9CisetCg184PUyU9ZHFU6HWOPRUCgYEA9W4rhyF9hpXXgXl0lohs\n\
jX39Kk717PPTOi4iDUCiD3/QxFDoGaYfFZzC98+jOd8gC/ROh1h1lvAzMFk9GSjU\n\
5vu6ffCwrWqNedsh4vbbiJPh7IhE8+njZFxavbWzUR9ZPMVGd2waYROZgjRejbx2\n\
d7/CaKPVT4ZbCBQ1eMHRW8ECgYAed5YEXzDQTBIYshro1VVheHpmsnajX1ddHgLS\n\
g8OJXE2Oys42Yu2Ra34FnqC0awEiwkrOAKgEYI+nHGoL75+pgC0EgJTHy2IMjKrF\n\
FOTABUPx8g4ldniArToTnuH+Bfqzw/qQmGERNk/CQzEoOfNDG68P0KAxRUz/oSsH\n\
kkKnqQKBgQDHm5MdHVgLx9n/WZAYl0NLL8Q7i8X1+iYczGa8ITjRMWqOWuLa3Rex\n\
suEbZizpXprMVgdC1H+RcTXskVauNz4xK3U+zz+WOu+8Cs9llpViR/HGjbFQcChK\n\
AN65r7jtGNZRadgn7r9SCi1kpqIFA3VI0RsYmlNf5dvH5PcrjCfI8Q==\n\
-----END RSA PRIVATE KEY-----\n"
                        };

#endif


// at&t 5G CONNECTION 
#define HOLOGRAM

#ifdef HOLOGRAM
char APN[] = "hologram";
char LOGIN[] = "";
char PASSWORD[] = "";
#endif


// this sets up the uart. 
Uart mySerial2(&sercom1, MOSI, SCK, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM1_Handler()
{
  mySerial2.IrqHandler();
}



// this is the mqtt server where the 5g module thing resides
// this is the ENDPOINT
char mqtt_server[] = "aqfjn3nnqy4qw-ats.iot.us-west-1.amazonaws.com";

// this is the MQTTS port that is often used
//either 1883 , 443, 8883
unsigned int mqtt_port = 8883;

// this clinet ID. this info should have been established 
// when we created the "thing" in AWS iot core

char mqtt_client_id[] = "5G_Module_thing";
unsigned int comm_pdp_index = 1;  // The range is 1 ~ 16
unsigned int comm_ssl_index = 1;  // The range is 0 ~ 5
unsigned int comm_mqtt_index = 1; // The range is 0 ~ 5

//mqtt version
Mqtt_Version_t version = MQTT_V3;
//Mqtt_Version_t version = 5;
//mqtt QOS
Mqtt_Qos_t mqtt_qos = AT_MOST_ONCE;

_5G_NB_IoT_MQTT _5GNBIoT(ATSerial, DSerial);

void setup() {
  DSerial.begin(115200);
  

  
  // This is UART #1
  Serial.begin(9600); 
 


  while (DSerial.read() >= 0);
  DSerial.println("This is the _5GNBIoT Debug Serial!");
  delay(1000);
  ATSerial.begin(115200);
  while (ATSerial.read() >= 0);
  delay(1000);
  // Initialize module 
  while (!_5GNBIoT.InitModule());

  _5GNBIoT.SetDevCommandEcho(false);

  char inf[64];
  //get the dev info
  if (_5GNBIoT.GetDevInformation(inf)) {
    DSerial.println(inf);
  }

  // if there is APN error, it will display the following problem
  char apn_error[64];
  while (!_5GNBIoT.InitAPN(comm_pdp_index, APN, LOGIN, PASSWORD, apn_error)) 
  {
    DSerial.println(apn_error);
  }
  DSerial.println(apn_error);

#ifdef USE_CERT
  char ssl_error[128];
  while (!_5GNBIoT.InitSSL(comm_ssl_index, pem_CA, pem_cert, pem_pkey, ssl_error)) {
    DSerial.println(ssl_error);
  }
  DSerial.println(ssl_error);

#else
  char ssl_error[128];
  while (!_5GNBIoT.InitSSL(comm_ssl_index, "", "", "", ssl_error)) {
    DSerial.println(ssl_error);
  }
  DSerial.println(ssl_error);
#endif


// version is 5 
// you could use the version 
  while (!_5GNBIoT.SetMQTTConfigureParameters(comm_mqtt_index, comm_pdp_index, version, 150, SERVER_STORE_SUBSCRIPTIONS)) {
    DSerial.println("\r\nConfig the MQTT Parameter Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }
  
  DSerial.println("\r\nConfig the MQTT Parameter Success!");
 

  while (!_5GNBIoT.SetMQTTEnableSSL(comm_mqtt_index, comm_ssl_index, true)) {
    DSerial.println("\r\nEnable the SSL Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }
  DSerial.println("\r\nEnable the SSL Success!");

  while (_5GNBIoT.OpenMQTTNetwork(comm_mqtt_index, mqtt_server, mqtt_port) != 0) {
    DSerial.println("\r\nSet the MQTT Service Address Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }
  DSerial.println("\r\nSet the MQTT Service Address Success!");
  

  while (_5GNBIoT.CreateMQTTClient(comm_mqtt_index, mqtt_client_id, "", "") != 0) {
    DSerial.println("\r\nCreate a MQTT Client Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }
  DSerial.println("\r\nCreate a MQTT Client Success!");
 

  // the topic is motor_control
  while (_5GNBIoT.MQTTSubscribeTopic(comm_mqtt_index, 1, "motor_control", mqtt_qos) != 0) {
    DSerial.println("\r\nMQTT Subscribe Topic Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }
  DSerial.println("\r\nMQTT Subscribe Topic Success!");
    
  DSerial.println("\r\n finished done setting up.....");

}

void loop() 
{

  // this is used to receive data from aws server to 
  // then send it down to the UART to the FPGA
  char mqtt_recv[128];
  char *sta_buf;
  Mqtt_URC_Event_t ret = _5GNBIoT.WaitCheckMQTTURCEvent(mqtt_recv, 2);
  switch (ret)
  {
    case MQTT_RECV_DATA_EVENT:
      sta_buf = strstr(mqtt_recv, "\",\"");

      //send data down the UART
      DSerial.println("\r\n before sending");
      Serial.println(mqtt_recv);
      DSerial.println("\r\n after sending");

      DSerial.println("\r\nThe MQTT Recv Data");
      DSerial.println(sta_buf + 3);
      break;
    case MQTT_STATUS_EVENT:
      sta_buf = strchr(mqtt_recv, ',');
      if (atoi(sta_buf + 1) == 1) {
        if (_5GNBIoT.CloseMQTTClient(comm_mqtt_index)) {
          DSerial.println("\r\nClose the MQTT Client Success!");
        }
      } else {
        DSerial.print("\r\nStatus cade is :");
        DSerial.println(atoi(sta_buf + 1));
        DSerial.println("Please check the documentation for error details.");
      }
      break;
  }


  // this is used to check and see if it is able to 
  // publish messages for the topic statistics for motor
  // topic: statistics_for_motor
  // message: depends...

  // if 
  // (
  //       _5GNBIoT.MQTTPublishMessages
  //       (
  //         comm_mqtt_index, 
  //         1, 
  //         mqtt_qos,
  //         "topic/statistics_for_motor",
  //         false, 
  //         "testing testing..."
  //       ) == 0
  // ) 
  // {
  //   DSerial.println("\r\nMQTT Publish Messages Success!");
  //   delay(1000);
  // }


  // the topic is motor_control
  /*
  while (_5GNBIoT.MQTTPublishMessages(comm_mqtt_index, 1, mqtt_qos, "statistics_for_motor", false, "testing testing...") != 0) 
  {
    DSerial.println("\r\nMQTT publish Topic Fail!");
    int e_code;
    if (_5GNBIoT.returnErrorCode(e_code)) {
      DSerial.print("\r\nERROR CODE: ");
      DSerial.println(e_code);
      DSerial.println("Please check the documentation for error details.");
      while (1);
    }
  }

*/





}
