void retardo();
char cvalue;
char keypress;

char keypad[5][4]={
        {'A','B','#','*'},
        {'1','2','3','m'},
        {'4','5','6','n'},
        {'7','8','9','F'},
        {'<','0','>','E'}
        };

/*
char readkey(){

    uint8_t i;
    uint8_t j;
    LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
    for(i=4;i<9;i++){
        LPC_GPIO2->FIOCLR |= (1<<i);//11101||1111)
        for(j=0;j<4;j++){
            if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                return keypad[8-i][j];
            }
        }
        LPC_GPIO2->FIOSET |= (1<<i);
        //retardo();
    }
    return 'r';
}

*/


char presiona(){
	uint8_t cont=0;
	uint8_t i;
	uint8_t j;
    while(1){

        LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
        for(i=4;i<9;i++){
            LPC_GPIO2->FIOCLR |= (1<<i);//11110||1111)
            for(j=0;j<4;j++){
                if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                	cont++;
					if(cont==3){
						keypress=keypad[8-i][j];
						return keypad[8-i][j];

					}
					LPC_GPIO2->FIOSET |= (1<<i);
					i=4;
					j=0;
					LPC_GPIO2->FIOCLR |= (1<<i);
					retardo10ms();
                }

            }
            LPC_GPIO2->FIOSET |= (1<<i);

        }
       cont=0;
    }
}


char readkey(){
	uint8_t cont=0;
	uint8_t aux=20;
	uint8_t i;
	uint8_t j;
    while(aux){

        LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
        for(i=4;i<9;i++){
            LPC_GPIO2->FIOCLR |= (1<<i);//11110||1111)
            for(j=0;j<4;j++){
                if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                	cont++;
					if(cont==3){
						keypress=keypad[8-i][j];
						return keypad[8-i][j];

					}
					LPC_GPIO2->FIOSET |= (1<<i);
					i=4;
					j=0;
					LPC_GPIO2->FIOCLR |= (1<<i);
					retardo10ms();
                }

            }
            LPC_GPIO2->FIOSET |= (1<<i);
            
        }
       cont=0;
       aux--;
    }
    return 'r';
}

void suelta(){
	uint8_t i;
	uint8_t j;
	LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
	for(i=4;i<9;i++){
	    LPC_GPIO2->FIOCLR |= (1<<i);//11101||1111)
	    for(j=0;j<4;j++){
	         if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
	             i=4;
	             j=0;
	         }
	    }
	    LPC_GPIO2->FIOSET |= (1<<i);
	}
}

void retardo(void){
    uint32_t contador;
    for(contador =0 ; contador<100000; contador++){};
}

