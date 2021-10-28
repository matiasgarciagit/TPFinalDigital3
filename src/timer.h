
void confTimers(void){
    //TIMER0 M1 de 1 minuto
    TIM_TIMERCFG_Type	struct_config;
    TIM_MATCHCFG_Type	struct_match;

    struct_config.PrescaleOption	=	TIM_PRESCALE_USVAL;
    struct_config.PrescaleValue		=	1000000;

    struct_match.MatchChannel		=	1;
    struct_match.IntOnMatch			=	ENABLE;
    struct_match.ResetOnMatch		=	ENABLE;
    struct_match.StopOnMatch		=	DISABLE;
    struct_match.ExtMatchOutputType	=	TIM_EXTMATCH_TOGGLE;
    struct_match.MatchValue			=	59;

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &struct_config);
    TIM_ConfigMatch(LPC_TIM0, &struct_match);
    TIM_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);

    //TIMER1 M0 15 segundos
    struct_config.PrescaleOption	=	TIM_PRESCALE_USVAL;
    struct_config.PrescaleValue		=	1000000;

    struct_match.MatchChannel		=	0;
    struct_match.IntOnMatch			=	ENABLE;
    struct_match.ResetOnMatch		=	ENABLE;
    struct_match.StopOnMatch		=	DISABLE;
    struct_match.ExtMatchOutputType	=	TIM_EXTMATCH_NOTHING;
    struct_match.MatchValue			=	14;

    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &struct_config);
    TIM_ConfigMatch(LPC_TIM1, &struct_match);
    TIM_Cmd(LPC_TIM1, ENABLE);
    NVIC_EnableIRQ(TIMER1_IRQn);

}
