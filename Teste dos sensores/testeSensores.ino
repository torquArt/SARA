//código utilizado para verificar o funcionamento dos sensores e seus respectivos valores de leitura analógica

char dedos[5][10] = {"polegar", "indicador", "medio", "anelar","minimo"};
int pinosSensores[5] = {A0, A1, A2, A3, A4};

void setup() {
Serial.begin(9600);
}

void loop() {
for (int i = 0; i < 5; i++){
Serial.print(dedos[i]); Serial.print(" "); Serial.print(analogRead(pinosSensores[i])); Serial.print(" // "); //Imprime no monitor serial o dedo que está sendo verificado seguido por sua respectiva leitura analógica.
}
Serial.println();
}
