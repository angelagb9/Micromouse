#include <Arduino.h>
#include "Sensores.h"

Sensores::Sensores(int _sD, int _sI, int _sED,int _sEI,int _sF){
    sD=_sD;
    sI=_sI;
    sED=_sED;
    sEI=_sEI;
    sF=_sF;
  }
int Sensores::getSensorFrente(){
  return analogRead(sF);
}
int Sensores::getSensorIzquierdo(){
  return analogRead(sI);
}
int Sensores::getSensorDerecho(){
  return analogRead(sD);
}
int Sensores::getSensorEsquinaIzquierda(){
  return analogRead(sEI);
}
int Sensores::getSensorEsquinaDerecha(){
  return analogRead(sED);
}
void Sensores::imprimirSensores(){
  Serial.print("Sensor Izquierdo: ");
  Serial.print(analogRead(sI));
  Serial.print(" Sensor Esquina Izquierda : ");
  Serial.print(analogRead(sEI));
  Serial.print(" Sensor Frente: ");
  Serial.print(analogRead(sF));
  Serial.print(" Sensor Esquina Derecha: ");
  Serial.print(analogRead(sED));
  Serial.print(" Sensor Derecho: ");
  Serial.println(analogRead(sD));
}
bool Sensores::paredFrente(){
    if (analogRead(sF)<1150) return false;
    else return true;
  }
bool Sensores::paredDerecha(){
    if (analogRead(sD)<10) return false;
    else return true;
  }
bool Sensores::paredIzquierda(){
  if (analogRead(sI)<10) return false;
    else return true;
}
