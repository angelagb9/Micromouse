#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int _IN1, int _IN2, int _canalA,int _canalB)
{
  canalA=_canalA;
  canalB=_canalB;
  IN1=_IN1;
  IN2=_IN2;
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  ledcSetup(canalA, frecuencia, resolucion);
  ledcAttachPin(IN1, canalA);
  ledcSetup(canalB, frecuencia, resolucion);
  ledcAttachPin(IN2, canalB);
}
void Motor::setDireccion(int PWMA, int PWMB){
  ledcWrite(canalA,PWMA);
  ledcWrite(canalB,PWMB);
}
void Motor::setMotor(int PWM){
  if(PWM>0){
      setDireccion(0,PWM);
    }
   else if(PWM<0){
    setDireccion(PWM,0);
   }
   else{
      setDireccion(0,0);
    }
  
 }
