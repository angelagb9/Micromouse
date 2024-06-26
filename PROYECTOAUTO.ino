#include <PID_v1.h>
#include <Encoder.h>
#include "Motor.h"
#include "Sensores.h"

#define sensorF 15
#define sensorEI 2
#define sensorI 4
#define sensorED 13
#define sensorD 12

#define IN1 26
#define IN2 25
#define IN3 32
#define IN4 33

#define CANAL_A 0
#define CANAL_B 1
#define CANAL_C 2
#define CANAL_D 3

#define ENCODER1A 14
#define ENCODER1B 27
#define ENCODER2A 18
#define ENCODER2B 19

#define BOTON 22
#define LED 23

#define MEDIA 2200
#define AVANZAR 700
#define AVANZAR2 600
#define VUELTA180 2250

#define KP 1
#define KD 1.5
#define KI 0.5

//#define KP2 0.3
//#define KD2 5
//#define KI2 0

#define KP2 0.1
#define KD2 0.5
#define KI2 10

#define VELOCIDAD 180

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

#define offset 1000

int estado=1;

int opcionMenu = 0;
int posEncoderD = 0;
int posEncoderI = 0;
int posAntEncoderD = 0;
int posAntEncoderI = 0;
double Input, Output, Setpoint;
int dir;

Motor motorDerecho = Motor(IN1, IN2, CANAL_A, CANAL_B);
Motor motorIzquierdo = Motor(IN3, IN4, CANAL_C, CANAL_D);
Encoder encoderI = Encoder(19,18);
Encoder encoderD=Encoder(14,27);
PID myPID(&Input, &Output, &Setpoint,KP,KI,KD, DIRECT);
PID myPID2(&Input, &Output, &Setpoint,KP2,KI2,KD2, DIRECT);
Sensores sensores(sensorD,sensorI,sensorED,sensorEI,sensorF);

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BOTON,INPUT);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);
  myPID2.SetMode(AUTOMATIC);
  myPID2.SetOutputLimits(-255, 255);
}

void loop() {
//sensores.imprimirSensores();
//      switch(opcionMenu){
//          case 0: cambiarEstado();
//                break;
//        case 1: mapear();
//                break;
//        default: opcionMenu=0;
//                break;
//      }
//leerEncoders();
}
void cambiarEstado() {
  if (digitalRead(BOTON) == LOW) {
    long tiempoInicial = millis();
    while (digitalRead(BOTON) == LOW);
    long tiempoFinal = millis();
    long tiempo = (tiempoFinal - tiempoInicial) / 1000;
    if (tiempo >= 5.0) {
      opcionMenu = 0;
    }
    else {
      delay(500);
      opcionMenu = 1;
    }
  }
}
//void leerEncoders(){
//  Serial.print("Encoder Derecho: ");
//  Serial.print(encoderD.read());
//  Serial.print("Encoder Izquierdo: ");
//  Serial.println(encoderI.read());
//  
//}
//void moverMotores(){
//  motorDerecho.setMotor(255);
//  motorIzquierdo.setMotor(255);
//  delay(2000);
//  motorDerecho.setMotor(0);
//  motorIzquierdo.setMotor(0);
//  delay(2000);
//  motorDerecho.setMotor(-255);
//  motorIzquierdo.setMotor(-255);
//  delay(2000);
//  motorDerecho.setMotor(0);
//  motorIzquierdo.setMotor(0);
//  delay(2000);
//}

