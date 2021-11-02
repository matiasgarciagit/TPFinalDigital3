
void confADC(void){
    //Configuramos ADC para que funicone con TIMER0 M1

    ADC_Init(LPC_ADC,200000);
    ADC_BurstCmd(LPC_ADC,DISABLE);
    ADC_StartCmd(LPC_ADC,ADC_START_ON_MAT01);
    ADC_EdgeStartConfig(LPC_ADC,1);
    //ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
    ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);
    NVIC_EnableIRQ(ADC_IRQn);

}

void ADC_IRQHandler(void)
{

ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF; //Variable auxiliar para observar el valor del registro de captura

if (ADC0Value<2054){
LPC_GPIO0->FIOSET = (1<<22);
}
else{
LPC_GPIO0->FIOCLR = (1<<22);
}

return;
}
