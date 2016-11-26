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

//variables
const double PI =  3.1415926535897;
double x[100];

double li = 0.4166;
int ct2;

int main(int argc, const char * argv[])
{
    printf("\n\r*********\n\r\n\rProgram to create ECG graph.\n\r\n\r*********\n\r");
    
    printf("Main function calls genX()\n\r");
    genX();  //generate x array
    printf("Calling function pWav\n\r");
    pWav();
    genX(); //generate x array
    printf("Calling function qWav\n\r");
    qWav();
}


void genX()
{
    int a;
    printf("genX() creates x array and prints\n\r");
    for( a = 0; a < 100; a++)
    {
        x[a] = 0.60008 + (a * 0.008);
        printf("Array x: %.4f\n\r", x[a]);
    }
   // printf("End of x array.\n\r");
   // printf("Calling function pWav\n\r");
    
}


void pWav()
{
    printf("pWav creates elements or p section of ECG\n\r");
    double b =  9.2593;
    double p2[100];
    double harm1[100];
    int i, ii,z;
    
    printf("\n\r*********\n\r\n\rPrinting P2 <<<<<<<<<<<<<<\n\r\n\r*********\n\r");
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
    printf("\n\r*********\n\r\n\rPrinting pwavArray: 0      <<<<<<<<<<<\n\r\n\r*********\n\r");
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




