#include "mbed.h"
#include "stdio.h"
#include <iostream>
#include "math.h"

using namespace std;
const double PI =  3.1415926535897;
float x[100];
float li = 0.4166;

//P wave and PR interval default settings
float a_pwav=0.25; //P wave amplitude
float d_pwav=0.09; //P wave duration
float t_pwav=0.16; //PR interval. This combined with P wave duration defines PR segment

//Q wave default settings
float a_qwav=0.025; //Q wave amplitude
float d_qwav=0.066; //Q wave duration
float t_qwav=0.166; //not adjustable in program

//R wave default settings
float a_qrswav=1.6; //R wave amplitude
float d_qrswav=0.11; //R wave duration

//S wave default settings
float a_swav=0.25; //S wave amplitude
float d_swav=0.066; //S wave duration
float t_swav=0.09; //not adjustable in program

//T wave default settings
float a_twav=0.35; //T wave amplitude
float d_twav=0.142; //T wave duration
float t_twav=0.2; //ST Interval

//U wave default settings
float a_uwav=0.035; //U wave amplitude
float d_uwav=0.0476; //U wave duration
float t_uwav=0.433; //not adjustable in program


int main()
{
	while (true)
	{
		genX();
	}
}



void genX( float * x)
{
	int a;
	for(a = 0; *x < 100; x++)
	{
		x[a] = 0.60008 + (a * 0.008);
	}
	genX(x);
}


void pWav (float * x, float a_pwav, float t_pwav, float li)
{
	float a = a_pwav;
	float x1  = *x + t_pwav;
	float b = (2*li)/d_pwav;
	float harm1, pwav1, pwav;

	float p1 = 1/li, p2 = 0;
	int z;
	for( z = 0; z < 100; z++)
	{
		harm1=(((sin((PI/(2*b))*(b-(2*z))))/(b-(2*z))+(sin((PI/(2*b))*(b+(2*z))))/(b+(2*z)))*(2/PI))*cos((z*PI*x1)/li);
		p2=p2+harm1;
	}
	pwav1=p1+p2;
	pwav=(a*pwav1);
}


/*
function [pwav]=p_wav(x,a_pwav,d_pwav,t_pwav,li)
l=li;
a=a_pwav;
x=x+t_pwav;
b=(2*l)/d_pwav;
n=100;
p1=1/l;
p2=0;
for i = 1:n
    harm1=(((sin((PI/(2*b))*(b-(2*i))))/(b-(2*i))+(sin((PI/(2*b))*(b+(2*i))))/(b+(2*i)))*(2/PI))*cos((i*PI*x)/l);
    p2=p2+harm1;
end
pwav1=p1+p2;
pwav=a*pwav1;*/
