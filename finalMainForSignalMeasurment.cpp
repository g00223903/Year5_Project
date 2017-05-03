#include "mbed.h"
#include <TCPSocket.h>
#include <EthInterface.h>
#include <stdio.h>
#include <stdlib.h>
#include "EthernetInterface.h"
#include "string.h"
#include "ESP8266Interface.h"


Ticker flipper;
DigitalOut led2(LED2);
float ecgArray[100], copyArray[100];
AnalogIn   ain(A0);
volatile int x = 0;
int t;
volatile int flag = 0;
void flip() {
    led2 = !led2;
    ecgArray[x++] = ain.read();
    
    if(x == 100)
    {
        
        flag = 1;
        x = 0;
        for(t = 0; t < 100; t++)
        {
            copyArray[t] = ecgArray[t];
        }
    }
}


ESP8266Interface wifi(D1, D0);
char rbuffer[1000], requestStr[800];
char data[450];
int rcount, index, count = 0;
//********  user detals
char firstName[40];
char secondName[40];
char details[80];
char ageStr[15], patientNoStr[10];
int yourage, patientNo;

//prototypes
void getUserDetails();
void ClearBuffer();
void getEcgData();
int sendData();
int sendDetails();
int connectToWiFi();

//socket
TCPSocket sock;
//main
int main() {
    getUserDetails();
    sendDetails();
    printf("\n\n*******************************\n\n\rMain\n\r");
    printf("\n\rECG size: %d\n\r", sizeof ecg);
    connectToWiFi();
    flipper.attach(&flip, .05);//samlpes at .02 = 50/sec
    
    while(1)
    {
        if(flag  == 1)
        {
            printf("flag = 1");
            getEcgData();
            printf("\n\r between functions");
            sendData();
            printf("\n\r after send data");
            flag = 0;
        }
    }
    printf("\n\r***Closing WiFi***\n\r");
    int disconnect = wifi.disconnect();
    while (disconnect != 0){
        wifi.disconnect();
        break;
    }
    printf("Disconeccted!\r\n");
    printf("END");
    //return 0;
}

