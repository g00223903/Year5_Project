//error in mbed-client-wrapper.h


#include "mbed.h"
#include "rtos.h"
#include "config.h"
#include "security.h"
#include "easy-connect.h"
#include "simple-mbed-client.h"

SimpleMbedClient client;
DigitalOut red(LED_RED);
DigitalOut green(LED_GREEN);
DigitalOut blue(LED_BLUE);
// We need a way to signal from an interrupt context -> main thread, use a Semaphore for it...
Semaphore updates(0);

// Function declaration

void connect();
void getHeartRate();
void registered();


AnalogIn   ain(A0);
Timer timer;
int begin,end;

SimpleResourceString name = client.define_resource("device/0/name", "jan", M2MBase::GET_PUT_ALLOWED, true);
SimpleResourceInt heartRate = client.define_resource("heart/0/rate",0, M2MBase::GET_PUT_ALLOWED);

int main(int, char**) {
    
    connect();
    red=0;
    green=1;
    blue=1;
    name = "\n\rPatrick Shaughnessy\n\rYear 5 Project Demo\n\rECG Heart Monitoring System";
    
    
    int v = updates.wait(25000);
    
    
    int count = 0;
    printf("\n\rANALOG READ IN\r\n");
    while (1)
    {
        // test the voltage on the initialized analog pin
        //  and if greater than 0.5 * VCC set the digital pin
        //  to a logic 1 otherwise a logic 0
        
        red = 1;
        if(ain > 0.5f)
        {
            timer.start();
            begin = timer.read_us();
            red = 1; //led off
            count++;
            //wait_us(.2);
            wait(.2);
            
            //wait_ms(8);
        }
        else
        {
            red = 0;
            
        }
        //printf("Analog read in: %f      \tRercentage: %3.3f%%   \tNormalized: 0x%04X   \tCount: %d\r", ain.read(),
        //         ain.read()*100.0f , ain.read_u16(), count);
        //fprintf(fp,"Analog read in: %f       Count:  %d   \n\r", ain.read(), count);
        // print the percentage and 16 bit normalized values
        if (count == 2)
        {
            getHeartRate();
        }
        else{}
        client.keep_alive();
    }
    
}
//connects to mbed device connector
void connect()
{
    printf("In connect function!");
    NetworkInterface* network = easy_connect(true);
    if (!network) {
        printf("Connect to internet failed... See serial output.\n");
        //return 1;
    }
    
    struct MbedClientOptions options = client.get_default_options();
    options.DeviceType = "ECG cloud monitor";
    if (!client.setup(options, network)) {
        printf("Setting up mbed_client failed...\n");
        //return 1;
    }
    client.on_registered(&registered);
    
    
}

// Registered callback for mbed Client
DigitalOut statusLed(LED1, 1);
void registered() {
    statusLed = 0;
}
//Calculate heart rate
void getHeartRate()
{
    //Rate = 60/(R-R interval)
    end = timer.read();
    int rrInterval = ((end - begin) / 1000000);
    printf("Interval: %d ", rrInterval);
    printf( "Sec: %d  \r\n",rrInterval);
    int rate = 60 /rrInterval;
    heartRate = rate;
    printf("\rRate: %d  ",rate);
    //count = 0;
    //printf( "\n\ruS: %d  \r",end = begin);
    wait(2);
}