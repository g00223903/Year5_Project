
//
//  wifiTest2.cpp
//  ecgSignalCcode
//
//  Created by patrick shaughnessy.
//  Copyright © 2017 patrick shaughnessy. All rights reserved.
//

#include <stdio.h>
#include "mbed.h"
#include "rtos.h"
#include "config.h"
#include "security.h"
#include "easy-connect.h"
#include "simple-mbed-client.h"

SimpleMbedClient client;


InterruptIn pir(SW2);

// We need a way to signal from an interrupt context -> main thread, use a Semaphore for it...
Semaphore updates(0);

SimpleResourceString name = client.define_resource("device/0/name", "jan", M2MBase::GET_PUT_ALLOWED, true);
SimpleResourceInt heartRate = client.define_resource("my/0/patientHeartRate", 0, M2MBase::GET_ALLOWED);
//SimpleResourceInt myCount = client.define_resource("my/0/count", 0, M2MBase::GET_ALLOWED);


// Registered callback for mbed Client
DigitalOut statusLed(LED1, 1);
void registered() {
    statusLed = 0;
}



AnalogIn   ain(A0);
static DigitalOut led(LED1);;
Timer timer;
int start=0, end, heartBeats = 0;
int oldStartTime = 0, newStartTime = 0;
float rate = 0.0;
float peakMax = 0;
volatile float temp = 0;
float interval = 0;
void  getHeartRate();
int fPeakFlag = 0;
int ary[100];
int z = 0;

float oldValue = 0, newValue = 0;
void getHeartRate();
void getHeartRate()
{
    printf("\033[H\033[J");//clears screen
    printf("Get Heart Rate Function!!!\r\n");
    led = 0;
    timer.start();
    while(1)
    {
        oldValue = newValue;
        newValue = ain.read();
        if((newValue - oldValue > 0) && (newValue > 0.5f) && (fPeakFlag == 0))
        {
            oldStartTime = newStartTime;
            newStartTime = timer.read_ms();
            fPeakFlag = 1;
            rate = ((60 / (float)(newStartTime - oldStartTime))*1000);
            printf("Time: %d HeartRate %f \r\n",newStartTime-oldStartTime, rate);
            heartRate = rate;
        }
        if(newValue < 0.5f)
        {
            fPeakFlag = 0;
        }
    }
}

void connect();
void connect()
{
    NetworkInterface* network = easy_connect(true);
    if (!network) {
        printf("Connect to internet failed... See serial output.\n");
    }
    struct MbedClientOptions options = client.get_default_options();
    options.DeviceType = "wifi test";
    if (!client.setup(options, network)) {
        printf("Setting up mbed_client failed...\n");
    }
    client.on_registered(&registered);
    
}

int main(int, char**) {
    char *ptr = "Patrick Shaughnessy";
    name = ptr;
    //heartRate = 0;
    connect();
    getHeartRate();
}


/*    NetworkInterface* network = easy_connect(true);
 if (!network) {
 printf("Connect to internet failed... See serial output.\n");
 return 1;
 }
 struct MbedClientOptions options = client.get_default_options();
 options.DeviceType = "wifi test";
 if (!client.setup(options, network)) {
 printf("Setting up mbed_client failed...\n");
 return 1;
 }
 client.on_registered(&registered);
 */