int sendData(){
    memset(data,0,sizeof(data));
    strcpy(data,requestStr);
    //printf("In sendData()\r\nSending: %s\n\rSize of strData : %d",data,sizeof(data));
    sock.open(&wifi);
    int ret2 = sock.connect("172.20.10.2", 8082);
    if(ret2 != 0)
    {
        while(1){
            ret2 = sock.connect("172.20.10.2", 8082);
            if(ret2 == 0){
                printf("\r\nSocket connected\r\n");
                break;
            }
            
        }
        //wifi.disconnect();
        printf("*** Socket connection error ***\r\n");
        return -1;
    }
    sock.set_blocking(false);
    //sending to java server
    printf("Sending details to database\r\n");
    int scount = sock.send(data, sizeof data);
    printf("sent %d [%.*s]\r\n", scount, strstr(data, "\r\n")-data, data);
    
    
    //recieve from java server
    while( 1) {//waits for something to be in the buffer  (timing issues)
        printf("\r\nWaitng for acknowlegment form server...\t\r");
        count++;
        if (count == 30){
            count = 0;
            break;
        }
        int32_t val = sock.recv(rbuffer, sizeof(rbuffer) -1);
        //printf("val = %d",val);
        if(val >0)
            break;
    }
    printf("\r\nRecieved from server: %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    //ClearBuffer();
    memset(rbuffer,0,sizeof(rbuffer));
    sock.close();
    return 0;
}


int sendDetails(){
    memset(data,0,sizeof(data));
    strcpy(data,details);
    //printf("In sendData()\r\nSending: %s\n\rSize of strData : %d",data,sizeof(data));
    sock.open(&wifi);
    int ret2 = sock.connect("172.20.10.2", 8082);
    if(ret2 != 0)
    {
        while(1){
            ret2 = sock.connect("172.20.10.2", 8082);
            if(ret2 == 0){
                printf("\r\nSocket connected\r\n");
                break;
            }
            
        }
        //wifi.disconnect();
        printf("*** Socket connection error ***\r\n");
        return -1;
    }
    sock.set_blocking(false);
    //sending to java server
    printf("Sending details to database\r\n");
    int scount = sock.send(data, sizeof data);
    printf("sent %d [%.*s]\r\n", scount, strstr(data, "\r\n")-data, data);
    
    
    //recieve from java server
    while( 1) {//waits for something to be in the buffer  (timing issues)
        printf("\r\nWaitng for acknowlegment form server...\t\r");
        count++;
        if (count == 30){
            count = 0;
            break;
        }
        int32_t val = sock.recv(rbuffer, sizeof(rbuffer) -1);
        //printf("val = %d",val);
        if(val >0)
            break;
    }
    printf("\r\nRecieved from server: %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    //ClearBuffer();
    memset(rbuffer,0,sizeof(rbuffer));
    sock.close();
    return 0;
}



int connectToWiFi(){
    printf("\n\rConnecting...\n\r");
    int ret = wifi.connect("iPhone","Kingpin086++", NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\n*** WiFi Connection error ***\r\n");
        return -1;
    }
    printf("IP Address is %s\r\n", wifi.get_ip_address());
    
    
    sock.open(&wifi);
    int ret2 = sock.connect("172.20.10.2", 8082);
    if(ret2 != 0)
    {
        while(1){
            ret2 = sock.connect("172.20.10.2", 8082);
            if(ret2 == 0){
                printf("\r\nSocket connected\r\n");
                break;
            }
            
        }
        //wifi.disconnect();
        printf("*** Socket connection error ***\r\n");
        return -1;
    }
    sock.set_blocking(false);
    
    return 0;
}


//pass a ptr
int sendData(char strData[]){
    
    strcpy(data,strData);
    // printf("In sendData()\r\nSending: %s\n\rSize of strData : %d",data,sizeof(data));
    //sock.open(&wifi);
    //    int ret2 = sock.connect("172.20.10.2", 8082);
    //    if(ret2 != 0)
    //    {
    //      while(1){
    //       ret2 = sock.connect("172.20.10.2", 8082);
    //       if(ret2 == 0){
    //        printf("\r\nSocket connected\r\n");
    //        break;
    //        }
    //
    //    }
    //       //wifi.disconnect();
    //       printf("*** Socket connection error ***\r\n");
    //       return -1;
    //    }
    //    sock.set_blocking(false);
    //sending to java server
    printf("Sending details to database\r\n");
    int scount = sock.send(data, sizeof data);
    printf("data sent: %d",sizeof data);
    //  printf("sent %d [%.*s]\r\n", scount, strstr(data, "\r\n")-data, data);
    
    
    //recieve from java server
    // while( 1) {//waits for something to be in the buffer  (timing issues)
    //        printf("\r\nWaitng for acknowlegment form server...\t\r");
    //        count++;
    //        if (count == 30){
    //            count = 0;
    //            break;
    //        }
    //        int32_t val = sock.recv(rbuffer, sizeof(rbuffer) -1);
    //        //printf("val = %d",val);
    //        if(val >0)
    //            break;
    //    }
    // printf("\r\nRecieved from server: %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    //ClearBuffer();
    // memset(rbuffer,0,sizeof(rbuffer));
    //sock.close();
    return 0;
}

void getEcgData(){
    //memset rqsstr
    memset(requestStr,0,sizeof(requestStr));
    for(index = 0; index < 10; index++)
    {
        float tempFloat = copyArray[index];
        char tempStr[7];
        snprintf(tempStr, 7, "%f", tempFloat);
        strcat(requestStr, tempStr);
        strcat(requestStr, ",");
    }
    strcat(requestStr, patientNoStr);
    strcat(requestStr,"ecgData\r\n");
    //printf("%s", requestStr);
    printf("\r\nRequestStr: %d", sizeof(requestStr));
    printf("\n\r end getEcg data\n\r");
}

void getUserDetails(){
    //fname
    printf("Enter user first name: ");
    scanf("%s", firstName);
    printf(":%s",firstName);
    strcat(firstName," ");
    //sname
    printf("\r\nEnter user second name: ");
    scanf("%s", secondName);
    printf(":%s",secondName);
    strcat(secondName," ");
    strcat(firstName, secondName);
    strcpy(details, firstName);
    //age
    printf("\r\nEnter you age:  ");
    scanf("%d",&yourage);
    sprintf(ageStr, "%d", yourage);
    printf(": %s", ageStr);
    strcat(ageStr," ");
    strcat(details, ageStr);
    //patient number
    printf("\r\nEnter patient number:  ");
    scanf("%d",&patientNo);
    sprintf(patientNoStr, "%d", patientNo);
    printf(": %s", patientNoStr);
    strcat(patientNoStr," ");
    strcat(details, patientNoStr);
    strcat(details, "details\r\n");
    printf("\r\nDetails: %s",details);
}

void ClearBuffer(){
    for(int i = 0; i <= rcount; i++)
    {
        rbuffer[i] = '\0';
        data[i] = '\0';
    }
}