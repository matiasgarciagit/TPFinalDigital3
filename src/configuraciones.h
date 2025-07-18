//Declaramos variables globales
uint8_t HoraAlarma;
uint8_t HoraReloj;
uint8_t MinutosAlarma;
uint8_t MinutosReloj;
uint8_t alarma=0;
uint8_t led=0;
uint8_t mostrar=1;
int16_t Temp;
uint16_t temperaturaDMA;
uint8_t auxretardo=0;

//Prototipos
void SetAlarma(void);
void SetHora(void);
void CambiarMenu(void);
void VerificarAlarma(void);
void MostrarTemp(void);
void MostrarHora(void);
void SonarAlarma(void);

void config_GPIO(){//Configuraciones de pines
	//Teclado
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

	//UART
    pin_configuration.Portnum = 0;
    pin_configuration.Pinnum = 2;
    pin_configuration.Pinmode = 0;
    pin_configuration.Funcnum = 1;
    pin_configuration.OpenDrain = 0;
    PINSEL_ConfigPin(&pin_configuration);
    pin_configuration.Pinnum = 3;
    PINSEL_ConfigPin(&pin_configuration);

    //ADC
    pin_configuration.Portnum = 0;
    pin_configuration.Pinnum = 23;
    pin_configuration.Pinmode = PINSEL_PINMODE_TRISTATE;
    pin_configuration.Funcnum = 1;
    pin_configuration.OpenDrain = 0;
    PINSEL_ConfigPin(&pin_configuration);

    //TIMER
	pin_configuration.Portnum = 1;
	pin_configuration.Pinnum = 22;
	pin_configuration.Pinmode = PINSEL_PINMODE_TRISTATE;
	pin_configuration.Funcnum = 3;
	pin_configuration.OpenDrain = 0;
	PINSEL_ConfigPin(&pin_configuration);

}

void configINT(void){//Configuracion de interrupciones por GPIO para el teclado
	LPC_GPIOINT->IO2IntEnF |= (0b1111<<0);
	LPC_GPIOINT->IO2IntClr |= (0b1111<<0);
	LPC_GPIO2->FIOCLR |= (0b11111<<4);
	NVIC_EnableIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn, 2);
}

void retardoms(void){//Retardo por Timer 2
	auxretardo=1;
	TIM_Cmd(LPC_TIM2, ENABLE);
	while(auxretardo==1){}

}


