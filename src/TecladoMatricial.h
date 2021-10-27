
#include "F:\Users\Matias Garcia\Documents\MCUXpressoIDE_11.4.0_6237\workspace\CMSISv2p00_LPC17xx\inc\LPC17xx.h"
#include "F:\Users\Matias Garcia\Documents\MCUXpressoIDE_11.4.0_6237\workspace\CMSISv2p00_LPC17xx\Drivers\inc\lpc17xx_gpio.h"
#include "F:\Users\Matias Garcia\Documents\MCUXpressoIDE_11.4.0_6237\workspace\CMSISv2p00_LPC17xx\Drivers\inc\lpc17xx_timer.h"
#include "F:\Users\Matias Garcia\Documents\MCUXpressoIDE_11.4.0_6237\workspace\CMSISv2p00_LPC17xx\Drivers\inc\lpc17xx_pinsel.h"


#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"


void config_GPIO(void);
void retardo();
void readkey();

char keypress;
char keypad[5][4]={
        {'q','w','#','*'},
        {'1','2','3','m'},
        {'4','5','6','n'},
        {'7','8','9','b'},
        {'z','0','c','v'}
        };


void config_GPIO(){

    //Entradas (columnas)

	PINSEL_CFG_Type pin_configuration;
    uint8_t i;
	for(i=0;i<4;i++){
	    pin_configuration.Portnum 	=	2;
	    pin_configuration.Pinnum	=	i;
	    pin_configuration.Pinmode	=	PINSEL_PINMODE_PULLUP;//Con PullUp
	    pin_configuration.Funcnum	= 	PINSEL_FUNC_0;//Funcion de GPIO
	    pin_configuration.OpenDrain	=	0;
	    PINSEL_ConfigPin(&pin_configuration); //Cargamos la configuracion
	    GPIO_SetDir( 2 , (1<<i) , 0);
	}

	//Salidas (filas)

	for(i=4;i<9;i++){
	    pin_configuration.Portnum 	=	2;
	    pin_configuration.Pinnum	=	i;
	    pin_configuration.Pinmode	=	PINSEL_PINMODE_PULLUP;
	    pin_configuration.Funcnum	= 	PINSEL_FUNC_0;
	    pin_configuration.OpenDrain	=	0;
	    PINSEL_ConfigPin(&pin_configuration);
	    GPIO_SetDir( 2 , (1<<i) , 1);
	}


}

void readkey(){

    uint8_t i;
    uint8_t j;
    LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
    for(i=4;i<9;i++){
        LPC_GPIO2->FIOCLR |= (1<<i);//11101||1111)
        for(j=0;j<4;j++){
            if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                keypress=keypad[8-i][j];
            }
        }
        LPC_GPIO2->FIOSET |= (1<<i);
        retardo();
    }

}

void retardo(void){
    uint32_t contador;
    for(contador =0 ; contador<100000; contador++){};
}
