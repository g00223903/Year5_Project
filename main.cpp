#include "mbed.h"
#include "stdio.h"

DigitalOut gpo(D0);
DigitalOut led(LED_RED);

int main()
{
    while (true)
    {
    	int count;
        gpo = !gpo; // toggle pin
        led = !led; // toggle led
        wait(0.5f);
        //cout << "Count: %d \r" << count;
        printf("Count: %d\r\t",count);
        count++;
    }
}
