int code;

void execute_comandos(){
  
  if( isExistChar('G') ){
    code= getValorInt('G');
    int velocidade;
    float A, B, C, I, J;
    switch(code){
      case 0:{
          A = (isExistChar('X')) ? getValorFloat('X') : eixo.x;
          B = (isExistChar('Y')) ? getValorFloat('Y') : eixo.y;
          C = (isExistChar('Z')) ? getValorFloat('Z') : eixo.z;
          movePosXYZ( A, B, C, 60);
      }break;
      case 1:{
         A = (isExistChar('X')) ? getValorFloat('X') : eixo.x;
         B = (isExistChar('Y')) ? getValorFloat('Y') : eixo.y;
         C = (isExistChar('Z')) ? getValorFloat('Z') : eixo.z;
         velocidade=  (isExistChar('F')) ? getValorInt('F'):motorSpeed;
         movePosXYZ( A, B, C, velocidade);
      }break;
      case 2:{ //Movimento circular horario
        velocidade= (isExistChar('F')) ? getValorInt('F'):motorSpeed;
        setXYSpeed(velocidade);
        if( isExistChar('X') ) A = getValorFloat('X');
        if( isExistChar('Y') ) B = getValorFloat('Y');
        if( isExistChar('I') ) I = getValorFloat('I');
        if( isExistChar('J') ) J = getValorFloat('J');
        drawCircunferenciaG2( A, B, I, J); 
      }break;
      case 3:{ //Movimento circular anti-horario
        velocidade= (isExistChar('F')) ? getValorInt('F'):motorSpeed;
        setXYSpeed(velocidade);
        if( isExistChar('X') ) A = getValorFloat('X');
        if( isExistChar('Y') ) B = getValorFloat('Y');
        if( isExistChar('I') ) I = getValorFloat('I');
        if( isExistChar('J') ) J = getValorFloat('J');
        drawCircunferenciaG3( A, B, I, J); 
      }break;
      case 4:{ //Uma pausa no script
        int tempo= 0;
        if(  isExistChar('P') ) tempo= getValorInt('P');
        delay(tempo);
      }break;
      case 20:{ //Define valores em polegadas por unidade
        conversionFactor= 25.4;
      }break;
      case 21:{ //Define valores em milimetros por unidade
        conversionFactor= 1;
      }break;
      case 28:{ //Volta os eixos na posição zero
        movePosXYZ(0, 0, 0, 60);
      }break;
      case 30:{ //Vai até o ponto desejado e depois volta ao ponto anterior
        
      }break;
      case 81:{ //Operação drill
        
      }break;
      case 92:{ //Reseta os eixos em zero
        eixo.x= 0;
        eixo.y= 0;
        eixo.z= 0;
        X= 0;
        Y= 0;
        Z= 0;
      }break;
    }
    Serial.println("ok");
    
  }else if( isExistChar('M') ){
    int code_m= getValorInt('M');
    switch(code_m){
      case 4:{ //define a velocidade do spindle e liga-o "M4 S500"
        vel_spindle= ( isExistChar('S') ) ? getValorInt('S') : vel_spindle;
        digitalWrite(PIN_FERRAMENTA, HIGH);
      }break;
      case 5:{ //Desliga o spindle
        digitalWrite(PIN_FERRAMENTA, LOW);
      }break;
      case 18:{ //Para e desliga todos os motores de passo
        powerdown();
      }break;
      case 150:{ //Define os modos dos motores
        motorMode= ( isExistChar('S') ) ? getValorInt('S') : motorMode;
      }break;
      case 151:{ //Define a posição maxima do servo motor
        servoPosMax= ( isExistChar('S') ) ? getValorInt('S') : servoPosMax;
      }break;
      case 152:{ //Define a posição mínima do servo motor
        servoPosMin= ( isExistChar('S') ) ? getValorInt('S') : servoPosMin;
      }break;
      case 123:{ //Define o valor de incrementação do servo
        servo_increment= ( isExistChar('S') ) ? getValorInt('S') : servo_increment;
      }break;
      case 160:{ //Define o numero de passos por milimetro no eixo X
        stepsPerMillimeter_X= ( isExistChar('S') ) ? getValorInt('S') : stepsPerMillimeter_X;
      }break;
      case 161:{ //Define o numero de passos por milimetro no eixo Y
        stepsPerMillimeter_Y= ( isExistChar('S') ) ? getValorInt('S') : stepsPerMillimeter_Y;
      }break;
      case 162:{ //Define o numero de passos por milimetro no eixo Z
        stepsPerMillimeter_Z= ( isExistChar('S') ) ? getValorInt('S') : stepsPerMillimeter_Z;
      }break;
    }
    Serial.println("ok");
  }else if( isExistChar('E') ){
    int code_e= getValorInt('E');
    switch(code_e){
      case 1:{ //Pausar motores
          motor_1.pause_motor();
          motor_2.pause_motor();
          motor_3.pause_motor();
      }break; 
      case 2:{ //Resumir motores
          motor_1.resume_motor();
          motor_2.resume_motor();
          motor_3.resume_motor();
      }break;
    }
    Serial.println("ok");
  }else{
    Serial.println("???");
  }
  
}
