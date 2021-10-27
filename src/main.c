
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "configuraciones.h"
#include "TecladoMatricial.h"


int main(void) {
	config_GPIO();
    while(1) {
    	readkey();
    }
    return 0 ;
}
