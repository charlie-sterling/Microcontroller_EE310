//Main Function

#include <xc.h>
#include "C:\Program Files\Microchip\xc8\v2.46\pic\include\proc\pic18f47k42.h"
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000                 // Fosc  frequency for _delay()  library
#define FCY    _XTAL_FREQ/4

int SECRET_CODE = 0x33; //code can only be between 0x11-0x44 (First/Second bit can only be 1,2,3,4)
void seg_display();

void main(void)
{
    inter_init(); //initailize external interrupt
    PORTD = 0; TRISD = 0; ANSELD = 0; LATD =0;//enable ports that are going to be used
    PORTB = 0; TRISB = 0x31; ANSELB = 0; LATB = 0;
    PORTBbits.RB6 = 1;//turn on SYS_LED
    while(1) //loop to wait for inputs
    {
        int num1 = 0; //first input
        int num2 = 0; //second input
        int test = 0; //combined inputs
        if (PORTBbits.RB4 == 0 || PORTBbits.RB5 == 0 )//wait for input from Photoresistors
        {
            num1 = input();//call input() function for first intput
            PORTD = 0x0; // clears 7-seg
            __delay_ms(100);//delay
            num2 = input();//call input() function for second input
            PORTD = 0x0; // clears 7-seg
            test = (num1*16) + num2; //num1 (1-4) times 16 for high bit, plus low bit
            if (test == SECRET_CODE)//if statement if inputs is secret code then turn on motor(seperate function)
            {
                motor(); // turn on motor
                PORTD = 0x00; //clear 7-segment
            }
            else
            {
                PORTD = 0xFF;
                PORTBbits.RB7 = 1;
                __delay_ms(1000);
                PORTBbits.RB7 = 0;
                __delay_ms(1000);
                PORTBbits.RB7 = 1;
                __delay_ms(1000);
                PORTBbits.RB7 = 0;
                PORTD = 0x00; //Process over
            }
        }
    }
}
