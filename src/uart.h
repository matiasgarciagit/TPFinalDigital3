uint8_t clear[] = "\033[H\033[J";
uint8_t data[] = "";

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

void sendData(){
	UART_Send(LPC_UART0, data, sizeof(data), BLOCKING);
}
