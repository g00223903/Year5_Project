//
//  main.c
//  ecgSignalCcode
//
//  Created by patrick shaughnessy on 23/11/2016.
//  Copyright © 2016 patrick shaughnessy. All rights reserved.
//
//incldes
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "mbed.h"

//P wave and PR interval default settings
double a_pwav=0.25; //P wave amplitude
double d_pwav=0.09; //P wave duration
double t_pwav=0.16; //PR interval. This combined with P wave duration defines PR segment

//Q wave default settings
double a_qwav=0.025; //Q wave amplitude
double d_qwav=0.066; //Q wave duration
double t_qwav=0.166; //not adjustable in program

//R wave default settings
double a_qrswav=1.6; //R wave amplitude
double d_qrswav=0.11; //R wave duration

//S wave default settings
double a_swav=0.25; //S wave amplitude
double d_swav=0.066; //S wave duration
double t_swav=0.09; //not adjustable in program

//T wave default settings
double a_twav=0.35; //T wave amplitude
double d_twav=0.142; //T wave duration
double t_twav=0.2; //ST Interval

//U wave default settings
double a_uwav=0.035; //U wave amplitude
double d_uwav=0.0476; //U wave duration
double t_uwav=0.433; //not adjustable in program

//function declarations
void genX();
void pWav();
void qWav();
void qrsWav();
void sWav();
void tWav();
void uWav();
void initArrays();

//variables
const double PI =  3.1415926535897;
double x[100];
double li = 0.4166;
int ct2, i, ii, z, ct3;


double pWavArray[100];
double  qrsWavArray[100];
double tWavArray[100];
double sWavArray[100];
double uWavArray[100];
double ecgArray[100];
double qWavArray[100];
AnalogOut tri(DAC0_OUT);
Serial pc(USBTX, USBRX); // tx, rx
int main(int argc, const char * argv[])
{
    int heartRate = 0;
    printf("*************************************\n\r");
    printf("\tECG signal generator\n\r\tInitialising Arrays...\n\r");
    initArrays();
    genX();  //generate x array
    pWav();
    genX(); //generate x array
    qWav();
    genX(); //generate x array
    qrsWav();
    genX(); //generate x array
    sWav();
    genX(); //generate x array
    tWav();
    genX(); //generate x array
    uWav();
    int elementCount = 0;
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        elementCount++;
        ecgArray[ct2] += pWavArray[ct2] += qrsWavArray[ct2] += tWavArray[ct2] += sWavArray[ct2] += qWavArray[ct2] += uWavArray[ct2];
    }
    //printf("\tPress enter to begin: ");
    printf("\n\r*************************************");
    
    while(1)
    {
        printf("\r\nPress enter to begin: ");
        if (pc.getc())
        {
            printf("\n\rPlease enter heart rate: ");
            scanf("%i",&heartRate);
            printf("%i",heartRate);
            for(ct3 = 0; ct3 < 20; ct3 ++)
            {
                for( ct2 = 0; ct2 < 100; ct2++)
                {
                    tri = ecgArray[ct2]/3.3;
                    wait_ms(600/heartRate);
                    
                }
                //if (pc.getc()){break;}
            }
        }
    }
    
}
void initArrays()
{
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pWavArray[ct2] = 0;
        qrsWavArray[ct2] = 0;
        tWavArray[ct2] = 0;
        sWavArray[ct2] = 0;
        uWavArray[ct2] = 0;
        ecgArray[ct2] = 0;
        qWavArray[ct2] = 0;
    }
}

void genX()
{
    int a;
    for( a = 0; a < 100; a++)
    {
        x[a] = 0.60008 + (a * 0.008);
        
    }
}


void pWav()
{
    double b =  9.2593;
    double p2[100];
    double harm1[100];
    double pwav1[100];
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        p2[ct2] = 0;//initializing p2 array to zero
        pwav1[ct2] = 0;
    }
    
    for ( i = 0; i < 100; i++ )
    {
        x[ i ] += t_pwav; // set element at location i to i + t_pwav
        
    }
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm1[z]=(((sin((PI/(2*b))*(b-(2*ii))))/(b-(2*ii))+(sin((PI/(2*b))*(b+(2*ii))))/(b+(2*ii)))*(2/PI))*cos((ii*PI*x[z])/li);
            p2[z] += harm1[z];
        }
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pwav1[ct2] = p2[ct2] + 2.4000;
    }
    
    for(ct2=0; ct2<100; ct2++)
    {
        pWavArray[ct2] = a_swav  * pwav1[ct2];
    }
}

