# simple implementation of the device just for early prototyping purposes
# I plan to develop a full library for closed loop control of the wheels.  



#include "mbed.h"

InterruptIn button(USER_BUTTON);

PwmOut mypwm(LED1);

DigitalOut IN1(D9);
DigitalOut IN2(D10);
DigitalOut IN3(D11);
DigitalOut IN4(D12);

PwmOut ENR(D13);
PwmOut ENL(D8);


Serial pc(USBTX,USBRX);



int y = 0;
float pwrAv;




void Init (){
    mypwm.period_ms(10);
    ENL.period_ms(10);
    ENR.period_ms(10);
    printf("PWM period set\n");
    }

void Speed(int n)
{
    ENL.pulsewidth_ms(n);
    ENR.pulsewidth_ms(n);
    mypwm.pulsewidth_ms(n);
    printf("speed : %d\n",n);
}

void motdrive(float pwrL, float pwrR){
    pwrAv = ((pwrL+pwrR)/2);
    ENL.pulsewidth_ms(pwrL);
    ENR.pulsewidth_ms(pwrR);
    mypwm.pulsewidth_ms(pwrAv);
    printf("speed : %f\n",pwrAv);
    }

void dir(int A, int B)
{
    if(A == 0) {
        IN1 = 1;
        IN2 = 0;
    }
    if(A==0) {
        IN1 = 0;
        IN2 = 1;
    }
    if(B==1) {
        IN3 = 1;
        IN4 = 0;
    }
    if(B==0) {
        IN3 = 0;
        IN4 = 1;
    }
}

void SetPower(float L,float R)
{
    if (L<-1){
        L=-1;
        } 
    if (L>1){
        L=1;
        }
    if (R<-1){
        R=-1;
        } 
    if (R>1){
        R=1;
        }          //Debug input 
        
    if(L>0) {
        IN1 = 1;
        IN2 = 0;
    }
    if(L<0) {
        IN1 = 0;
        IN2 = 1;
    }
    if(R>1) {
        IN3 = 1;
        IN4 = 0;
    }
    if(R<0) {
        IN3 = 0;
        IN4 = 1;
    }              // set Dir ** in dire need of optimisation 
    L=L*10;
    R=R*10;
    motdrive(L,R);

    
}



int main() {
     
    Init();
    //dir(0,0);
    
    while(1) {
    SetPower(0.2,0.2);  
    //y++;
    //printf(" y = %d\n",y);
    wait(0.1);  
      
    if(y>=9){
        y=0;           
     }     
    }
}
