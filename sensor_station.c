#include <LPC21xx.H>
#include <stdio.h>
#include"header.h"

#define FLAME  ((IOPIN0>>14)&1)
#define PIR  ((IOPIN0>>15)&1)

extern int flag;

int main(){

unsigned int adc[3],ldr;
float vo[3],temp=0,pot=0;
char a[20];

	uart_init(9600);
	vic_for_timer1();
	adc_init();

	while(1){
		if(flag==1){
			uart_str("\r\n\r\n--:Sensor Station:--");

			//============ TEMP ==========
	 		adc[0]=adc_read(1);
		 	vo[0]=(adc[0]*3.3)/1023;
	 		temp=(vo[0]-0.05)/0.1;
			//============ POT ===========
			adc[1]=adc_read(2);
		 	pot=(adc[1]*3.3)/1023;
			
			//============ LDR ===========
			adc[2]=adc_read(3);
			ldr=(adc[2]*100)/1023;

			//============================
		 	sprintf(a,"\r\nTemperature: %.2f\r\nLIGHT:%d\r\nVTG: %.2f",temp,ldr,pot);
	 		uart_str(a);
			//============ FIR =================
			if(FLAME==0){							  				//Active LOw
			 	sprintf(a,"\r\nFlame= Detected");
				uart_str(a);
			}
			else{
				sprintf(a,"\r\nFlame= Not Detected");
			  	uart_str(a);
			}
			//============ PIR/Vibration =================   
			if(PIR==1){													//Active High
				sprintf(a,"\r\nVibration: Detected");
				uart_str(a);
			}
			else{
				sprintf(a,"\r\nVibretion: Not Detected");
				uart_str(a);
			}
			flag=0;
		}	
	}
}
