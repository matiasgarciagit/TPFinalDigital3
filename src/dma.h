void transmitirDMA();
void DMA_IRQHandler (void);

/* Flag que avisa cuando se termina la transferencia en el canal 0 */
__IO uint32_t Channel0_TC;

/* Flag que avisa cuando se produce un error  en la transferencia en el canal 0  */
__IO uint32_t Channel0_Err;

#define DMA_SIZE		1

uint32_t adc_value;
GPDMA_Channel_CFG_Type GPDMACfg;


void DMA_IRQHandler (void)
{
	// chequeamos que la interrupción fue por el canal 0
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 0)){
		// Si la interrupcion fue porque se terminó de enviar el dato
		if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)){
			// Clear terminate counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 0);
				Channel0_TC++;
		}
		// Si la interrupcion fue porque se generó un error al enviar el dato
		if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 0)){
			// Clear error counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, 0);
			Channel0_Err++;
		}
	}
}


//Estructura de configuracion del DMA
void confDMA(){

	NVIC_DisableIRQ(DMA_IRQn);

	NVIC_SetPriority(DMA_IRQn, 9);

	GPDMA_Init();

    GPDMACfg.ChannelNum = 0;	//Canal 0
    GPDMACfg.SrcMemAddr = 0;	//ADC
    GPDMACfg.DstMemAddr = (uint32_t) &adc_value;
    GPDMACfg.TransferSize = DMA_SIZE;	//Tamaño de la transferencia
    GPDMACfg.TransferWidth = 0;	//No usado
    GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
    GPDMACfg.SrcConn = GPDMA_CONN_ADC;	//La fuente es memoria => no connection
    GPDMACfg.DstConn = 0;
    GPDMACfg.DMALLI = 0;
    GPDMA_Setup(&GPDMACfg);
    /*Reseteamos la cuenta en ambos flags*/
    Channel0_TC = 0;
    Channel0_Err = 0;

    NVIC_EnableIRQ(DMA_IRQn);
}

void transmitirDMA(){

	uint32_t tmp;
	GPDMA_ChannelCmd(0, ENABLE);
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	while ((Channel0_TC == 0) );
	GPDMA_ChannelCmd(0, DISABLE);
	for(tmp = 0; tmp < 1000000; tmp++);
	GPDMA_Setup(&GPDMACfg);
	temperaturaDMA=ADC_DR_RESULT(adc_value);

	/*Reseteamos las cuentas*/
	Channel0_TC = 0;
	Channel0_Err = 0;



}
