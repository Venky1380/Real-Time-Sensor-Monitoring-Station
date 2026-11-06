#include <stdio.h>
#include <LPC21xx.H>

//========= Delay ==========
extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);
extern void vic_for_timer1(void);

//========== UART ==========
extern void uart_init(unsigned int br);
extern void uart_tx(unsigned char data);
extern char uart_rx(void);
extern void uart_str(char *p);
extern void uart_int(int num);
extern void uart_float(float num);

//========== ADC ===========
extern void adc_init(void);
extern unsigned int adc_read(unsigned int ch_num);
