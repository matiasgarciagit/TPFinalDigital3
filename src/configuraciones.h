
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


