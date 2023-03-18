#ifndef JOOUART_H_
#define JOOUART_H_

enum UART_DATALENGTH{
	DL5 = 0,
	DL6 = 1,
	DL7 = 2,
	DL8 = 3,
	DL9 = 7
};

enum UART_PARITY{
	NONE = 0,
	EVEN = 2,
	ODD = 3
};
enum UART_STOPBIT{
	ONE = 0,
	TWO = 1
};

unsigned int get_UBRR(unsigned long baudrate, unsigned long fcpu, unsigned char S2X);
void init_uart(unsigned long baudrate, unsigned long fcpu, unsigned char S2X, unsigned char datalength, unsigned char parity, unsigned char stopbit);
unsigned char uart_receive(void);
void uart_transmit(unsigned char datum);

void uart_transmit_print_line(char* str);
void uart_transmit_print(char* str);
#endif /* JOOUART_H_ */