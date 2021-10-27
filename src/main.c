
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_ADC.h"
#include "configuraciones.h"
#include "TecladoMatricial.h"
#include "uart.h"
#include "timer.h"
#include "ADC.h"


int main(void) {
	config_GPIO();
	confTimers();
	confUart();
    confADC();

    while(1) {
        consoleclear();
    	readkey();
    	data[0]=keypress;
    	sendData();
    }
    return 0 ;
}
