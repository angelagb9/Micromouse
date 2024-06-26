#ifndef Motor_h
#define Motor_h

#if ARDUINO > 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Motor{
      private:
        int IN1; //Motor 1
        int IN2; //Motor 2
        int canalA; //Canal para el pwm del pin 1
        int canalB; // Canal para el pwm del pin 2
        int resolucion=8; //resolucion de la señal pwm
        int frecuencia=5000; //frecuencia de la señal pwm

      public:
        Motor(int _IN1, int _IN2, int _canalA,int _canalB); //inicializar los pines
        void setDireccion(int PWMA,int PWMB); //establece los valores en base a dos valores
        void setMotor(int PWM); //establece los valores en base a un valor
  };

#endif
