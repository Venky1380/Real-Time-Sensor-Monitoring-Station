#include "header.h"

#define done ((ADDR>>31)&1)

void adc_init(void){
PINSEL1|=0X15400000;
ADCR=0X00200400; //set PDN and Pclk pins
}

unsigned int adc_read(unsigned int ch_num){
unsigned int result;

ADCR|=(1<<ch_num);	//Select channels
ADCR|=(1<<24); //start adc
while(done == 0);
ADCR^=(1<<24);//stop adc	
ADCR^=(1<<ch_num); //Diselect channels
result=(ADDR>>6)&0X3FF;	//extract data from ADDR register

return result;

}
