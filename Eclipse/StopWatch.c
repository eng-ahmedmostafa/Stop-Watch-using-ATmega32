
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char tick = 0  ;
unsigned char second = 0 ;
unsigned char Mint = 0 ;
unsigned char Hour = 0;

void Timer1_CTC(void)
{

	TCCR1A = (1 << FOC1A);

	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	TCNT1 = 0;
	OCR1A = 977;
	TIMSK |= (1 << OCIE1A);

}
void INT_0(void) {
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);

}


void INT_1(void) {
	MCUCR |= (1 << ISC10) | (1 << ISC11);
	GICR |= (1 << INT1);
	DDRD &= ~(1 << PD3);
}

void INTR_2(void){

	MCUCSR &= ~(1 << ISC2);
	GICR |= (1 << INT2);
}

int main ()
{
	DDRD &= ~(1 << 2);
	PORTD |= (1 << 2);
	INT_0();

	DDRD &= ~(1 << PD3);
	INT_1();

	DDRB &= ~(1 << 2);
	PORTB |= (1 << 2);
	INTR_2();
	Timer1_CTC();

	SREG |=(1<<7);
	DDRC = 0x0F;
	PORTC = 0x00;

	DDRA = 0x3F;
	PORTA  = 0x3F;

	while (1)
	{
		PORTA =0X20;
		PORTC =(PORTC & 0XF0) | ((second%10) & 0X0F);
		_delay_ms(5);

		PORTA =0X10;
		PORTC =(PORTC & 0XF0) | ((second/10) & 0X0F);
		_delay_ms(5);

		PORTA =0X08;
		PORTC =(PORTC & 0XF0) | ((Mint%10) & 0X0F);
		_delay_ms(5);

		PORTA =0X04;
		PORTC =(PORTC & 0XF0) | ((Mint/10) & 0X0F);
		_delay_ms(5);

		PORTA =0X02;
		PORTC =(PORTC & 0XF0) | ((Hour%10) & 0X0F);
		_delay_ms(5);

		PORTA =0X01;
		PORTC =(PORTC & 0XF0) | ((Hour/10) & 0X0F);
		_delay_ms(5);


	}
}

ISR(INT0_vect)        //RESET OF USED TIMER
{

	second = 0;
	Mint = 0;
	Hour = 0;

}


ISR(INT1_vect) {

	TCCR1B = 0;
}

ISR(INT2_vect) {

	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
}





ISR(TIMER1_COMPA_vect) {
	if (second == 60)
	{
		second = 0;
		if (Mint == 60)
			{
				Mint = 0;
				if (Hour == 99)
					{
						second = 0;
						Mint = 0;
						Hour = 0;
					}else
					{
						Hour++;

					}
			}else
			{
				Mint++;

			}
	}else
	{
		second++;

	}


}

