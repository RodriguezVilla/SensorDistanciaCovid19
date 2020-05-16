#include <NewPing.h>

const int EchoPin = 5;
const int TriggerPin = 6;
const int DistanciaMax = 200;

NewPing sonar(TriggerPin,EchoPin, DistanciaMax);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  Serial.print(sonar.ping_cm()); // obtener el valor en cm (0 = fuera de rango)
  Serial.println("cm");

}
