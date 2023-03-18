#include "JooI2C.h"

void I2C_init()
{
	TWBR = 32;
}

void I2C_start()
{
	TWCR = 1 << TWINT | 1 << TWSTA | 1 << TWEN | 1 << TWEA;
	while(!(TWCR & (1 << TWINT)));
}

void I2C_transmit(unsigned char data)
{
	TWDR = data;
	TWCR = 1 << TWINT | 1 << TWEN | 1 << TWEA;
	while(!(TWCR & (1 << TWINT)));
}

unsigned char I2C_receive(unsigned char ack)
{
	unsigned char a = ack & 0x01;
	TWCR = 1 << TWINT | 1 << TWEN | a << TWEA;
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}

void I2C_stop()
{
	TWCR = 1 << TWINT | 1 << TWSTO | 1 << TWEN | 1 << TWEA;
}