//
//  analogReadIn.c
//  ecgSignalCcode
//
//  Created by patrick shaughnessy on 10/12/2016.
//  Copyright © 2016 patrick shaughnessy. All rights reserved.
//

#include "mbed.h"
#include "stdio.h"
#include "string.h"

// Initialize a pins to perform analog input and digital output fucntions
AnalogIn   ain(A0);
static DigitalOut led(LED1);;
Timer timer;
int begin, end, heartBeat = 0;
void  getHeartRate();
int main(void)
{
    float peakMax = 0;
    float temp = 0;
    
    
    led = 0;
    while(1)
    {
        printf("Analog read in: %f \tPeak Max: %f HeartBeat: %i\t\r",ain.read(), peakMax, heartBeat);
        
        temp = ain.read();
        if (temp > peakMax)
            peakMax = temp;
        if(ain.read() > 0.5f && ain.read() < 0.8f)
        {
            heartBeat++;//timestamp at each beat and sotre into and an array of size 10
            float start =  timer.start();
            if(heartBeat == 2)
            {
                float end = timer.stop();
                float interval = ((end - start) / 1000000);
            }
            led = !led;
            while(ain.read() > 0.5f)
            {}
        }
    }
}