void qWav()
{
    double b=(2*li)/d_qwav;
    double q1=(a_qwav/(2*b))*(2-b);
    double q2[100];
    double harm5[100];
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        q2[ct2] = 0;//setting q2 = 0
        harm5[ct2] = 0;
        q2[ct2] = 0;
        //printf("%.8f\n\r", q2[ct2]);
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] += t_qwav;
        //printf("X array qWav: %.8f\n\r", x[ct2]);
    }
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            //harm5= (((2*b*a)/(i*i*pi*pi)) * (1-cos((i*pi) /b)))*cos((i* pi*x)   /l);
            harm5[z]=(((2*b*a_qwav)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            
            q2[z] += harm5[z];
        }
    }
    
    //qwav=-1*(q1+q2);   q1: -0.0105
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qWavArray[ct2] = (-1*(q1 + q2[ct2]));
        //printf("%.8f <<<<<<<qWavArray after qWavArray=-1*(q1+q2) \n\r", qWavArray[ct2]);
    }
    
    //qWavArray is correct
}

void qrsWav()
{
    double qrs2[100];
    double harm[100];
    double b =(2*li)/d_qrswav;
    double qrs1=(a_qrswav/(2*b))*(2-b);// -0.5888000
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qrs2[ct2] = 0;
        harm[ct2] = 0;
        //printf("%.8f <<<<<<<qWavArray set to 0\n\r", qWavArray[ct2]);
    }
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            //harm    = (((2*b*a)/(i* i* pi*pi))*(1-cos((i *pi)/b)))*cos((i* pi * x) /l);
            harm[z] = (((2*b*a_qrswav)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            qrs2[z] += harm[z];
        }
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qrsWavArray[ct2] = qrs1 + qrs2[ct2];
    }
}

void sWav()
{
    double b=(2*li)/d_swav;
    double s1 = (a_swav/(2*b))*(2-b);
    double s2[100];
    double harm3[100];
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        s2[ct2] = 0;
        harm3[ct2] = 0;
        sWavArray[ct2] = 0;
    }
    //    x=x-t_swav;
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= t_swav;
    }
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm3[z] = (((2*b*a_swav)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            s2[z] +=harm3[z];
        }
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        sWavArray[ct2] = (-1*(s1 + s2[ct2]));
        //  printf("%.8f <<<<<<<qWavArray after sWavArray=-1*(q1+q2) \n\r", sWavArray[ct2]);
    }
}

void tWav()
{
    
    double  b=(2*li)/d_twav;
    double  t1=1/li;
    double t2[100];
    double harm2[100];
    double tWav1[100];
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        t2[ct2] = 0;
        harm2[ct2] = 0;
        tWav1[ct2] = 0;
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= t_twav;
        //printf("%.4f <<<<<<<xArray -t_twav tWav function\n\r", x[ct2]);
    }
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= 0.045;
        // printf("%.4f <<<<<<<xArray -t_twav tWav function<<<<<<<<<<<<<<<\n\r", x[ct2]);
    }
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm2[z] = (((sin((PI/(2*b))*(b-(2*ii))))/(b-(2*ii))+(sin((PI/(2*b))*(b+(2*ii))))/(b+(2*ii)))*(2/PI))*cos((ii*PI*x[z])/li);
            t2[z] +=harm2[z];
        }
    }
    
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        tWav1[ct2] = t1 + t2[ct2];
    }
    
    //    twav=a*twav1;
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        tWavArray[ct2] = a_twav * tWav1[ct2];
    }
}

void uWav()
{
    double b=(2*li)/d_uwav;
    double u1=1/li;
    double  u2[100];
    double harm4[100];
    double uWav1[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        u2[ct2] = 0;
        harm4[ct2] = 0;
        uWav1[ct2] = 0;
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= t_uwav;
    }
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm4[z] = (((sin((PI/(2*b))*(b-(2*ii))))/(b-(2*ii))+(sin((PI/(2*b))*(b+(2*ii))))/(b+(2*ii)))*(2/PI))*cos((ii*PI*x[z])/li);
            u2[z] +=harm4[z];
        }
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        uWav1[ct2] = u1 + u2[ct2];
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        uWavArray[ct2] = a_uwav * uWav1[ct2];
    }
}
