

uint8_t clear[] = "\033[H\033[J";
uint8_t reloj[5];
int16_t temperatura[5];

void setRelojUART(uint8_t horas, uint8_t minutos){//Conversión de reloj en enteros a reloj en string para transmitir
	reloj[2]=':';
	char charValue;
	int aux;

    aux=horas%10;
    charValue=aux+'0';
    reloj[1]=charValue;
    horas /= 10;

    aux=horas%10;
    charValue=aux+'0';
    reloj[0]=charValue;

    aux=minutos%10;
    charValue=aux+'0';
    reloj[4]=charValue;
    minutos /= 10;

    aux=minutos%10;
    charValue=aux+'0';
    reloj[3]=charValue;

}

void setTemperaturaUART(int16_t valor){//Conversión de temperatura en enteros a string para transmitir
    char charValue;
    int aux;
    if(valor>=0){
            temperatura[0]=' ';
    }

    if(valor<0){
        temperatura[0]='-';
        valor=-valor;
    }

    aux=valor%10;
    charValue=aux+'0';
    temperatura[2]=charValue;
    valor /= 10;

    aux=valor%10;
    charValue=aux+'0';
    temperatura[1]=charValue;
    temperatura[3]=176;
    temperatura[4]='C';

}

void confUart(void){
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	//configuración por defecto:
	UART_ConfigStructInit(&UARTConfigStruct);
	//inicializa periférico
	UART_Init(LPC_UART0, &UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	//Inicializa FIFO
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);
	//Habilita transmisión
	UART_TxCmd(LPC_UART0, ENABLE);
}

void consoleclear(){
	UART_Send(LPC_UART0, clear, sizeof(clear), BLOCKING);
}

void enviarReloj(){
	UART_Send(LPC_UART0, reloj, sizeof(reloj), BLOCKING);
}

void enviarRTemperatura(){
	UART_Send(LPC_UART0, temperatura, sizeof(temperatura), BLOCKING);
}

