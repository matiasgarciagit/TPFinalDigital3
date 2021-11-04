
void confTimers(void){
    //TIMER0 M1 de 1 minuto
    TIM_TIMERCFG_Type	struct_config;
    TIM_MATCHCFG_Type	struct_match;

    struct_config.PrescaleOption	=	TIM_PRESCALE_USVAL;
    struct_config.PrescaleValue		=	500000;

    struct_match.MatchChannel		=	1;
    struct_match.IntOnMatch			=	ENABLE;
    struct_match.ResetOnMatch		=	ENABLE;
    struct_match.StopOnMatch		=	DISABLE;
    struct_match.ExtMatchOutputType	=	TIM_EXTMATCH_TOGGLE;
    struct_match.MatchValue			=	1; //119 para 1min

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &struct_config);
    TIM_ConfigMatch(LPC_TIM0, &struct_match);
    TIM_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);

    //TIMER1 M0 25u Segundos
    struct_config.PrescaleOption	=	TIM_PRESCALE_USVAL;
    struct_config.PrescaleValue		=	50000;

    struct_match.MatchChannel		=	0;
    struct_match.IntOnMatch			=	ENABLE;
    struct_match.ResetOnMatch		=	ENABLE;
    struct_match.StopOnMatch		=	DISABLE;
    struct_match.ExtMatchOutputType	=	TIM_EXTMATCH_TOGGLE;
    struct_match.MatchValue			=	1;

    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &struct_config);
    TIM_ConfigMatch(LPC_TIM1, &struct_match);
	//TIM_Cmd(LPC_TIM1, ENABLE);
    NVIC_EnableIRQ(TIMER1_IRQn);


    // Prioridades
    NVIC_SetPriority(TIMER1_IRQn, 1);
    NVIC_SetPriority(TIMER0_IRQn, 0);

}

void TIMER0_IRQHandler(void){
	mostrar=1;
	MinutosReloj++;
	if(MinutosReloj == 60){
		MinutosReloj = 0;
		HoraReloj++;
		if(HoraReloj == 24){
			HoraReloj = 0;
		}

	}
	LPC_TIM0->IR|= (1<<1);


}

void TIMER1_IRQHandler(void){
	led++;
	if(led==30){
		TIM_Cmd(LPC_TIM1, DISABLE);
		led=0;
		LPC_TIM1->EMR &= ~(1);
	}
	LPC_TIM1->IR|= (1);
}

