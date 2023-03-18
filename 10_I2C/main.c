#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "JooI2C/JooI2C.h"
#include "JooUART/JooUART.h"
#define BT 3
#define EN 2
#define RW 1
#define RS 0

#define ADDRESS 0x27

unsigned char bt = 1;

void setup_expander(unsigned char data)
{
	I2C_start();
	I2C_transmit(ADDRESS << 1);
	I2C_transmit(data | bt << BT);
	I2C_stop();
}

void generate_pulse(unsigned char data)
{
	setup_expander(data | (1 << EN));
	_delay_us(1);
	setup_expander(data & ~(1 << EN));
	_delay_us(60);
}

void send4bits(unsigned char data)
{
	setup_expander(data);
	generate_pulse(data);	
}

void sendbyte(unsigned char data)
{
	send4bits(data & 0xF0);
	send4bits((data << 4) & 0xF0);
}

void write(unsigned char data)
{
	send4bits((data & 0xF0) | (1 << RS));
	send4bits(((data << 4) & 0xF0) | (1 << RS));
}

int main(void)
{
	I2C_init();
	_delay_ms(50);
	
	setup_expander(0);
	
	_delay_ms(1000);
	send4bits(0b0011 << 4);
	_delay_ms(5);
	send4bits(0b0011 << 4);
	_delay_us(150);
	send4bits(0b0011 << 4);
	_delay_us(150);
	send4bits(0b0010 << 4);
	 
	sendbyte(0b00101000);
	
	sendbyte(0b00001110);
	
	sendbyte(0b00000110);
	
	sendbyte(0b00000010);
	_delay_ms(5);
	
	init_uart(9600, F_CPU, 0x01, DL8, NONE, ONE);
	unsigned char received = 0;
    while (1) 
    {
	    received = uart_receive();
		write(received);
	}
}

