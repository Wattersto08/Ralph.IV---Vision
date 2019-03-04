#include "mbed.h"
#include "TextLCD.h"


//------------------------------------------------------------------------------------


// build X-axis servo object 
PwmOut Xservo(D11);
PwmOut Yservo(D12);

// X asis positioning values
float Xpos;
int xpos;
float Ypos;
int ypos;

// serial configuarion 
char    data[16];
Serial pc(USBTX,USBRX,9600);

// DF robot shield config, set IO
TextLCD lcd(D8, D9, D4, D5, D6,D7);



//------------------------------------------------------------------------------------

// simple map function 
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//------------------------------------------------------------------------------------

int main() {

  // config servo period
  Xservo.period_ms(20);
    
    
    while(1) {
        
        if (pc.readable()) {
            
            // read the serial port, for input vals, taking in X,Y offsets for face and object tracking 
            // refer to the Python script for the string output, change the %14 below to configure length of the string 
            pc.scanf("%14s", data);

            // set up short term variables 
            char *token;
            int a,b,c;
            
            // read the initial string 
            token = strtok(data, ",;");

            // read the first int
            token = strtok(NULL, ",;");
            a = atoi(token);

            // read the second int
            token = strtok(NULL, ",;");
            b = atoi(token);

            // read the third int
            token = strtok(NULL, ",;");
            c = atoi(token);     
            
            // map and convert the x offset to servo position int
            Xpos = map(b,-400,400,1200,1800);
            xpos = floor(Xpos);
            
            
            // print results to the lcd 
            lcd.locate(0,0);
            lcd.printf("Xpos : %d   ",xpos);
            lcd.locate(0,1);
            lcd.printf("X offset : %d    ",b);
            
            // Set pulsewidth to the servos  
            Xservo.pulsewidth_us(xpos);                  
         } 
    }
}
