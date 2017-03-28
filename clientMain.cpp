#include "mbed.h"
#include <TCPSocket.h>
#include <EthInterface.h>
#include "EthernetInterface.h"
#include "string.h"
#include "ESP8266Interface.h"
ESP8266Interface wifi(D1, D0);
void ClearBuffer();
char rbuffer[300];
int rcount;
int main() {
    printf("Main\n\r"); 
    printf("Connecting...\n\r");
    int ret = wifi.connect("ssid","password", NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\n*** WiFi Connection error ***\r\n");
        return -1;
    }
    printf("IP Address is %s\r\n", wifi.get_ip_address());
    
    
    //create socket
    TCPSocket sock;
    sock.open(&wifi);
    int ret2 = sock.connect("ip address", portNo);
    if(ret2 != 0)
    {
       printf("*** Socket connection error ***\r\n");
       return -1;
    }
   
    sock.set_blocking(false);
    //sending to java server
    printf("Sending char[] to ip address...\r\n");
    char sbuffer[] = "Hello from client\r\n\r\n";
    int scount = sock.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\r\n", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);
    
    //recieve from java server
    while( 1) {//waits for something to be in the buffer  (timing issues)
        int32_t val =sock.recv(rbuffer, sizeof(rbuffer) -1);
        //printf("val = %d",val);
        if(val >0)
            break;
    }
    printf("recv %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    printf("Done\r\n"); 
    sock.close();
    wifi.disconnect();
}

void ClearBuffer(){
    for(int i = 0; i <= rcount; i++)
        rbuffer[i] = '\0';
}
