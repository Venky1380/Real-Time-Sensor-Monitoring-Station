#include "header.h"


int task[5]={0},c=0;

void timer1_handler(void)__irq{
	T1IR=1;
	c++;
	
	if(c==10){
		task[0]=1;
	}
	else if(c==13){
		task[1]=1;
	}
	else if(c==16){
		task[2]=1;
	}
	else if(c==18){
		task[3]=1;
	}
	else if(c==20){
		task[4]=1;
		c=0;
	}		
	
	VICVectAddr=0;
}

void vic_for_timer1(void){
	T1TCR=0x2;
	T1PR=15000-1;
	T1TC=T1PC=0;
	
	T1MCR=(1<<1)|(1<<0);
	T1MR0=100;  //change here to change delay time
	
	VICIntSelect=0;
	VICVectAddr0=(unsigned int)timer1_handler;
	VICVectCntl0=(1<<5)|5;
	VICIntEnable=(1<<5);
	T1TCR=1;
}

