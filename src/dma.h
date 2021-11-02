#define DMA_SIZE		16

void confDMA(){

    GPDMA_Channel_CFG_Type GPDMACfg;	//Estructura de configuracion del DMA
    GPDMA_Init();	//Inicializa el modulo DMA

    GPDMACfg.ChannelNum = 0;	//Canal 0
    GPDMACfg.SrcMemAddr = 0;	//Origen
    GPDMACfg.DstMemAddr = &ADCdma;	//Destino = es un periferico, no es memoria
    GPDMACfg.TransferSize = DMA_SIZE;	//Tamaño de la transferencia
    GPDMACfg.TransferWidth = 0;	//No usado
    GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
    GPDMACfg.SrcConn = GPDMA_CONN_ADC;	//La fuente es memoria => no connection
    GPDMACfg.DstConn = 0;	//Destino : conexión al ADC
    GPDMACfg.DMALLI = 0;	//Lista de enlace del DMA
    GPDMA_Setup(&GPDMACfg);
    GPDMA_ChannelCmd(0, ENABLE);	//Enciende el modulo DMA

}

