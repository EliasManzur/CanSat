#include "esp32-hal-uart.h"
#include <SoftwareSerial.h>
// Librerías para definir parámetros de antenas LoRa

void Parametros_Estacion_Terrena(int RX, int TX, int frec, int address, int network, int RX2, int TX2, int frec2, int address2, int network2) {

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX, TX);
  Serial1.begin(115200, SERIAL_8N1, RX2, TX2);
  delay(1000);
  
  Serial1.println("AT+BAND=" + String(frec)); // ancho de banda
  delay(500);
  Serial1.println("AT+ADDRESS=" + String(address)); // Estacion terrena
  delay(500);
  Serial1.println("AT+NETWORKID=" + String(network));
  delay(500);
  Serial1.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);

  Serial1.println("AT+BAND=" + String(frec2)); // ancho de banda
  delay(500);
  Serial1.println("AT+ADDRESS=" + String(address2)); // Estacion terrena
  delay(500);
  Serial1.println("AT+NETWORKID=" + String(network2));
  delay(500);
  Serial1.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);

}

void Parametros_Cargas(int RX, int TX, int frec, int address, int network){
  Serial.begin(115200);
  while(!Serial) {delay(10);
  }
  Serial1.begin(115200, SERIAL_8N1, RX, TX);
  while(!Serial1) {delay(10); }

  Serial1.println("+BAND="+ String(frec)); // ancho de banda
  delay(500);
  Serial1.println("AT+ADDRESS=" + String(address)); 
  delay(500);
  Serial1.println("AT+NETWORKID="+ String(network));
  delay(500);
  Serial1.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);
}


// Aquí se envían los datos

void Lectura_Carga(int dir, String mensaje){
  String cadena = "AT+SEND="+ String(dir) + "," + String(mensaje.length()) + "," + mensaje;
  
  Serial1.println(cadena);
  Serial.println(cadena);
  delay(500);
}

// Aquí se reciben los datos
void Lectura_Estacion_Terrena(){
  String in_values = "Serial1:("; // Cambiado a Serial1
  while(Serial1.available() > 0) {
    if(Serial1.available() > 0) {
      in_values += String(char(Serial1.read())); // Le añade los valores que se encuentren en dicho Serial
    }
  }

  in_values += ")Serial2:("; // Cambiado a Serial2

  while(Serial2.available() > 0) { // Cambiado a Serial2
    if(Serial2.available() > 0) { // Cambiado a Serial2
      in_values += String(char(Serial2.read())); // Le añade los valores que se encuentren en dicho Serial
    }
  }
  in_values += ")";
  Serial.println(in_values);
  delay(1000);
}