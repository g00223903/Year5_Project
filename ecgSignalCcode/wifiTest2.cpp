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
SimpleResourceInt myCount = client.define_resource("my/0/count", 0, M2MBase::GET_ALLOWED);

// Registered callback for mbed Client
DigitalOut statusLed(LED1, 1);
void registered() {
    statusLed = 0;
}



int main(int, char**) {
    //name = "Patrick Shaughnessy";
    //ask for ssid and password
    
    char *ptr = "Patrick Shaughnessy";
    name = ptr;
    
    
    int numArray[100];
    for(int x = 0; x < 100; x++)
    {
        numArray[x] = x;
    }
    
    myCount = numArray[51];
    
    NetworkInterface* network = easy_connect(true);
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
    int count;
    while (1) {
        int v = updates.wait(25000);
        if (v == 1) {
            count +=1;
            printf("\nCount: %i",count);
        }
        client.keep_alive();
    }
}