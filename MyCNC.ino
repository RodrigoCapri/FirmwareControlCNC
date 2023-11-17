#include <MStepper.h>
#include <Servo.h>

struct Maquina{
  float x;
  float y;
  float z;
};
Maquina eixo;

//Absolute steps position
int X;
int Y;
int Z;

MStepper motor_1(200, 4, 5, 6, 7);
MStepper motor_2(200, 8, 9, 10, 11);
MStepper motor_3(200, A0, A1, A2, A3);
int stepsPerMillimeter_X = 200;
int stepsPerMillimeter_Y = 200;
int stepsPerMillimeter_Z = 200;
double conversionFactor= 1;
int motorSpeed= 60;
int motorMode= 0;

Servo my_servo;
#define PIN_SERVO_MOTOR 12
int PIN_FERRAMENTA= 13;
int servoPosMax= 80;
int servoPosMin= 70;
int servo_increment= 1;
int vel_spindle;

void setup() {
  // put your setup code here, to run once:
  initCommands();
  initMotores();

  motor_1.set_function_auxiliar( &function_auxiliar );
  motor_2.set_function_auxiliar( &function_auxiliar );
  motor_3.set_function_auxiliar( &function_auxiliar );
  
  Serial.begin(9600);
  Serial.println("ready");
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    if( c != '\n'){
      addChar(c);
    }else{
      //Executar comando
      execute_comandos();
      //Limpar comando
      initCommands();
    }
  }
}

void function_auxiliar(){
  
}
