

#ifndef JOOI2C_H_
#define JOOI2C_H_

#include <avr/io.h>

void I2C_init();
void I2C_start();
void I2C_transmit(unsigned char data);
unsigned char I2C_receive(unsigned char ack);
void I2C_stop();

#endif /* JOOI2C_H_ */