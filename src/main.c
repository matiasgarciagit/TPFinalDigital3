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
#include "dma.h"

char keypress;
uint8_t menu=0;
uint8_t hora;
uint8_t minutos;
int main(void){
	//Configuraciones de perifericos y pines
	config_GPIO();
	confUart();
    confADC();
    configINT();
    confTimers();
    confDMA();

    while(1) {
    	//Bucle infinito para menu de hora o menu de temperatura
		if(menu==0){
    		VerificarAlarma();
    		if(mostrar==1){
    			MostrarHora();
    		}
    	}
    	else{
    		VerificarAlarma();
    		if(mostrar==1){
    			MostrarTemp();
    		}

    	}

    }
    return 0 ;
}

void EINT3_IRQHandler(void){//Interrupciones por GPIO2 que corresponden al teclado
	mostrar=1;
	char tecla;
	tecla = readkey(); //Guardamos tecla presionada
	//Por interrupción solo funcionan las siguientes teclas
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
	        case 'F': //Apaga alarma con la tecla escape solo si está sonando
	        	if(!(led==0)){
				TIM_Cmd(LPC_TIM1, DISABLE);
				led=0;
				LPC_TIM1->EMR &= ~(1);
	        	}
				break;
	    }
	LPC_GPIO2->FIOCLR |= (0b11111<<4);
	LPC_GPIOINT->IO2IntClr |=(0b1111<<0);
}

void SetAlarma(void){//Menú de configuración de alarma
	suelta();
	uint8_t si=1;
	uint8_t aux=1;
	consoleclear();
	char mensaje11[]="- Para configurar Alarma presione Enter \n \r";
	UART_Send(LPC_UART0, mensaje11, sizeof(mensaje11), BLOCKING);
	char mensaje12[]="- Para Desactivar Alarma presione Escape \n";
	UART_Send(LPC_UART0, mensaje12, sizeof(mensaje12), BLOCKING);

	switch(presiona()){
	case 'F'://Sale del menú y desactiva la alarma.
		alarma=0;
		return;

	case 'E'://Configura la alarma
		suelta();
		while(aux){
			consoleclear();
			char mensaje1[]="Ingrese 2 digitos para Alarma entre 00-23";
			UART_Send(LPC_UART0, mensaje1, sizeof(mensaje1), BLOCKING);
			while(si){
					hora= (((int) presiona())-48)*10;
					suelta();
					hora += ((int) presiona()) -48;
					suelta();
					if(hora>23 || hora<0){ //Verificamos que la hora es válida
						consoleclear();
						char mensaje2[]="Hora incorrecta, ingrese nuevamente:";
						UART_Send(LPC_UART0, mensaje2, sizeof(mensaje2), BLOCKING);
					}
					else si=0;
				}

				si=1;
				consoleclear();
				char mensaje3[]="Ingrese 2 digitos para minutos entre 00-59";
				UART_Send(LPC_UART0, mensaje3, sizeof(mensaje3), BLOCKING);
				while(si){
					minutos= (((int) presiona())-48)*10;
					suelta();
					minutos += ((int) presiona()) -48;
					suelta();
					if(minutos>59 || minutos<0){//Verificamos que los minutos son válidos
						consoleclear();
						char mensaje4[]="Minutos incorrecto, ingrese nuevamente:";
						UART_Send(LPC_UART0, mensaje4, sizeof(mensaje4), BLOCKING);
					}
					else si=0;
				}
				consoleclear();
				char mensaje5[]="La Alarma ingresada es ";
				UART_Send(LPC_UART0, mensaje5, sizeof(mensaje5), BLOCKING);
				setRelojUART(hora,minutos);
				enviarReloj(reloj);
				char mensaje6[]=" . Si es correcta presione Enter";
				UART_Send(LPC_UART0, mensaje6, sizeof(mensaje6), BLOCKING);
				if(presiona() == 'E'){//Si presiona entener se configura la alarma y si no se vuelve a la configuración
					aux=0;
					HoraAlarma=hora;
					MinutosAlarma=minutos;
					alarma=1;

				}
				si=1;
				suelta();
			}
		}


}
void SetHora(void){//Menu de configuracion de hora
	TIM_Cmd(LPC_TIM0, DISABLE);
	suelta();

	uint8_t si=1;
	uint8_t aux=1;
	while(aux){
		consoleclear();
		char mensaje1[]="Ingrese 2 digitos para hora entre 00-23";
		UART_Send(LPC_UART0, mensaje1, sizeof(mensaje1), BLOCKING);
		while(si){
				hora= (((int) presiona())-48)*10;
				suelta();
				hora += ((int) presiona()) -48;
				suelta();
				if(hora>23 || hora<0){
					consoleclear();
					char mensaje2[]="Hora incorrecta, ingrese nuevamente:";
					UART_Send(LPC_UART0, mensaje2, sizeof(mensaje2), BLOCKING);
				}
				else si=0;
			}

			si=1;
			consoleclear();
			char mensaje3[]="Ingrese 2 digitos para minutos entre 00-59";
			UART_Send(LPC_UART0, mensaje3, sizeof(mensaje3), BLOCKING);
			while(si){
				minutos= (((int) presiona())-48)*10;
				suelta();
				minutos += ((int) presiona()) -48;
				suelta();
				if(minutos>59 || minutos<0){
					consoleclear();
					char mensaje4[]="Minutos incorrecto, ingrese nuevamente:";
					UART_Send(LPC_UART0, mensaje4, sizeof(mensaje4), BLOCKING);
				}
				else si=0;
			}
			consoleclear();
			char mensaje5[]="La hora ingresada es ";
			UART_Send(LPC_UART0, mensaje5, sizeof(mensaje5), BLOCKING);
			setRelojUART(hora,minutos);
			enviarReloj(reloj);
			char mensaje6[]=" . Si es correcta presione Enter";
			UART_Send(LPC_UART0, mensaje6, sizeof(mensaje6), BLOCKING);
			if(presiona() == 'E'){
				aux=0;
				HoraReloj=hora;
				MinutosReloj=minutos;
				TIM_Cmd(LPC_TIM0, ENABLE);

			}
			si=1;
			suelta();
	}


}
void CambiarMenu(void){//Cambia de menú al apretar algúna de las flechas "<" o ">"
	if(menu==0){
		menu=1;
	}
	else{
		menu=0;
	}
	//mostrar=1;
}
void VerificarAlarma(void){//Verifica si la alarma está activada, y si reloj y alarma coinciden
	if(alarma==1){
		if(HoraReloj==HoraAlarma){
			if(MinutosReloj==MinutosAlarma){
				SonarAlarma();
			}
		}
	}

}
void MostrarTemp(void){//Muestro la temperatura mediante UART
	transmitirDMA();//Convierte entrada ADC y activa el DMA para tranferir el dato del ADC a memoria
	Temp = (temperaturaDMA*80/4096)-20;//Adecuamos valor de la conversión para representarlo en grados
	consoleclear();
	setTemperaturaUART(Temp);
	enviarRTemperatura();
	mostrar=0;

}
void MostrarHora(void){//Muestro la hora mediante UART
    consoleclear();
    setRelojUART(HoraReloj,MinutosReloj);
    enviarReloj(reloj);
    mostrar=0;
}

void SonarAlarma(void){//Activamos Timer 1 para alarma
	TIM_Cmd(LPC_TIM1, ENABLE);
	led =1;
}
