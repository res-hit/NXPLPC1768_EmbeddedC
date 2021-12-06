#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

#define true 1
#define false 0
	
#define min_curr 1
#define min_old 0
#define max	233

uint8_t curr_value=1;
uint8_t old_value=0;
uint8_t over = 0; //overflow

void EINT0_IRQHandler (void)	  
{
	//LED_On(0);
	old_value = min_old;
	curr_value = min_curr;
	LED_Out(curr_value);
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	if (curr_value < max && over== false){
	uint8_t tmp = curr_value;
  //LED_On(1);
	curr_value = curr_value + old_value;
	old_value = tmp;
	//if (curr_value > 0) not needed, we have defined unsigned int 
	
	
		LED_Out(curr_value); //E9 i.e. 1110 1001 i.e. 233
																		//putting this as final line,assures 233 to be included to led shown
	
	if(curr_value == max) over = true;
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	}
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	//LED_Off(0);
	//LED_Off(1);
	uint8_t tmp = curr_value;
	if (curr_value == min_curr && old_value == min_old){
		LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
		return;
	}
	old_value = curr_value - old_value;
	curr_value = tmp - old_value;
	
	LED_Out(curr_value);
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


