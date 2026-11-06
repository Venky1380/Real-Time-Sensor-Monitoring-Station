/* Real-Time Sensors Monitoring Station Using Periodic Task Scheduler*/

#include"header.h"

#define FLAME  ((IOPIN0>>14)&1)
#define PIR  ((IOPIN0>>15)&1)
#define LED (1<<5)

extern int flag;

int main(){
	unsigned int adc[3],ldr;
	float temp=0,pot=0;
	char a[40];
	
	IODIR0=LED;
	IOSET0=LED;
	
	uart_init(9600);
	vic_for_timer1();
	adc_init();

	while(1){
		if(flag==1){
			uart_str("\r\n\r\n--:Sensor Station:--");

			//============ TEMP ==========
	 		adc[0]=adc_read(1);
	 		temp=(adc[0]*3.3*100)/1023;		//5v power supply
			
			//============ POT ===========
			adc[1]=adc_read(2);
		 	pot=(adc[1]*3.3)/1023;
			
			//============ LDR ===========
			adc[2]=adc_read(3);
			ldr=(adc[2]*100)/1023;
			
			//============================
		 	sprintf(a,"\r\nTemperature: %.2f C\r\nVTG: %.2f\r\nLIGHT:%d",temp,pot,ldr);
	 		uart_str(a);
			uart_tx('%');
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
			//============= LED ALert ===================
			if((temp>=35)||(FLAME==0)||(PIR==1)){
				IOCLR0=LED;
			}
			else if((temp<35)&&(FLAME==1)&&(PIR==0)){
				IOSET0=LED;
			}
			flag=0;
		}	
	}
}