void mapear(){
 if(sensores.paredFrente() && sensores.paredDerecha() && !sensores.paredIzquierda()){
     //Serial.println("Gira a la izquierda");
     vueltaIzquierda();
     avanzar(AVANZAR);
     Izquierdo();
    }
  else if(sensores.paredFrente() && !sensores.paredDerecha() && sensores.paredIzquierda()){
      //Serial.println("Gira a la Derecha");
      //Serial.println(sensores.getSensorDerecho());
      vueltaDerecha();
      avanzar(AVANZAR2);
      Derecho();
    }
  else if(!sensores.paredDerecha()){
    Derecho();
    //Serial.println("Gira a la Derecha");
    //Serial.println(sensores.getSensorDerecho());
    avanzar(AVANZAR);
    vueltaDerecha();
    avanzar(AVANZAR2);
    }
  else if(sensores.getSensorFrente()>3500 && sensores.paredDerecha() && sensores.paredIzquierda()){
      vuelta180();
      avanzar(AVANZAR);
      vuelta180D();
    }
    //else if(!sensores.paredFrente() && sensores.paredDerecha() && !sensores.paredIzquierda()){
        //Input = 120-sensores.getSensorDerecho();
        //pid2();
      //}
  else {
      //Input = sensores.getSensorIzquierdo()-sensores.getSensorDerecho()-100;
      //pid();
      setDirection(FORWARD,VELOCIDAD,VELOCIDAD);
   }
   //Serial.print("Estado: ");
   //Serial.println(estado);
}
void detenerMotores(){
  motorDerecho.setMotor(0);
  motorIzquierdo.setMotor(0);
}
void pid(){
  Setpoint = 0;
  myPID.Compute();
  if(Output>VELOCIDAD) Output=VELOCIDAD;
  if(Output<-VELOCIDAD) Output=-VELOCIDAD;
  double RMS = VELOCIDAD + Output;
  double LMS = VELOCIDAD - Output;

  if(RMS<0){
     RMS = map(RMS , 0 , -255, 0, 255);
     setDirection(RIGHT, LMS, RMS);
  }
  else if(LMS<0){
    LMS = map(LMS , 0 , -255, 0, 255);
    setDirection(LEFT, LMS,RMS);
   }
   else {
      setDirection(FORWARD, LMS,RMS);
    }
   RMS = map(RMS , 0 , 360, 0, 255); 
   LMS = map(LMS , 0 , 360, 0, 255); 
  
}
void pid2(){
  Setpoint = 0;
  myPID2.Compute();
  if(Output>VELOCIDAD) Output=VELOCIDAD;
  if(Output<-VELOCIDAD) Output=-VELOCIDAD;
  double RMS = VELOCIDAD + Output;
  double LMS = VELOCIDAD - Output;

  if(RMS<0){
     RMS = map(RMS , 0 , -255, 0, 255);
     setDirection(RIGHT, LMS, RMS);
  }
  else if(LMS<0){
    LMS = map(LMS , 0 , -255, 0, 255);
    setDirection(LEFT, LMS,RMS);
   }
   else {
      setDirection(FORWARD, LMS,RMS);
    }
}
double difSensores(){
  return (analogRead(sensorI) - analogRead(sensorD)-100)*1.0;
}
void vueltaIzquierda(){
  posEncoderD=encoderD.read();
  posAntEncoderD=posEncoderD;
  int resta = posEncoderD - posAntEncoderD;
  while(resta<MEDIA){
    motorDerecho.setMotor(VELOCIDAD);
    motorIzquierdo.setMotor(0);
    posEncoderD=encoderD.read();
    resta = posEncoderD - posAntEncoderD;
  }
  setDirection(STOP,0,0);
}
void vueltaDerecha(){
  posEncoderI=encoderI.read();
  posAntEncoderI=posEncoderI;
  int resta = posEncoderI - posAntEncoderI;
  while(resta<MEDIA){
    motorIzquierdo.setMotor(VELOCIDAD);
    motorDerecho.setMotor(0);
    posEncoderI=encoderI.read();
    resta = posEncoderI - posAntEncoderI;
  }
  setDirection(STOP,0,0);
}
void avanzar(int cant){
  posEncoderI=encoderI.read();
  posAntEncoderI=posEncoderI;
  int resta = posEncoderI - posAntEncoderI;
  while(resta<cant){
    motorIzquierdo.setMotor(VELOCIDAD);
    motorDerecho.setMotor(VELOCIDAD);
    posEncoderI=encoderI.read();
    resta = posEncoderI - posAntEncoderI;
  }
  setDirection(STOP,0,0);
}
void retroceder(){
  posEncoderI=encoderI.read();
  posAntEncoderI=posEncoderI;
  int resta =posAntEncoderI- posEncoderI;
  while(resta<300){
    motorIzquierdo.setMotor(-VELOCIDAD);
    motorDerecho.setMotor(-VELOCIDAD);
    posEncoderI=encoderI.read();
    resta = posAntEncoderI- posEncoderI;
  }
  setDirection(STOP,0,0);
}
void vuelta180(){
    posEncoderI=encoderI.read();
    posAntEncoderI=posEncoderI;
    posEncoderD=encoderD.read();
    posAntEncoderD=posEncoderD;
    int resta1 = posEncoderI - posAntEncoderI;
    int resta2 = posAntEncoderD-posEncoderD;
    while(resta1<VUELTA180&&resta2<VUELTA180){
      motorIzquierdo.setMotor(VELOCIDAD);
      motorDerecho.setMotor(-VELOCIDAD);
      posEncoderI=encoderI.read();
      posEncoderD=encoderD.read();
      resta1 = posEncoderI - posAntEncoderI;
      resta2 = posAntEncoderD-posEncoderD;
  }
  setDirection(STOP,0,0);
}
void setDirection(int dir, int PWM1, int PWM2) {

  if ( dir == FORWARD ) {
    motorIzquierdo.setDireccion(0,PWM1);
    motorDerecho.setDireccion(0,PWM2);
  }
  else if ( dir == LEFT ) {
    motorIzquierdo.setDireccion(PWM1,0);
    motorDerecho.setDireccion(0,PWM2);
  }
  else if ( dir == RIGHT ) {
    motorIzquierdo.setDireccion(0,PWM1);
    motorDerecho.setDireccion(PWM2,0);
  }
  else if ( dir == STOP ) {
    motorIzquierdo.setDireccion(0,0);
    motorDerecho.setDireccion(0,0);
  }
  else if ( dir == BACKWARD ) {
    motorIzquierdo.setDireccion(PWM1,0);
    motorDerecho.setDireccion(0,PWM2);
  }
}
void Derecho(){
  if(estado<4){
    estado=+1;
  }
  else{
    estado=1;
  }
}

void Izquierdo(){
  if(estado>1){
    estado=-1;
  }
  else{
    estado=4;
  }
}

void vuelta180D(){
  estado=+2;
  if(estado>4){
    estado=-4;
  }
}
