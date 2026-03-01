#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP32Servo.h>

// ===== I2C OLED =====
#define SDA_PIN 5
#define SCL_PIN 6

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// ===== SERVOS =====
const int pinosServos[5] = {3, 4, 7, 8, 9};   // Ajuste conforme seu ESP32
Servo servos[5];

// ===== SENSORES =====
const int pinosSensores[5] = {0, 1, 2, 3, 4}; // GPIOs ADC do ESP32
int valoresMaxLeitura[5] = {0,0,0,0,0};
int valoresMinLeitura[5] = {0,0,0,0,0};
int valorAtual[5];
int angulo[5];

void calibracao();

void setup() {
  Serial.begin(115200);

  // Inicia I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();

  // Configura servos
  for (int i = 0; i < 5; i++) {
    servos[i].attach(pinosServos[i], 500, 2400); 
  }

  calibracao();
}

void loop() {

  for(int i = 0; i < 5; i++){
    valorAtual[i] = analogRead(pinosSensores[i]);

    angulo[i] = map(valorAtual[i],
                    valoresMinLeitura[i],
                    valoresMaxLeitura[i],
                    0, 180);

    angulo[i] = constrain(angulo[i], 0, 180);
    servos[i].write(angulo[i]);
  }

  delay(20);
}

void calibracao(){

  // ===== INICIO =====
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0,12,"Iniciando");
  u8g2.drawStr(0,24,"calibracao");
  u8g2.sendBuffer();
  delay(2000);

  // ===== MAO FECHADA =====
  u8g2.clearBuffer();
  u8g2.drawStr(0,12,"Feche a mao");

  u8g2.sendBuffer();
  delay(2000);

  for(int i = 5; i > 0; i--){
    u8g2.clearBuffer();
    
    u8g2.drawStr(0,12,"Mantenha a");
    u8g2.drawStr(0,24,"mao fechada");

    char contador[2];
    sprintf(contador, "%d", i);
    u8g2.drawStr(30,36,contador);

    u8g2.sendBuffer();
    delay(1000);

    for (int j = 0; j < 5; j++){
      valoresMaxLeitura[j] += analogRead(pinosSensores[j]);
    }
  }

  for (int j = 0; j < 5; j++){
    valoresMaxLeitura[j] /= 5;
  }

  // ===== MAO ABERTA =====
  u8g2.clearBuffer();
  u8g2.drawStr(0,12,"Abra a mao");

  u8g2.sendBuffer();
  delay(2000);

  for(int i = 5; i > 0; i--){
    u8g2.clearBuffer();
    u8g2.drawStr(0,12,"Mantenha a");
    u8g2.drawStr(0,24,"mao aberta");

    char contador[2];
    sprintf(contador, "%d", i);
    u8g2.drawStr(30,36,contador);

    u8g2.sendBuffer();
    delay(1000);

    for (int j = 0; j < 5; j++){
      valoresMinLeitura[j] += analogRead(pinosSensores[j]);
    }
  }

  for (int j = 0; j < 5; j++){
    valoresMinLeitura[j] /= 5;
  }

  // ===== FINAL =====
  u8g2.clearBuffer();
  u8g2.drawStr(0,12,"Calibracao");
  u8g2.drawStr(0,24,"concluida");
  u8g2.sendBuffer();
  delay(2000);
}
