#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

uint8_t curr_value=1;
uint8_t old_value=0;

void EINT0_IRQHandler (void)	  
{
	//LED_On(0);
	old_value = 0;
	curr_value = 1;
	LPC_GPIO2->FIOPIN = curr_value;
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	uint8_t tmp = curr_value;
  //LED_On(1);
	curr_value = curr_value + old_value;
	old_value = tmp;
	//if (curr_value > 0) not needed, we have defined unsigned int 
	LPC_GPIO2->FIOPIN = curr_value;
	
	if (curr_value < 233)		LPC_GPIO2->FIOPIN = curr_value; //E9 i.e. 1110 1001 i.e. 233
	//putting this as final line,assures 233 to be included to led shown
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	//LED_Off(0);
	//LED_Off(1);
	uint8_t tmp = curr_value;
	if (curr_value == 1 && old_value == 0){
		LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
		return;
	}
	old_value = curr_value - old_value;
	curr_value = tmp - old_value;
	
	LPC_GPIO2->FIOPIN = curr_value;
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


