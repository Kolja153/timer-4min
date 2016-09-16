/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 16.09.2016
Author  : 
Company : 
Comments: 


Chip type               : ATtiny13
AVR Core Clock frequency: 4,800000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 16
*****************************************************/

#include <tiny13.h>

#include <delay.h>
int j=0, i=0;

void Bip()
  {            
    if (j>3) 
            { 
              j = 0; 
                delay_ms(500);    
             } 
           else
             {
               PORTB.4 = 1;
                delay_ms(100);     
                PORTB.4 = 0;
                delay_ms(50);  
                j++;
              }    
  }

// Timer 0 output compare A interrupt service routine
interrupt [TIM0_COMPA] void timer0_compa_isr(void)
{
    i++;

}

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State5=T State4=0 State3=T State2=T State1=T State0=P 
PORTB=0x01;
DDRB=0x10;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 4,688 kHz
// Mode: CTC top=OCR0A
// OC0A output: Disconnected
// OC0B output: Disconnected

TCNT0=0x00;
OCR0A=0xFF;
OCR0B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-5: Off
GIMSK=0x00;
MCUCR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x04;

// Analog Comparator initialization
// Analog Comparator: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR0=0x00;

// ADC initialization
// ADC Clock frequency: 600,000 kHz
// ADC Bandgap Voltage Reference: Off
// ADC Auto Trigger Source: ADC Stopped
// Digital input buffers on ADC0: Off, ADC1: Off, ADC2: Off, ADC3: On
DIDR0&=0x03;
DIDR0|=0x34;
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x83;

// Global enable interrupts
#asm("sei")

while (1)
      {
         if (PINB.0==1)
         {
            TCCR0A=0x02;
            TCCR0B=0x05;     
            if (i>read_adc(3)*10) 
            {
               Bip();
             }                  
             
          }   
        else
        {
           TCCR0A=0x00;
           TCCR0B=0x00;
           PORTB.4=0;   
           i=0;
        }
      }
}
