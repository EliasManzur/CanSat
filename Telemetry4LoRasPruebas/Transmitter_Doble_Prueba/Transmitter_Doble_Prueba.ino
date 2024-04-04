// CARGA PRIMARIA

#include "Cargas.h"
#include "Sensores_Carga_Primaria.h"

#define RX 10
#define TX 9

#define gps_RX 27
#define gps_TX 25

extern SoftwareSerial ss(gps_RX, gps_TX);
static const uint32_t GPSBaud = 9600;

void setup() {
  ss.begin(GPSBaud);
  Parametros_Cargas(RX, TX, 915000000, 3, 11); // Carga Primaria
  Sensores();
  Servo_Setup(32);
}

void loop() {
  GPS();
  Valores_Sensores();
  Recopilar_Datos();
  Lectura_Carga(1,mensaje);
 // Servo_Desacople();
  SerialDisplay();
  delay(500);
}