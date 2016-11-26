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

//variables
const double PI =  3.1415926535897;
double x[100];

double li = 0.4166;
int ct2;

int main(int argc, const char * argv[])
{
    printf("\n\r*********\n\r\n\rProgram to create ECG graph.\n\r\n\r*********\n\r");
    
    //    printf("Main function calls genX()\n\r");
    //    genX();  //generate x array
    //    printf("Calling function pWav\n\r");
    //    pWav();
    //    genX(); //generate x array
    //    printf("Calling function qWav\n\r");
    //    qWav();
    //    genX(); //generate x array
    //    printf("Calling function qrsWav\n\r");
    //    qrsWav();
    //    genX(); //generate x array
    //    printf("Calling function sWav\n\r");
    //    sWav();
    genX(); //generate x array
    printf("Calling function tWav\n\r");
    tWav();
    
}


void genX()
{
    int a;
    printf("genX() creates x array and prints\n\r");
    for( a = 0; a < 100; a++)
    {
        x[a] = 0.60008 + (a * 0.008);
        //   printf("Array x: %.4f\n\r", x[a]);
    }
}


void pWav()
{
    printf("pWav creates elements or p section of ECG\n\r");
    double b =  9.2593;
    double p2[100];
    double harm1[100];
    int i, ii,z;
    
    //printf("\n\r*********\n\r\n\rPrinting P2 <<<<<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        p2[ct2] = 0;//initializing p2 array to zero
        //printf("%.8f\n\r", p2[ct2]);
    }
    
    //    printf("\r\nValue at x[0]:%.4f\r\n",x[0]);
    //    printf("\n\rDisplaying array x after adding t_pwav(0.16) to each element in x array\r\n");
    for ( i = 0; i < 100; i++ )
    {
        x[ i ] += t_pwav; // set element at location i to i + t_pwav
        // printf("Array x: %.4f\r\n ", x[i]);
    }
    //working correctly as far as here
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm1[z]=(((sin((PI/(2*b))*(b-(2*ii))))/(b-(2*ii))+(sin((PI/(2*b))*(b+(2*ii))))/(b+(2*ii)))*(2/PI))*cos((ii*PI*x[z])/li);
            p2[z] += harm1[z];
        }
    }
    
    
    //printf("\n\r*********\n\r\n\rPrinting harm1 array\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        // printf("%.8f\n\r", harm1[ct2]);
    }
    
    // printf("\n\r*********\n\r\n\rPrinting P2 array\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        // printf("%.8f\n\r", p2[ct2]);
        
    }
    
    
    
    
    double pwav1[100];
    //printf("\n\r*********\n\r\n\rPrinting pwav1!!!!<<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pwav1[ct2] = 0;
        //printf("%.8f\n\r", pwav1[ct2]);
    }
    
    //printf("\n\r*********\n\r\n\rPrinting pwav1 + p1: 2.4000<<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pwav1[ct2] = p2[ct2] + 2.4000;
        // printf("%.8f\n\r", pwav1[ct2]);
    }
    
    
    
    
    
    //pwavArray=a*pwav1;
    double pwavArray[100];
    //printf("\n\r*********\n\r\n\rPrinting pwavArray: 0      <<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pwavArray[ct2] = 0;
        //printf("%.8f\n\r", pwavArray[ct2]);
        
    }
    
    double a = 0.25;
    for(ct2=0; ct2<100; ct2++)
    {
        pwavArray[ct2] = a  * pwav1[ct2];
    }
    
    
    printf("\n\r*********\n\r\n\rPrinting pwavArray       <<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        printf("%.8f\n\r", pwavArray[ct2]);
    }
    
    //pwavArray is correct
}

void qWav()
{
    double a =  a_qwav;
    double b=(2*li)/d_qwav;
    double q1=(a/(2*b))*(2-b);
    double q2[100];
    double qWavArray[100];
    int ii, z;
    double harm5[100];
    
    printf("\n\r<<<<<<<<<<<<         qWav         >>>>>>>>>>>>>>\r\n");
    printf("a: %.4f\r\n ", a);
    printf("b: %.4f\r\n ", b);
    printf("q1: %.4f\r\n ", q1);
    printf("\n\rDisplaying array x after adding t_qwav(0.166) to each element in x array\r\n");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] += t_qwav;
        //printf("X array qWav: %.8f\n\r", x[ct2]);
    }
    
    double pwavArray[100];
    //printf("\n\r*********\n\r\n\rPrinting pwavArray: 0      <<<<<<<<<<<\n\r\n\r*********\n\r");
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        pwavArray[ct2] = 0;
        // printf("%.8f\n\r", pwavArray[ct2]);
        
    }
    
    
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        q2[ct2] = 0;//setting q2 = 0
        //printf("%.8f\n\r", q2[ct2]);
    }
    
    
    
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        harm5[ct2] = 0;//setting harm5 = 0
        //printf("%.8f <<<<<<<harm5 set to 0\n\r", harm5[ct2]);
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        q2[ct2] = 0; //setting q2array to 0
        //printf("%.12f <<<<<<<q2 = 0\n\r", q2[ct2]);
    }
    
    
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            //harm5= (((2*b*a)/(i*i*pi*pi)) * (1-cos((i*pi) /b)))*cos((i* pi*x)   /l);
            harm5[z]=(((2*b*a)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            
            q2[z] += harm5[z];
        }
    }
    
    //    for( ct2 = 0; ct2 < 100; ct2++)
    //    {
    //        printf("%.12f <<<<<<<harm5 after loop\n\r", harm5[ct2]);
    //    }
    
    
    
    //    for( ct2 = 0; ct2 < 100; ct2++)
    //    {
    //
    //        printf("%.12f <<<<<<<q2 after q2=q2+harm5\n\r", q2[ct2]);
    //    }
    
    
    //    qwav=-1*(q1+q2);
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qWavArray[ct2] = 0;
        //printf("%.8f <<<<<<<qWavArray set to 0\n\r", qWavArray[ct2]);
    }
    
    //qwav=-1*(q1+q2);   q1: -0.0105
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qWavArray[ct2] = (-1*(q1 + q2[ct2]));
        printf("%.8f <<<<<<<qWavArray after qWavArray=-1*(q1+q2) \n\r", qWavArray[ct2]);
    }
    
    //qWavArray is correct
}


