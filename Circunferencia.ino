
#define LIMITE_DIF_X 0.1 //Funcionou com0.6
#define LIMITE_DIF_Y 0.2
#define VAL_INCREMENT 0.01 //Funcionou com 0.01
#define CIRCLE 0 //Circulo completo
#define LEFT 1 //Esquerda
#define RIGTH 2 //Direita

//a,b seria o ponto do centro do arco
float a, b;
float raio;

// Aqui faz o processo de desenhar um arco ou circunferencia
void drawCircunferenciaG3(float x, float y, float i, float j) {
    //Equação geral da circunferencia
    // x^2 + y^2 - 2ax - 2by + a^2 + b^2 - R^2 = 0
    // x^2 - (d*x) - e + f
    //Define o centro do arco
    a = eixo.x + i;
    b = eixo.y + j;
    //
    //Equação de distancia para pegar o raio, calcula a distância entre o inicio arco e o centro do arco
    float delta_x = pow( ( a - eixo.x) , 2);
    float delta_y = pow( ( b - eixo.y) , 2);
    raio = sqrt( (delta_x + delta_y) ); // distancia essa que é o raio
    //
    int diretion_x= 0; // Variável para determinar a direção do movimento
    int diretion_circle= 0; //Variável para determinar a direção inical de um circulo
    //Para determinar a direção inicial do arco usa-se a posição relativa do ponto inicial para o centro do arco

    if(eixo.x == x && eixo.y == y){ // Caso for uma Circunferencia completa, ha outro esquema
        diretion_x= CIRCLE;
        if(eixo.y > b){
            diretion_circle = LEFT;
        }else
            if(eixo.y < b){
                diretion_circle = RIGTH;
        }else 
            if(eixo.y == b && eixo.x < a){
                diretion_circle = RIGTH;
        }else 
            if(eixo.y == b && eixo.x > a){
                diretion_circle = LEFT;
        }
    }else
        if(eixo.y > b){
            diretion_x = LEFT;
    }else
        if(eixo.y < b){
            diretion_x = RIGTH;
    }else
        if(eixo.y == b && eixo.x < a){
            diretion_x = RIGTH;
    }else
        if(eixo.y == b && eixo.x > a){
            diretion_x = LEFT;
    }

    //Inicia-se então os ciclcos para desenhar o arco
    float position_x= eixo.x;
    while( !( ( (eixo.x >= (x-LIMITE_DIF_X) ) && (eixo.x <= (x+LIMITE_DIF_X) ) ) &&
            ( (eixo.y >= (y-LIMITE_DIF_Y) ) && (eixo.y <= (y+LIMITE_DIF_Y)) ) )  ||
            (diretion_x == CIRCLE) ){

        float resultado = 0;

        switch(diretion_x){
            case CIRCLE:{
                switch(diretion_circle){
                    case LEFT:{
                        if(position_x <= (a-raio) ){ //Se o valor de X for maior ou igual ao extremo do raio, então muda a direção
                            position_x= (a-raio);
                            diretion_x= RIGTH;
                            linePos(position_x, eixo.y, eixo.z);
                        }else{ //Se o valor de X ainda estiver dentro do raio, então o calculo será realizado
                            float val_x = position_x - a;
                            float resultado_potencias = ( pow(val_x, 2)- pow(raio, 2) );

                            if(resultado_potencias < 0)
                                resultado_potencias *= -1;
                            resultado = sqrt( resultado_potencias );

                            linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação
                            position_x -= VAL_INCREMENT; // Incrementa o eixo X para os calculos
                        }
                    }break;
                    case RIGTH:{
                        if(position_x >= (a+raio) ){
                            position_x= (a+raio);
                            diretion_x= LEFT;
                            linePos(position_x, eixo.y, eixo.z);
                        }else{
                            float val_x= position_x - a;
                            float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                            if(resultado_potencias < 0)
                                resultado_potencias *= -1;
                            resultado = sqrt( resultado_potencias );

                            resultado*= -1; //Como é sentido anti-horário, então deve-se inverter o resultado do Y na ocasião do X ser incrementado

                            linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação 
                            position_x+= VAL_INCREMENT;
                        }
                    }break;
                }

            }break;
            case LEFT:{
                if(position_x <= (a-raio) ){ //Se o valor de X for maior ou igual ao extremo do raio, então muda a direção
                    position_x= (a-raio);
                    diretion_x= RIGTH;
                    linePos(position_x, eixo.y, eixo.z);
                }else{ //Se o valor de X ainda estiver dentro do raio, então o calculo será realizado
                    float val_x= position_x - a;
                    float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                    if(resultado_potencias < 0)
                        resultado_potencias *= -1;
                    resultado= sqrt( resultado_potencias );

                    linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação
                    position_x-= VAL_INCREMENT; // Incrementa o eixo X para os calculos
                }

            }break;
            case RIGTH:{
                if(position_x >= (a+raio) ){
                    position_x= (a+raio);
                    diretion_x= LEFT;
                    linePos(position_x, eixo.y, eixo.z);
                }else{
                    float val_x= position_x - a;
                    float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                    if(resultado_potencias < 0)
                        resultado_potencias *= -1;
                    resultado= sqrt( resultado_potencias );

                    resultado*= -1; //Como é sentido anti-horário, então deve-se inverter o resultado do Y na ocasião do X ser incrementado

                    linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação 
                    position_x+= VAL_INCREMENT;
                }

            }break;
        }
        //Serial.print("=> "); 
        //Serial.print(eixo.x); Serial.print(" , ");
        //Serial.print(eixo.y);
        //Serial.println("");
    }
    linePos(x, y, eixo.z);
}

