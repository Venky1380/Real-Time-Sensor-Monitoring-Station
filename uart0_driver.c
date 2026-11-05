#include "header.h"

void uart_init(unsigned int br){
	int pclk,result;
	
	if(VPBDIV==0)
		pclk=15000000;
	else if(VPBDIV==1)
		pclk=60000000;
	else if(VPBDIV==2)
		pclk=30000000;
	
	result=pclk/(br*16);
	
	PINSEL0|=0x5;
	U0LCR=0X83;
	U0DLL=result&0xff;
	U0DLM=result&0xff00;
	U0LCR=0X3;
}

#define THRE ((U0LSR>>5)&1)
void uart_tx(unsigned char data){
	U0THR=data;
	while(THRE == 0);
}

#define RDR (U0LSR&1)
char uart_rx(void){
	while(RDR == 0);
	return U0RBR;
}

void uart_str(char *p){
	while(*p){
		uart_tx(*p);
		p++;
	}
}

void uart_int(int num){
	if(num==0){
		uart_tx('0');
		return;
	}
	int i=0,temp=num;
	char a[10];
	
	if(num<0){
		uart_tx('-');
	}
	while(temp){
		a[i]=(temp%10)+'0';
		temp/=10;
		i++;
	}
	for(i--;i>=0;i--){
		uart_tx(a[i]);
	}	
}

void uart_float(float num){
	if(num==0){
		uart_tx('0');
		return;
	}
	unsigned int temp;
	temp=num;
	uart_int(temp);
	uart_tx('.');
	temp=(num-temp)*100;
	uart_int(temp);
}



