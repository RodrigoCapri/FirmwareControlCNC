String comando;

void initCommands(){
  comando= "";
}

void addChar(char c){
  comando+= c;
}

boolean isExistChar(char c){
  boolean result= false;
  for(int i=0; i<comando.length(); i++){
    if( c == comando[i] ){
      result= true;
      break;
    }
  }
  return result;
}

int getValorInt(char c){
  int count= 0;
  char valor[10]= "";
  int ctt= 0;

  //Percorre a estring até achar o caractere desejado e armazena o seu índice
  for(int i=0; i<comando.length(); i++, count++){
    if( c == comando[i] ){
      count++;
      break;
    }
  }

  //Com o índice já obtido percorre-se então a string de comando até encontrar espaço
  for(int i=count; i<comando.length(); i++, ctt++){
    if(comando[i] == ' ')
      break;
    else
      valor[ctt]= comando[i];
  }

  //Agora retorna o valor convertendo a string numerica para inteiro
  return atoi(valor);
}

float getValorFloat(char c){
  int count= 0;
  char valor[10]= "";
  int ctt= 0;

  //Percorre a estring até achar o caractere desejado e armazena o seu índice
  for(int i=0; i<comando.length(); i++, count++){
    if( c == comando[i] ){
      count++;
      break;
    }
  }

  //Com o índice já obtido percorre-se então a string de comando até encontrar espaço
  for(int i=count; i<comando.length(); i++, ctt++){
    if(comando[i] == ' ')
      break;
    else
      valor[ctt]= comando[i];
  }

  //Agora retorna o valor convertendo a string numerica para flaot
  return atof(valor);
}
