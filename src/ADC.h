
void confADC(void){
    //Configuramos ADC para que funcione con DMA

	ADC_Init(LPC_ADC, 200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);

}

