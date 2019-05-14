#include <mega8535.h>
#include <stdio.h>
#include <delay.h>
#define ADC_VREF_TYPE 0x00
// Declare your global variables here
int ts0 = 200;
int ts1 = 200;
int ts2 = 200;
int ts3 = 200;
int ts4 = 200;
int ts5 = 200;
int ts6 = 200;


unsigned int dataadc;
unsigned int dataadc1;
unsigned int dataadc2;
unsigned int dataadc3;
unsigned int dataadc4;
unsigned int dataadc5;
unsigned int dataadc6;
unsigned int dataadc7;


unsigned int sensor=0;
int kode;
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

void sensing()
{
      dataadc=read_adc(0);
      dataadc1 = read_adc(1);
      dataadc2 = read_adc(2);
      dataadc3 = read_adc(3);
      dataadc4 = read_adc(4);
      dataadc5 = read_adc(5);
      dataadc6 = read_adc(6);
      dataadc7 = read_adc(7);

      if(dataadc < ts0){sensor |= 0b0000001;  }
      else             {sensor &= 0b111110;  }

      if(dataadc1 < ts1){sensor |= 0b0000010; }
      else              {sensor &= 0b1111101; }

      if(dataadc2 < ts2){sensor |= 0b0000100; }
      else              {sensor &= 0b1111011; }

      if(dataadc3 < ts3){sensor |= 0b0001000; }
      else              {sensor &= 0b1110111; }

      if(dataadc4 < ts4){sensor |= 0b0010000; }
      else              {sensor &= 0b1101111; }

      if(dataadc5 < ts5){sensor |= 0b0100000; }
      else              {sensor &= 0b1011111; }

      if(dataadc6 < ts6){sensor |= 0b1000000; }
      else              {sensor &= 0b0111111; }
}

void pid() //pid tebal 2cm
{
    if(sensor == 0b1111110)kode = 6;
    else if(sensor ==  0b1111100)kode = 5;
    else if(sensor ==  0b1111101)kode = 4;
    else if(sensor ==  0b1111001)kode = 3;
    else if(sensor ==  0b1111011)kode = 2;
    else if(sensor ==  0b1110011)kode = 1;
    else if(sensor ==  0b1110111)kode = 0;
    else if(sensor ==  0b1100111)kode = -1;
    else if(sensor ==  0b1101111)kode = -2;
    else if(sensor ==  0b1001111)kode = -3;
    else if(sensor ==  0b1011111)kode = -4;
    else if(sensor ==  0b0011111)kode = -5;
    else if(sensor ==  0b0111111)kode = -6;

   /* if(sensor == 0b0000001)kode = 6;
    else if(sensor ==  0b0000011)kode = 5;
    else if(sensor ==  0b0000010)kode = 4;
    else if(sensor ==  0b0000110)kode = 3;
    else if(sensor ==  0b0000100)kode = 2;
    else if(sensor ==  0b0001100)kode = 1;
    else if(sensor ==  0b0001000)kode = 0;
    else if(sensor ==  0b0011000)kode = -1;
    else if(sensor ==  0b0010000)kode = -2;
    else if(sensor ==  0b0110000)kode = -3;
    else if(sensor ==  0b0100000)kode = -4;
    else if(sensor ==  0b1100000)kode = -5;
    else if(sensor ==  0b1000000)kode = -6;   */
       /*
    case 0b011111: kode = 5; break;
    case 0b001111: kode = 4; break;
    case 0b101111: kode = 3; break;
    case 0b100111: kode = 2; break;
    case 0b110111: kode = 1; break;
    case 0b110011: kode = 0; break;
    case 0b111011: kode = -1; break;
    case 0b111001: kode = -2; break;
    case 0b111101: kode = -3; break;
    case 0b111100: kode = -4; break;
    case 0b111110: kode = -5; break;
        */
}

void main(void)
{


PORTA=0x00;
DDRA=0x00;

PORTD=0x00;
DDRD=0x00;

TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

MCUCR=0x00;
MCUCSR=0x00;
TIMSK=0x00;

ACSR=0x80;
SFIOR=0x00;

ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x84;

UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

/*UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) |
(0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) |
(0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) |
(1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x67;*/

while (1)
      {
      // Place your code here

      sensing();
      pid();
      printf("nilai %d %d %d %d %d %d %d %d || Bit : %d || Kode :
%d\r\n",dataadc,dataadc1,dataadc2,dataadc3,dataadc4,dataadc5,dataadc6,dataadc7,sensor,kode);

      }
}
