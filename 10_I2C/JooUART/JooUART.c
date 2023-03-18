#include "avr/io.h"

unsigned int get_UBRR(unsigned long baudrate, unsigned long fcpu, unsigned char S2X){
	unsigned char factor = S2X > 0? 1:2;
	return fcpu/8/factor/baudrate-1;
}

void init_uart(unsigned long baudrate, unsigned long fcpu, unsigned char S2X, unsigned char datalength, unsigned char parity, unsigned char stopbit){
	
	UCSR0A |= ((0x01 & S2X) << U2X0); //Set 2X mode
	
	unsigned int ubbr = get_UBRR(baudrate, fcpu, S2X);
	UBRR0H = (unsigned char)(ubbr >> 8);			  //Set Baud rate
	UBRR0L = (unsigned char)ubbr;
	
	//parity, stop bit, data length
	UCSR0C |= parity << UPM00;
	UCSR0C |= stopbit << USBS0;
	
	UCSR0C |= (datalength & 0x03) << UCSZ00;
	UCSR0B |= ((datalength & 0x04) >> 2) << UCSZ02;
	
	UCSR0B |= (0x01 << RXEN0) | (0x01<<TXEN0); //Set RX/TX Enable
}

unsigned char uart_receive(void){
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void uart_transmit(unsigned char datum){
	while (!(UCSR0A&(1<<UDRE0)));
	UDR0 = datum;
}

void uart_transmit_print(char* str){
	for(int i = 0; str[i]; i++){
		uart_transmit(str[i]);
	}
}

void uart_transmit_print_line(char* str){
	uart_transmit_print(str);
	uart_transmit('\n');
}



