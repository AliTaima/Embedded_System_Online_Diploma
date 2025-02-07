/*
 * dio.c
 *
 * Created: 9/12/2022 2:35:16 PM
 *  Author: Ali Mohamed Taima
 */ 
// include.h
// Global variables
// functions definitions
#include "dio.h"
void DIO_init(EN_port_t portNumber, EN_pin_t pinNumber, EN_direction_t direction)
{
	switch (portNumber)
	{
		case PORT_A:
			if(direction == IN)
			{
				DDRA &= ~(1<<pinNumber);	//input
			}
			else if(direction == OUT)
			{
				DDRA |= (1<<pinNumber);	//output
			}
			else
			{
				// error handling
			}
			break;
		case PORT_B:
			if(direction == IN)
			{
				DDRB &= ~(1<<pinNumber);	//input
			}
			else if(direction == OUT)
			{
				DDRB |= (1<<pinNumber);	//output
			}
			else
			{
				// error handling
			}
			break;
		case PORT_C:
			if(direction == IN)
			{
				DDRC &= ~(1<<pinNumber);	//input
			}
			else if(direction == OUT)
			{
				DDRC |= (1<<pinNumber);	//output
			}
			else
			{
				// error handling
			}
			break;
		case PORT_D:
			if(direction == IN)
			{
				DDRD &= ~(1<<pinNumber);	//input
			}
			else if(direction == OUT)
			{
				DDRD |= (1<<pinNumber);	//output
			}
			else
			{
				// error handling
			}
			break;
		default:
			break;
			//error handling
	}
	
}
void DIO_write(EN_port_t portNumber, EN_pin_t pinNumber, EN_value_t value)
{
	switch(portNumber)
	{
		case PORT_A:
			if(value == LOW)
			{
				PORTA &= ~(1<<pinNumber);	//write 0
			}
			else if(value == HIGH)
			{
				PORTA |= (1<<pinNumber);	//write 1
			}
			else
			{
				// error handling
			}
			break;
		case PORT_B:
			if(value == LOW)
			{
				PORTB &= ~(1<<pinNumber);	//write 0
			}
			else if(value == HIGH)
			{
				PORTB |= (1<<pinNumber);	//write 1
			}
			else
			{
				// error handling
			}
			break;
		case PORT_C:
			if(value == LOW)
			{
				PORTC &= ~(1<<pinNumber);	//write 0
			}
			else if(value == HIGH)
			{
				PORTC |= (1<<pinNumber);	//write 1
			}
			else
			{
				// error handling
			}
			break;
		case PORT_D:
			if(value == LOW)
			{
				PORTD &= ~(1<<pinNumber);	//write 0
			}
			else if(value == HIGH)
			{
				PORTD |= (1<<pinNumber);	//write 1
			}
			else
			{
				// error handling
			}
			break;
		default:
			break;
			//error handling
	}
	
}

void DIO_toggle(EN_port_t portNumber, EN_pin_t pinNumber)
{
	switch(portNumber)
	{
		case PORT_A:
			PORTA ^= (1<<pinNumber);
			break;
		case PORT_B:
			PORTB ^= (1<<pinNumber);
			break;
		case PORT_C:
			PORTC ^= (1<<pinNumber);
			break;
		case PORT_D:
			PORTD ^= (1<<pinNumber);
			break;
		default:
		//Error handling
		break;
	}
	
}

void DIO_read(EN_port_t portNumber, EN_pin_t pinNumber, uint8_t *value)
{
	switch(portNumber)
	{
		case PORT_A:
			*value = (PINA & (1<<pinNumber))>>pinNumber; //get state --> read bit
			break;
		case PORT_B:
			*value = (PINB & (1<<pinNumber))>>pinNumber; //get state --> read bit
			break;
		case PORT_C:
			*value = (PINC & (1<<pinNumber))>>pinNumber; //get state --> read bit
			break;
		case PORT_D:
			*value = (PIND & (1<<pinNumber))>>pinNumber; //get state --> read bit
			break;
		default:
			//Error handling
			break;
	}
	
}