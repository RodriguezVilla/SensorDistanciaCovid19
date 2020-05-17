#include <Adafruit_NeoPixel.h>

/////////////////////////////////////
// Rubén R. V.
// 17/05/2020
// Sensor distancia Seguridad Covid 18. v1.0.0

// Repositorio:
//  - https://github.com/RodriguezVilla/SensorDistanciaCovid19
//
// Funciones:
//  -Indica cuando haya un obstaculo a menos de 2m
//
// Hardware:
//  * 1 Arduino nano.
//  * 1 sensor distancia HR-SR04.
//  * 1 100 Ohmios.
//  * 1 modulo altavoz.
//  * 1 Resistencia 330Ohmios.
//  * 1 tira led WS82-12.
//
//////////////////////////////////////

const int ledsPin = 3;
const int numLeds = 3; 
const int BuzzerPin = 4;
const int EchoPin = 5;
const int TriggerPin = 6;

int distancia_cm=0;

Adafruit_NeoPixel ledsDistSeguridad = Adafruit_NeoPixel(numLeds, ledsPin, NEO_GRB + NEO_KHZ800);

uint32_t offDistSeguridad =  ledsDistSeguridad.Color(0,0,0);
uint32_t rojoDistSeguridad =  ledsDistSeguridad.Color(130,0,0);

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  distancia_cm = ping(TriggerPin, EchoPin);
  delay(50);
  if(distancia_cm <200 && distancia_cm >0){
    Serial.print(distancia_cm ); 
    Serial.println("cm");
    
    for(int i=0; i<numLeds; i++){
      ledsDistSeguridad.setPixelColor(i, rojoDistSeguridad);
      ledsDistSeguridad.show();
    }
    
    tone(BuzzerPin,200,1000);

  }else{
    Serial.println("Distancia de seguridad");
    Serial.print(distancia_cm ); 
    Serial.println("cm");
        
    for(int i=0; i<numLeds; i++){
      ledsDistSeguridad.setPixelColor(i, offDistSeguridad);
      ledsDistSeguridad.show();
    }
  }

}

//------------------------------------------------
// Función: Vista en ->  https://www.luisllamas.es/medir-distancia-con-arduino-y-sensor-de-ultrasonidos-hc-sr04/
//-----------------------------------------------------
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}