// qrswav=qrs_wav(x,a_qrswav,d_qrswav,li);

void qrsWav()
{
    
    double a = a_qrswav;
    //printf("%.8f <<<<<<<a: \n\r", a);
    
    double b =(2*li)/d_qrswav;
    //printf("%.8f <<<<<<<b: \n\r", b);
    
    double qrs1=(a/(2*b))*(2-b);// -0.5888000
    //printf("%.8f <<<<<<<qrs1=-1*(q1+q2) \n\r", qrs1);
    
    double qrs2[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qrs2[ct2] = 0;
        //printf("%.8f <<<<<<<qWavArray set to 0\n\r", qWavArray[ct2]);
    }
    
    double harm[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        harm[ct2] = 0;
        //printf("%.8f <<<<<<<harm set to 0\n\r", harm[ct2]);
    }
    
    int ii, z;
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            //harm    = (((2*b*a)/(i* i* pi*pi))*(1-cos((i *pi)/b)))*cos((i* pi * x) /l);
            harm[z] = (((2*b*a)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            qrs2[z] += harm[z];
            
            
        }
    }
    
    
    //qrswav=qrs1+qrs2;
    double  qrsWavArray[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qrsWavArray[ct2] = 0;
        //  printf("%.8f <<<<<<<qrsWavArray set to 0\n\r", qrsWavArray[ct2]);
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        qrsWavArray[ct2] = qrs1 + qrs2[ct2];
    }
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        printf("%.8f <<<<<<<qrsWavArray\n\r", qrsWavArray[ct2]);
    }
    
    //qrsWavArray correct
}

void sWav()
{
    //    x=x-t_swav;
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= t_swav;
    }
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        printf("%.5f <<<<<<<xArray -t_swav\n\r", x[ct2]);
    }
    
    double a = a_swav;
    double b=(2*li)/d_swav;
    
    double s1 = (a/(2*b))*(2-b);
    double s2[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        s2[ct2] = 0;
        //  printf("%.8f <<<<<<<s2 set to 0\n\r", s2[ct2]);
    }
    double harm3[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        harm3[ct2] = 0;
        //  printf("%.8f <<<<<<<harm3 set to 0\n\r", harm3[ct2]);
    }
    
    
    int ii, z;
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            //harm    = (((2*b*a)/(i* i* pi*pi))*(1-cos((i *pi)/b)))*cos((i* pi * x) /l);
            harm3[z] = (((2*b*a)/(ii*ii*PI*PI))*(1-cos((ii*PI)/b)))*cos((ii*PI*x[z])/li);
            s2[z] +=harm3[z];
        }
    }
    
    
    //    swav=-1*(s1+s2);
    double sWavArray[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        sWavArray[ct2] = 0;
        //  printf("%.8f <<<<<<<sWavArray set to 0\n\r", sWavArray[ct2]);
    }
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        sWavArray[ct2] = (-1*(s1 + s2[ct2]));
        printf("%.8f <<<<<<<qWavArray after sWavArray=-1*(q1+q2) \n\r", sWavArray[ct2]);
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        //sWavArray[ct2] = 0;
        printf("%.8f <<<<<<<sWavArray\n\r", sWavArray[ct2]);
    }
    //sWavArray correct
    
}

void tWav()
{
    
    double a = a_twav;
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        //printf("%.4f <<<<<<<x Array\n\r", x[ct2]);
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= t_twav;
        //printf("%.4f <<<<<<<xArray -t_twav tWav function\n\r", x[ct2]);
    }
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        x[ ct2 ] -= 0.045;
        printf("%.4f <<<<<<<xArray -t_twav tWav function<<<<<<<<<<<<<<<\n\r", x[ct2]);
    }
    
    
    
    
    double    b=(2*li)/d_twav;
    
    double  t1=1/li;
    double t2[100];
    double harm2[100];
    double tWav1[100];
    double tWavArray[100];
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        t2[ct2] = 0;
        harm2[ct2] = 0;
        tWav1[ct2] = 0;
        tWavArray[ct2] = 0;
        //  printf("%.8f <<<<<<<sWavArray set to 0\n\r", sWavArray[ct2]);
    }
    
    
    int ii, z;
    for(ii = 1; ii <= 100; ii++)
    {
        for(z = 0; z < 100; z++)
        {
            harm2[z] = (((sin((PI/(2*b))*(b-(2*ii))))/(b-(2*ii))+(sin((PI/(2*b))*(b+(2*ii))))/(b+(2*ii)))*(2/PI))*cos((ii*PI*x[z])/li);
            t2[z] +=harm2[z];
        }
    }
    
    //    twav1=t1+t2;
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        tWav1[ct2] = t1 + t2[ct2];
    }
    
    //    twav=a*twav1;
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        tWavArray[ct2] = a * tWav1[ct2];
    }
    
    for( ct2 = 0; ct2 < 100; ct2++)
    {
        printf("%.4f <<<<<<<tWavArray\n\r", tWavArray[ct2]);
    }
}




