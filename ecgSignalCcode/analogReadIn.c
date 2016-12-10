//
//  analogReadIn.c
//  ecgSignalCcode
//
//  Created by patrick shaughnessy on 10/12/2016.
//  Copyright © 2016 patrick shaughnessy. All rights reserved.
//

/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"

// Initialize a pins to perform analog input and digital output fucntions
AnalogIn   ain(A0);
DigitalOut dout(LED1);

int main(void)
{
    printf("ANALOG READ IN\n\r");
    int count = 0;
    while (1) {
        // test the voltage on the initialized analog pin
        //  and if greater than 0.3 * VCC set the digital pin
        //  to a logic 1 otherwise a logic 0
        
        if(ain > 0.5f)
        {
            dout = 1;
            // count++;
        }
        else
        {
            dout = 0;
        }
        // printf("Count: %d   \r", count);
        
        
        // printf("Analog read in: %f       \r", ain.read());
        
        
        // print the percentage and 16 bit normalized values
        // printf("\n\rpercentage: %3.3f%%\n\r", ain.read()*100.0f);
        //        printf("normalized: 0x%04X\n\r\n\r", ain.read_u16());
        //wait_us(.2);
    }
}