void drawCircunferenciaG2(float x, float y, float i, float j) {
    //Define o centro do arco
    a = eixo.x + i;
    b = eixo.y + j;
    //
    //Equação de distancia para pegar o raio, calcula a distância entre o inicio arco e o centro do arco
    float delta_x = pow(( a - eixo.x), 2);
    float delta_y = pow(( b - eixo.y), 2);
    raio = sqrt((delta_x + delta_y)); // distancia essa que é o raio
    //
    int diretion_x= 0; // Variável para determinar a direção do movimento
    int diretion_circle= 0; //Variável para determinar a direção inical de um circulo
    //Para determinar a direção inicial do arco usa-se a posição relativa do ponto inicial para o centro do arco

    if(eixo.x == x && eixo.y == y){ // Caso for uma Circunferencia completa, ha outro esquema
        diretion_x= CIRCLE;
        if(eixo.y > b){
            diretion_circle = RIGTH;
        }else if(eixo.y < b){
            diretion_circle = LEFT;
        }else if(eixo.y == b && eixo.x < a){
            diretion_circle = RIGTH;
        }else if(eixo.y == b && eixo.x > a){
            diretion_circle = LEFT;
        }
    }else if(eixo.y > b){
        diretion_x = RIGTH;
    }else if(eixo.y < b){
        diretion_x = LEFT;
    }else if(eixo.y == b && eixo.x < a){
        diretion_x = RIGTH;
    }else if(eixo.y == b && eixo.x > a){
        diretion_x = LEFT;
    }
    //System.out.println("Raio: "+raio);
    //Inicia-se então os ciclcos para desenhar o arco
    float position_x= eixo.x;

    while( !( ( (eixo.x >= (x-LIMITE_DIF_X)) && (eixo.x <= (x+LIMITE_DIF_X)) ) &&
            ( (eixo.y >= (y-LIMITE_DIF_Y)) && (eixo.y <= (y+LIMITE_DIF_Y))) )  ||
            (diretion_x == CIRCLE) ){

        float resultado;

        switch(diretion_x){
            case CIRCLE:{

                switch(diretion_circle){
                    case LEFT:{
                        if(position_x <= (a-raio) ){ //Se o valor de X for maior ou igual ao extremo do raio, então muda a direção
                            position_x= (a-raio);
                            diretion_x= RIGTH;
                            linePos(position_x, eixo.y, eixo.z);
                        }else{ //Se o valor de X ainda estiver dentro do raio, então o calculo será realizado
                            float val_x= eixo.x - a;
                            float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                            if(resultado_potencias < 0)
                                resultado_potencias *= -1;
                            resultado= sqrt( resultado_potencias );

                            resultado*= -1; //Como é sentido horário, então deve-se inverter o resultado do Y na ocasião do X ser incrementado

                            linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação

                            position_x-= VAL_INCREMENT; // Incrementa o eixo X para os calculos
                        }
                    }break;
                    case RIGTH:{
                        if(position_x >= (a+raio) ){
                            position_x= (a+raio);
                            diretion_x= LEFT;
                            linePos(position_x, eixo.y, eixo.x);
                        }else{
                            float val_x= eixo.x - a;
                            float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                            if(resultado_potencias < 0)
                                resultado_potencias *= -1;
                            resultado= sqrt( resultado_potencias );

                            linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação 

                            position_x+= VAL_INCREMENT;
                        }
                    }break;
                }

            }break;
            case LEFT:{
                if(position_x <= (a-raio) ){ //Se o valor de X for maior ou igual ao extremo do raio, então muda a direção
                    position_x= (a-raio);
                    diretion_x= RIGTH;
                    linePos(position_x, eixo.y, eixo.z);
                }else{ //Se o valor de X ainda estiver dentro do raio, então o calculo será realizado
                    float val_x= eixo.x - a;
                    float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                    if(resultado_potencias < 0)
                        resultado_potencias *= -1;
                    resultado= sqrt( resultado_potencias );


                    resultado*= -1; //Como é sentido horário, então deve-se inverter o resultado do Y na ocasião do X ser incrementado

                    linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação

                    position_x-= VAL_INCREMENT; // Incrementa o eixo X para os calculos
                }

            }break;
            case RIGTH:{
                if(position_x >= (a+raio)){
                    position_x= (a+raio);
                    diretion_x= LEFT;
                    linePos(position_x, eixo.x, eixo.y);
                }else{
                    float val_x= eixo.x - a;
                    float resultado_potencias= ( pow(val_x, 2)- pow(raio, 2) );

                    if(resultado_potencias < 0)
                        resultado_potencias *= -1;
                    resultado= sqrt( resultado_potencias );

                    linePos(position_x, resultado+b, eixo.z); //Desenha uma reta com as coordenadas resultantes da equação 

                    position_x+= VAL_INCREMENT;
                }

            }break;
        }
        Serial.print("=> ");
        Serial.print(eixo.x); Serial.print(" , ");
        Serial.print(eixo.y);
        Serial.println("");
    }

    linePos(x, y, eixo.z);
    //System.out.println("Final G2");
}
