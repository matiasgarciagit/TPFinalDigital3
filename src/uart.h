

uint8_t clear[] = "\033[H\033[J";
uint8_t reloj[5];


void setReloj(uint8_t horas, uint8_t minutos){
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

void confUart(void){
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	//configuraci�n por defecto:
	UART_ConfigStructInit(&UARTConfigStruct);
	//inicializa perif�rico
	UART_Init(LPC_UART0, &UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	//Inicializa FIFO
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);
	//Habilita transmisi�n
	UART_TxCmd(LPC_UART0, ENABLE);
}

void consoleclear(){
	UART_Send(LPC_UART0, clear, sizeof(clear), BLOCKING);
}

void sendData(unsigned char *data){
	UART_Send(LPC_UART0, data, sizeof(reloj), BLOCKING);
}

