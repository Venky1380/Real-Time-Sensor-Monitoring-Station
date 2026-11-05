#include "header.h"
int flag;

void timer1_handler(void)__irq{
	T1IR=1;
	flag=1;
	VICVectAddr=0;
}

void vic_for_timer1(void){
	T1TCR=0x2;
	T1PR=15000000-1;
	T1TC=T1PC=0;
	
	T1MCR=(1<<1)|(1<<0);
	T1MR0=2;  //change here to change delay time
	
	VICIntSelect=0;
	VICVectAddr0=(unsigned int)timer1_handler;
	VICVectCntl0=(1<<5)|5;
	VICIntEnable=(1<<5);
	T1TCR=1;
}

