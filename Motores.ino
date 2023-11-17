#define MAX_VEL_EiXOS 60

void initMotores(){
  eixo.x= 0;
  eixo.y= 0;
  eixo.z= 0;
  X= 0;
  Y= 0;
  Z= 0;
  
  motor_1.setSpeed(MAX_VEL_EiXOS);
  motor_2.setSpeed(MAX_VEL_EiXOS);
  motor_3.setSpeed(MAX_VEL_EiXOS);
  motorSpeed= MAX_VEL_EiXOS;

  my_servo.attach(PIN_SERVO_MOTOR);
  my_servo.write(servoPosMax);
  pinMode(PIN_FERRAMENTA, OUTPUT);
}

void setXYSpeed(int vel){
  // remember
  motorSpeed = vel;
  
  motor_1.setSpeed(motorSpeed);
  motor_2.setSpeed(motorSpeed);
  motor_3.setSpeed(motorSpeed);
  
}

//Movimento dos motore de passo
void moveX(int dX){
  X+= dX;
  motor_1.step(dX);
}
void moveY(int dY){
  Y+= dY;
  motor_2.step(dY);
}
void moveZ(int dZ)
{
  Z+= dZ;  

  switch(motorMode) {
  case 0: //Quando eixo Z for com motor de passo
    motor_3.setSpeed(motorSpeed);
    motor_3.step(dZ);
    break;
  case 1: //Quando eixo Z for com servo motor sendo 1:Levanta, 0:Abaixas
    digitalWrite(PIN_FERRAMENTA,(eixo.z < 1) ? HIGH : LOW);
    //updateServo((eixo.z < 1) ? servoPosMin : servoPosMax);
    delay(100);
    break;
  case 2: //Quando eixo Z for com servo motor com posição definida por parametro
    //updateServo(servoPosMin + (servoPosZfactor*posZ));
    delay(200);
    break;
  case 3: //Apenas a ferramenta
    digitalWrite(PIN_FERRAMENTA,(eixo.z < 1) ? HIGH : LOW);
    break;
  }
}

void moveToX(int pX){
  moveX(pX - X);
}
void moveToY(int pY){
  moveY(pY - X);
}
void moveToZ(int pZ){
  moveZ(pZ - X);
}
void moveToXYZ(int pX, int pY, int pZ){
  if (pX - X)
    moveX(pX - X);
  if (pY - Y)
    moveY(pY - Y);
  if (pZ - Z)
    moveZ(pZ - Z);
}

void powerdown(){
  // Stepper 1
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  // Stepper 2  
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  // Stepper 3  
  digitalWrite(16,LOW);
  digitalWrite(17,LOW);
  digitalWrite(18,LOW);
  digitalWrite(19,LOW);
}

int sgn(int value){
  return value < 0 ? -1 : value > 0;
}

void movePosXYZ(float x2, float y2, float z2, int speed ){ //Percorre uma linha reta definindo a velocidade
  setXYSpeed(speed);
  linePos(x2, y2, z2);
}
void linePos(float x2, float y2, float z2){ //Percorre uma linha reta com velocidade pré-definida
  lineXYZ(convertPosX(x2),convertPosY(y2),convertPosZ(z2));
  eixo.x = x2;
  eixo.y = y2;
  eixo.z = z2;
}
void lineXYZ(int x2, int y2, int z2){
  int n, deltax, deltay, deltaz, sgndeltax, sgndeltay, sgndeltaz, deltaxabs, deltayabs, deltazabs, x, y, z, drawx, drawy, drawz;

  deltax = x2 - X;
  deltay = y2 - Y;
  deltaz = z2 - Z;
  deltaxabs = abs(deltax);
  deltayabs = abs(deltay);
  deltazabs = abs(deltaz);
  sgndeltax = sgn(deltax);
  sgndeltay = sgn(deltay);
  sgndeltaz = sgn(deltaz);
  x = deltayabs >> 1;
  y = deltaxabs >> 1;
  z = deltazabs >> 1;
  drawx = X;
  drawy = Y;
  drawz = Z;
  
  moveToXYZ(drawx, drawy, drawz);
  
  // dX is biggest
  if(deltaxabs >= deltayabs && deltaxabs >= deltazabs){
    for(n = 0; n < deltaxabs; n++){
      y += deltayabs;
      if(y >= deltaxabs){
        y -= deltaxabs;
        drawy += sgndeltay;
      }
      z += deltazabs;
      if(z >= deltaxabs){
        z -= deltaxabs;
        drawz += sgndeltaz;
      }

      drawx += sgndeltax;
      moveToXYZ(drawx, drawy, drawz);
    }
    return;
  }
  // dY is biggest
  if(deltayabs >= deltaxabs && deltayabs >= deltazabs){
    for(n = 0; n < deltayabs; n++){
      x += deltaxabs;
      if(x >= deltayabs){
        x -= deltayabs;
        drawx += sgndeltax;
      }
      z += deltazabs;
      if(z >= deltayabs){
        z -= deltayabs;
        drawz += sgndeltaz;
      }
      drawy += sgndeltay;
      moveToXYZ(drawx, drawy, drawz);
    }
    return;
  }
  // dZ is biggest
  if(deltazabs >= deltaxabs && deltazabs >= deltayabs){
    for(n = 0; n < deltazabs; n++){
      x += deltaxabs;
      if(x >= deltazabs){
        x -= deltazabs;
        drawx += sgndeltax;
      }
      y += deltayabs;
      if(y >= deltazabs){
        y -= deltazabs;
        drawy += sgndeltay;
      }
      drawz += sgndeltaz;
      moveToXYZ(drawx, drawy, drawz);
    }
    return;
  }
}


//Conversão dos valores dos motores para inteiro
int convertPosX(float pos){
  return (int) (pos * stepsPerMillimeter_X * conversionFactor);
}
int convertPosY(float pos){
  return (int) (pos * stepsPerMillimeter_Y * conversionFactor);
}
int convertPosZ(float pos){
  return (int) (pos * stepsPerMillimeter_Z * conversionFactor);
}
