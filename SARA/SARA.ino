#include <Servo.h>
#include <stdio.h>

int serial_putchar(char c, FILE* f) {
  Serial.write(c);
  return 0;
}

// Sensores nos pinos A1,A2,A3,A6,A7
const int flexPins[5] = {A1,A2,A3,A6,A7};
// Servos nos pinos digitais 3,5,6,9,10
const int servoPins[5] = {3,5,6,9,10};
// Cria 5 objetos servo
Servo servos[5];

const int min[5] = {906,612,816,969,227};
const int max[5] = {693,467,548,810,188};
int min_ang[5] = {0, 30, 50, 50, 50};
int max_ang[5] = {140, 170, 180, 180, 180};
int flexValue [5] = {0, 0, 0, 0, 0};
int angle [5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);

  fdevopen(&serial_putchar, 0);


  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
  }

 printf("Iniciando leitura dos sensores...\n");
}

void loop() {
  for (int i = 0; i < 2; i++) {
    flexValue[i] = analogRead(flexPins[i]);
    angle[i] = map(flexValue[i], min[i], max[i], min_ang[i], max_ang[i]);
    angle[i] = constrain(angle[i], min_ang[i], max_ang[i]);
    } 
    
  for (int i = 2; i < 5; i++) {
    flexValue[i] = analogRead(flexPins[i]);
    angle[i] = map(flexValue[i], min[i], max[i], min_ang[i], max_ang[i]);
    angle[i] = constrain(angle[i], min_ang[i], max_ang[i]);
    angle[i] = 180 - angle[i];  // Inverte movimento
    }
 
 for (int i = 0; i < 5; i++) {
    servos[i].write(angle[0]);
    
    printf("Sensor A%d = %d | Ângulo enviado: %d ||| ", i + 1, analogRead(flexPins[i]), angle[i]);
 }
Serial.println();

    // Impressão detalhada
    // Serial.print("Sensor A");
    // Serial.print(flexPins[i] - A0);
    // Serial.print(" | Valor lido: ");
    // Serial.print(flexValue);
    // Serial.print(" | Ângulo enviado: ");
    // Serial.print(angle);
    // Serial.print(" | Servo: ");
    // Serial.println(i + 1);

  

  

  Serial.println(" -");
  delay(300);
}