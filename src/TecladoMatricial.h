void retardo();
char cvalue;
char keypress;
//Mapeo del teclado
char keypad[5][4]={
        {'A','B','#','*'},
        {'1','2','3','m'},
        {'4','5','6','n'},
        {'7','8','9','F'},
        {'<','0','>','E'}
        };


char presiona(){//Espera a que se presione una tecla y retorna su valor
				//Con algoritmo antirebote
	uint8_t cont=0;
	uint8_t i;
	int8_t j;
    while(1){

        LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
        for(i=4;i<9;i++){
            LPC_GPIO2->FIOCLR |= (1<<i);//11110||1111)
            for(j=0;j<4;j++){
                if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                	cont++;
					if(cont==5){
						keypress=keypad[8-i][j];
						return keypad[8-i][j];

					}
					LPC_GPIO2->FIOSET |= (1<<i);
					i=4;
					j=-1;
					LPC_GPIO2->FIOCLR |= (1<<i);
					retardoms();
                }

            }
            LPC_GPIO2->FIOSET |= (1<<i);

        }
       cont=0;
    }

}


char readkey(){//Algoritmo de lectura de teclado, haya presionado una tecla o no
	uint8_t cont=0;
	uint8_t aux=5;
	uint8_t i;
	int8_t j;
    while(aux){

        LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
        for(i=4;i<9;i++){
            LPC_GPIO2->FIOCLR |= (1<<i);//11110||1111)
            for(j=0;j<4;j++){
                if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
                	cont++;
                	aux=5;
					if(cont==5){
						keypress=keypad[8-i][j];
						return keypad[8-i][j];

					}
					LPC_GPIO2->FIOSET |= (1<<i);
					i=4;
					j=-1;
					LPC_GPIO2->FIOCLR |= (1<<i);
					retardoms();
                }

            }
            LPC_GPIO2->FIOSET |= (1<<i);
            
        }
       cont=0;
       aux--;
    }
    return 'r';
}

void suelta(){//Comprueba que no haya ninguna tecla presionada
	uint8_t i;
	int8_t j;
	LPC_GPIO2->FIOPIN = (31<<4); //(11111||1111)
	for(i=4;i<9;i++){
	    LPC_GPIO2->FIOCLR |= (1<<i);//11101||1111)
	    for(j=0;j<4;j++){
	         if(!((LPC_GPIO2->FIOPIN)&(1<<j))){
	             i=4;
	             j=-1;
	         }
	    }
	    LPC_GPIO2->FIOSET |= (1<<i);
	}
}


