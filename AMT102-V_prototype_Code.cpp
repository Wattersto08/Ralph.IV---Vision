#include "mbed.h"

InterruptIn button(D2);
InterruptIn HE1(D3);
InterruptIn HE2(D4);
Serial pc(USBTX,USBRX,19200);
DigitalOut led(LED1);
int TICK1 =0;
int TICK2 =0;

int he1 =0;
int he2 =0;

int he1state = 0;
int he2state = 1;
int he1prev=0;

float singlerev = 360;
float resolution = 2048;

float Deginc = singlerev / resolution;
float Currentpos;

double delay = 0.5; // 500 ms

void ABS()
{
    printf("Abs Pos :\n");
}



void tick1H()
{
    he1=1;
    if(he2 != he1) {
        TICK1++;
    } else {
        TICK1--;
    }
    he1prev = he1;
    Currentpos = TICK1*Deginc;
}
void tick2H()
{
    //TICK2++;
    he2=1;

}
void tick1L()
{
    he1=0;

}
void tick2L()
{

    he2=0;
}


int main()
{
    Deginc= singlerev / resolution;
    // Assign functions to button
    button.fall(&ABS);

    HE1.rise(tick1H);
    HE2.rise(tick2H);
    HE1.fall(tick1L);
    HE2.fall(tick2L);

    while (1) {
        led = !led;
        wait(delay);

        printf("tick count : %d",TICK1);
        printf(" Abs angle : %f\n",Currentpos);
    }
}
