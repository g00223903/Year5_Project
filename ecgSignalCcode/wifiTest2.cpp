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
float ecgArray[500];
AnalogIn   ain(A0);
volatile int x;
void flip() {
    led2 = !led2;
    ecgArray[x++] = ain.read();
    if(x == 500){
        flipper.detach();
        led2 = 1;
    }
}


ESP8266Interface wifi(D1, D0);
float ecg[] = {0.8999, 0.8999, 0.9, 0.8997, 0.9333, 0.9961, 1.0493, 1.0901, 1.1147, 1.1286, 1.1277,1.1079, 1.0714, 1.0184, 0.9533, 0.8986, 0.8991, 0.8992, 0.8991, 0.899, 0.8988, 0.8982,0.8957, 1.0727, 1.3045, 1.537, 1.7698, 2.0028, 2.2362, 2.4672, 2.2959, 2.0652, 1.8332,1.6009, 1.3685, 1.1364, 0.9142, 0.8553, 0.7946, 0.7338, 0.672, 0.6876, 0.7482, 0.8088,0.8696, 0.901, 0.9006, 0.9006, 0.9005, 0.9005, 0.9007, 0.9075, 0.9683, 1.0276, 1.083,1.1326, 1.1749, 1.2087, 1.2328, 1.2465, 1.2494, 1.2414, 1.2227, 1.1939, 1.156, 1.11, 1.0575,1.0002, 0.9397, 0.8989, 0.8996, 0.8998, 0.8999, 0.9, 0.9, 0.9, 0.9001, 0.9001, 0.9, 0.9,0.8997, 0.913,0.9275, 0.9346, 0.9323, 0.9211, 0.904, 0.9, 0.8999, 0.8998, 0.8998, 0.8998,0.8997, 0.8997, 0.8998, 0.8998, 0.8998, 0.8998, 0.8999, 0.8999};
char rbuffer[1000], requestStr[800];
char data[900];
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
int sendData(char str[80]);
int connectToWiFi();

//socket
TCPSocket sock;
//main
int main() {
    flipper.attach(&flip, .02);
    printf("\n\n*******************************\n\n\rMain\n\r");
    printf("\n\rECG size: %d\n\r", sizeof ecg);
    getUserDetails();
    getEcgData();
    connectToWiFi();
    sendData(details);
    
    for(;;)
    {
        wait(2);
        sendData(requestStr);
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


int connectToWiFi(){
    printf("\n\rConnecting...\n\r");
    int ret = wifi.connect("iPhone","Kingpin086++", NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\n*** WiFi Connection error ***\r\n");
        return -1;
    }
    printf("IP Address is %s\r\n", wifi.get_ip_address());
    return 0;
}

int sendData(char strData[]){
    memset(data,0,sizeof(data));
    strcpy(data,strData);
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
    printf("\r\nRecieved from server: %d [%.*s]\r\nClosing socket", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    //ClearBuffer();
    memset(rbuffer,0,sizeof(rbuffer));
    sock.close();
    return 0;
}

void getEcgData(){
    for(index = 0; index < 50; index++)
    {
        float tempFloat = ecgArray[index];
        char tempStr[7];
        snprintf(tempStr, 7, "%f", tempFloat);
        strcat(requestStr, tempStr);
        strcat(requestStr, ",");
    }
    strcat(requestStr, patientNoStr);
    strcat(requestStr,"ecgData\r\n");
    //printf("%s", requestStr);
    printf("\r\nRequestStr%d", sizeof(requestStr));
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