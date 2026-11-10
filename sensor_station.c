#include"header.h"

#define FLAME  ((IOPIN0>>14)&1)
#define PIR 	 ((IOPIN0>>15)&1)
#define LED  	 (1<<5)

extern int task[5];

int main(){

	unsigned int adc[3],ldr;
	float vo[3],temp=0,pot=0;
	char a[20];
	IODIR0=LED;

	uart_init(9600);
	vic_for_timer1();
	adc_init();

	while(1){
		//============ TEMP ==========
		if(task[0]==1){	
			task[0]=0;		
			uart_str("\r\n\r\n--:Sensor Station:--");			
			adc[0]=adc_read(1);
			temp=(adc[0]*3.3*100)/1023;
			sprintf(a,"\r\nTemperature: %.2f C",temp);
			uart_str(a);
			(temp>35)?(IOCLR0=LED):(IOSET0=LED);
		}
		//============ POT ===========
		else if(task[1]==1){
			task[1]=0;
			adc[1]=adc_read(2);
			pot=(adc[1]*3.3)/1023;
			sprintf(a,"\r\nVTG: %.2f",pot);
			uart_str(a);
		}
		//============ LDR ===========
		else if(task[2]==1){
			task[2]=0;
			adc[2]=adc_read(3);
			ldr=(adc[2]*100)/1023;
			sprintf(a,"\r\nLIGHT:%d",ldr);
			uart_str(a);
		}
		//============ FIR =================
		else if(task[3]==1){
		task[3]=0;
			if(FLAME==0){							  				//Active LOw
				sprintf(a,"\r\nFlame= Detected");
				uart_str(a);
			}
			else{
				sprintf(a,"\r\nFlame= Not Detected");
					uart_str(a);
			}
		}
		//============ PIR =================  
		else if(task[4]==1){	
		task[4]=0;			
			if(PIR==1){													//Active High
				sprintf(a,"\r\nVibration: Detected\r\n");
				uart_str(a);
			}
			else{
				sprintf(a,"\r\nVibretion: Not Detected\r\n");
				uart_str(a);
			}
		}
	}
}
