void retardo();

char keypress;
char keypad[5][4]={
        {'A','B','#','*'},
        {'1','2','3','m'},
        {'4','5','6','n'},
        {'7','8','9','F'},
        {'<','0','>','E'}
        };


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

void retardo(void){
    uint32_t contador;
    for(contador =0 ; contador<100000; contador++){};
}
