/*código utilizado para obter as leituras dos sensores, nas posições de mão fechada e mão aberta, 
e realizar a calibração automática para que as informações sejam enviadas aos motores.*/
#include <Servo.h>

const int pinosServos[5] = {3,5,6,9,10};
Servo servos[5];

const int pinosSensores[5] = {A0, A1, A2, A3, A4};
char dedos[5][10] = {"Polegar", "Indicador", "Médio", "Anelar","Mínimo"};

int valoresMaxLeitura[5] = {0,0,0,0,0};
int valoresMinLeitura[5] = {0,0,0,0,0};
int valorAtual[5] = {0,0,0,0,0};
int angulo[5] = {0,0,0,0,0};

#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  for (int i = 0; i < 5; i++) {
    servos[i].attach(pinosServos[i]);
  }
    
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  
  calibracao();
}

void loop() {
  valorAtual[0] = analogRead(pinosSensores[0]);
  angulo[0] = map(valorAtual[0], valoresMinLeitura[0], valoresMaxLeitura[0], 0, 180);
  angulo[0] = constrain(angulo[0], 0, 180);
  servos[0].write(angulo[0]);
}

void calibracao(){
  //Aviso de inicialização
  lcd_1.setCursor(0,0);lcd_1.print("Iniciando");lcd_1.setCursor(0,1);lcd_1.print("calibracao");
  delay(1000);
  
  lcd_1.clear();  
  
  //Aviso para manter a mão fechada + contagem regressiva (5-0)e atribuição dos valores
  lcd_1.setCursor(0,0);lcd_1.print("Mantenha a");lcd_1.setCursor(0,1);lcd_1.print(" mao fechada");
  delay(1000);
  
  for(int i = 5; i > 0; i--){
    lcd_1.setCursor(14,0); lcd_1.print(i); delay(1000);
    
    for (int j = 0; j < 5; j++){
      valoresMaxLeitura[j] += analogRead(pinosSensores[j]); 
    }
  }
  // Calcula média
  for (int j = 0; j < 5; j++){
    valoresMaxLeitura[j] /= 5;}
 
  
  lcd_1.clear();  
  delay(500);
  
  //Aviso para manter a mão aberta + contagem regressiva (5-0)e atribuição dos valores
  lcd_1.setCursor(0,0);lcd_1.print("Mantenha a");lcd_1.setCursor(0,1);lcd_1.print(" mao aberta");
  delay(1000);
  
  for(int i = 5; i > 0; i--){
    lcd_1.setCursor(14,0); lcd_1.print(i); delay(1000);
    for (int j = 0; j < 5; j++){
      valoresMinLeitura[j] += analogRead(pinosSensores[j]);  
    }
  // Calcula média
  for (int j = 0; j < 5; j++){
    valoresMinLeitura[j] /= 5;}
  }
  
  delay(500);
  lcd_1.clear(); 
  lcd_1.setCursor(0,0);lcd_1.print("Calibracao");lcd_1.setCursor(0,1);lcd_1.print("realizada"); 
}
