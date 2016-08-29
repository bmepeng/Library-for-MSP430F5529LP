
//	       P6.2   <--->  ADC

#include <stdint.h>

//You cannot use any other function if the ADC12 module is not initialized.
//Once it's initialized, you don't need initialize it again.
void ADC_Init()
{
	P6SEL |= BIT2;//P6.2 used as A1
	ADC12CTL0 = ADC12SHT10 + ADC12ON;//Sample Hold Time:64 ADC12CLK cycles; Open ADC12
	ADC12CTL1 = ADC12SHP;
	ADC12MCTL0 |= ADC12INCH1;
	ADC12CTL0 |= ADC12ENC;//Enable Convert
}


//Return the ADC result.
uint16_t ADC_Sample()
{
	ADC12CTL0 |= ADC12SC;
	while(ADC12CTL1 & ADC12BUSY);
	return ADC12MEM0;
}


//Convert the ADC result into voltage.
//Example:float temp = Caculate_Voltage(ADC_Sample());
//Most of the time, you don;t need it, but the convert result is right only when
//the reference voltage is 3.3V. Usually the reference is 3.3V, but you'd better
//test it with something, and this function provided a test method.
float Caculate_Voltage(uint16_t adc)
{
	return adc*3.3/4095;
}
