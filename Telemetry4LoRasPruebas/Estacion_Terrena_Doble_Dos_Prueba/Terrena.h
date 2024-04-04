void Parametros() {

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 18, 19);
  Serial2.begin(115200, SERIAL_8N1, 17, 16);
  delay(1000);
  
  Serial1.println("AT+BAND=915000000"); // ancho de banda
  delay(500);
  Serial1.println("AT+ADDRESS=1"); // Estacion terrena
  delay(500);
  Serial1.println("AT+NETWORKID=11");
  delay(500);
  Serial1.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);

  Serial2.println("AT+BAND=868000000"); // ancho de banda
  delay(500);
  Serial2.println("AT+ADDRESS=2"); // Estacion terrena
  delay(500);
  Serial2.println("AT+NETWORKID=7");
  delay(500);
  Serial2.println("AT+PARAMETER=10,9,1,7"); // Justo para 3km
  delay(500);

}

void Lectura(){

  String in_values = "Serial1:\n"; // Cambiado a Serial1
  while(Serial1.available() > 0) {
    if(Serial1.available() > 0) {
      in_values += String(char(Serial1.read())); // Le añade los valores que se encuentren en dicho Serial
    }
  }

  in_values += "\nSerial2:\n"; // Cambiado a Serial2

  while(Serial2.available() > 0) { // Cambiado a Serial2
    if(Serial2.available() > 0) { // Cambiado a Serial2
      in_values += String(char(Serial2.read())); // Le añade los valores que se encuentren en dicho Serial
    }
  }

  Serial.println(in_values);
  delay(1000);

}