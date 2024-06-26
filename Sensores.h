#ifndef Sensores_h
#define Sensores_h

#if ARDUINO > 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Sensores{
      private:
        int sD;
        int sI;
        int sED;
        int sEI;
        int sF;

      public:
        Sensores(int _sD, int _sI, int _sED,int _sEI,int _sF);
        int getSensorFrente();
        int getSensorIzquierdo();
        int getSensorDerecho();
        int getSensorEsquinaIzquierda();
        int getSensorEsquinaDerecha();
        void imprimirSensores();
        bool paredFrente();
        bool paredDerecha();
        bool paredIzquierda();  
  };

#endif
