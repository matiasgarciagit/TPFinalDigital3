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
	// check GPDMA interrupt on channel 0
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 0)){
		// Check counter terminal status
		if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)){
			// Clear terminate counter Interrupt pending
			GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 0);
				Channel0_TC++;
		}
		// Check error terminal status
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
	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(DMA_IRQn, (2));
	/* Initialize GPDMA controller */
	GPDMA_Init();

    GPDMACfg.ChannelNum = 0;	//Canal 0
    GPDMACfg.SrcMemAddr = 0;	//Origen
    GPDMACfg.DstMemAddr = (uint32_t) &adc_value;	//Destino = es un periferico, no es memoria
    GPDMACfg.TransferSize = DMA_SIZE;	//Tamaño de la transferencia
    GPDMACfg.TransferWidth = 0;	//No usado
    GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
    GPDMACfg.SrcConn = GPDMA_CONN_ADC;	//La fuente es memoria => no connection
    GPDMACfg.DstConn = 0;	//Destino : conexión al ADC
    GPDMACfg.DMALLI = 0;
    GPDMA_Setup(&GPDMACfg);
    /* Reset terminal counter */
    Channel0_TC = 0;
    /* Reset Error counter */
    Channel0_Err = 0;
    /* Enable GPDMA interrupt */
    NVIC_EnableIRQ(DMA_IRQn);
}

void transmitirDMA(){
	uint32_t tmp;
	GPDMA_ChannelCmd(0, ENABLE);
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	/* Wait for GPDMA processing complete */;
	while ((Channel0_TC == 0) );
	// Disable GPDMA channel 0
	GPDMA_ChannelCmd(0, DISABLE);
	// Wait for a while
	for(tmp = 0; tmp < 1000000; tmp++);
	/* GPDMA Re-setup */
	GPDMA_Setup(&GPDMACfg);
	/* Reset terminal counter */

	temperaturaDMA=ADC_DR_RESULT(adc_value);

	Channel0_TC = 0;
	/* Reset Error counter */
	Channel0_Err = 0;

	//Temp = (ADC_DR_RESULT(adc_value)/4096*80)-20;


}
