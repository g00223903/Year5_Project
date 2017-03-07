//
//  analogReadFinal.cpp
//  ecgSignalCcode
//
//  Created by patrick shaughnessy on 07/03/2017.
//  Copyright © 2017 patrick shaughnessy. All rights reserved.
//

//  analogReadIn.c
//  ecgSignalCcode
//
//  Created by patrick shaughnessy on 10/12/2016.
//  Copyright © 2016 patrick shaughnessy. All rights reserved.
#include "mbed.h"
#include "stdio.h"
#include "string.h"
void getRate();
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

int main(void)
{
    printf("Main\r\n");
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
        }
        if(newValue < 0.5f)
        {
            fPeakFlag = 0;
        }
    }
}


