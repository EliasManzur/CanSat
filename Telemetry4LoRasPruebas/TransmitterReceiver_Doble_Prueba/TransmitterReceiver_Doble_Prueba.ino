const int RXD2 = 17;
const int TXD2 = 16;
//const int RXD2 = 16;
//const int TXD2 = 17;

#include "CargaSecundaria.h"

void setup(){
  Parametros_Carga_Secundaria();
}

void loop(){
  Lectura_Carga_Secundaria();
}


/*
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(500);

  Serial2.println("AT+BAND=868000000"); // ancho de banda
  delay(500);
  Serial2.println("AT+ADDRESS=4"); // Carga Primaria
  delay(500);
  Serial2.println("AT+NETWORKID=7");
  delay(500);
  Serial2.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);
}

void loop() {

  String OtraVar1 = String(float(random(1000))/7);
  String OtraVar2 = String(float(random(1000))/7);
  String OtraVar3 = String(float(random(1000))/7);
  String OtraVar4 = String(float(random(1000))/7);
  String OtraVar5 = String(float(random(1000))/7);
  String values1 = "VAR1:"+OtraVar1+",VAR2:"+OtraVar2+",VAR3:"+OtraVar3+",VAR4:"+OtraVar4+",VAR5:"+OtraVar5;
  
  String in_values = "";

  String envio = "AT+SEND=2," + String(values1.length()) + "," + values1;
  Serial2.println(envio);
  Serial.println(envio);
  delay(1000);
}
*/