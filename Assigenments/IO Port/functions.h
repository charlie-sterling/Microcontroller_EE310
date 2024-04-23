?*
  Author: Charlie Sterling
  Purpose: Functions used in assignments
*?

//Interrupt Function
void __interrupt(irq(INT0),base(0x4008)) INT0_ISR(void)
{
    if (PIR1bits.INT0IF == 1)
    {
        PORTBbits.RB3 = 0;
        PORTBbits.RB7 = 1;//turn on buzzer
        __delay_ms(100);//delay
        PORTBbits.RB7 = 0;//turn off buzzer
        __delay_ms(100);//delay
        PORTBbits.RB7 = 1;//turn on buzzer
        __delay_ms(100);//delay
        PORTBbits.RB7 = 0;//turn off buzzer
        PIR1bits.INT0IF = 0; //clear the interrupt
    }
}

//Set up interrupt
void inter_init(void)
{
    INTCON0bits.IPEN = 1;
    INTCON0bits.GIEH = 1;
    INTCON0bits.GIEL = 1;
    INTCON0bits.INT0EDG = 1;
    IPR1bits.INT0IP = 1;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    IVTBASEU = 0x00;
    IVTBASEH = 0x40;
    IVTBASEL = 0x08;
}

//Input function

int input(void)
{
    int count = 0;
    int num = 0;
    while (1)
    {
        if (count == 5)
        {
            return (num);
        }
        else if(PORTBbits.RB4 == 1 && PORTBbits.RB5 == 1)
        {
            count = count +1;
            __delay_ms(100);
        }
        else if(num == 4)
        {
            __delay_ms(500);
            return (num);
        }
        else
        {
            num = num + 1;
            count = 0;
            seg_display(num); //function that display current number on seven segment
            __delay_ms(1000);
        }
    }
}

// Controls 7-Seg

void seg_display(int num)
{
    if (num == 1)
    {
        PORTD = 0x06; // 1
    }
    else if(num == 2)
    {
        PORTD = 0x5B; // 2
    }
    else if( num == 3)
    {
        PORTD = 0x4F; // 3
    }
    else if(num == 4)
    {
        PORTD = 0x66; // 4
    }
    return;
}

//Controls motor

void motor(void)
{
    PORTBbits.RB3 = 1;
    __delay_ms(500);
    PORTBbits.RB3 = 0;
}

