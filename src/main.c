#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_ADC.h"
#include "lpc17xx_gpdma.h"
#include "configuraciones.h"
#include "TecladoMatricial.h"
#include "uart.h"
#include "timer.h"
#include "ADC.h"
//#include "dma.h"

char keypress;
uint8_t menu=0;

int main(void){

	config_GPIO();
	confUart();
    confADC();
    configINT();
    confTimers();
    //confDMA();

    while(1) {

    	if(menu==0){
    		VerificarAlarma();
    		MostrarHora();
    	}
    	else{
    		VerificarAlarma();
    		MostrarTemp();

    	}

    }
    return 0 ;
}

void EINT3_IRQHandler(void){
	Antirebote();
	char tecla;
	tecla = readkey();
	keypress =tecla;
	switch(tecla){
			case 'A':
	            SetHora();
	            break;
	        case 'B':
	            SetAlarma();
	            break;
	        case '<':
	            CambiarMenu();
	            break;
	        case '>':
	            CambiarMenu();
	            break;
	    }
	LPC_GPIO2->FIOCLR |= (0b11111<<4);
	LPC_GPIOINT->IO2IntClr |=(0b1111<<0);
}

void SetAlarma(void){

}
void SetHora(void){

}
void CambiarMenu(void){
	if(menu==0){
		menu=1;
	}
	else{
		menu=0;
	}
}
void VerificarAlarma(void){
	if(HoraReloj==HoraAlarma){
		if(MinutosReloj==MinutosAlarma){
			SonarAlarma();
		}
	}
}
void MostrarTemp(void){
	while((LPC_ADC->ADDR0)&(1<<31)){
		ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF;
		Temp= (ADC0Value/4096*80)-20;
		}
		 // Temperatura entre -20° y 60°
	consoleclear();
	setTemperatura(Temp);
	enviarRTemperatura();

}
void MostrarHora(void){
    consoleclear();
    setReloj(HoraReloj,MinutosReloj);
    enviarReloj(reloj);
}

void SonarAlarma(void){

}
