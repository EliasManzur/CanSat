

/*
    En este header file se declaran y definen las funciones referentes a la telemetría
    Asi como la construcción de los objetos de cada sensor y estructura de datos
    Se empleo una estructura de datos para guardar los datos de telemetría
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <TinyGPSPlus.h>
#include "esp32-hal-uart.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP32Servo.h>



struct Telemetria {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float tin;
  float lat;
  float lon;
  float temp;
  float pres;
  float altit;
  float hum;
  int hora;
  int minu;
  int sec;
  int servo_posicion;
};

String mensaje;
Adafruit_MPU6050 mpu; 
Adafruit_BME280 bme;
TinyGPSPlus gps;
Telemetria datos;
Servo myServo;

extern SoftwareSerial ss;

void Sensores(){
  ///////////////////BME//////////////////////
  #define SEALEVELPRESSURE_HPA (1013.25)
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        while (1) delay(10);
    }

  ///////////////////MPU//////////////////////
  // Inicializar el sensor MPU6050
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
    }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
    }
}

void Servo_Setup(int pin){
  myServo.attach(pin);
  datos.servo_posicion = 0;
  myServo.write(0);    // Mueve el servo a la posición 0 grados
  
}

/*void Servo_Desacople(){
  
  if (datos.servo_posicion == 0 && tiempo >= 5000){
    datos.servo_posicion = 90;
    myServo.write(datos.servo_posicion);
  }
  
}
*/

void displayInfo_GPS() {
  if(gps.location.isValid()) {
    datos.lat = gps.location.lat();
    datos.lon = gps.location.lng();
  }
  if (gps.time.isValid()) {
    datos.hora = gps.time.hour();
    datos.minu = gps.time.minute(); 
    datos.sec = gps.time.second();
  }
}

void GPS(){
  while(ss.available() > 0) {
    if(gps.encode(ss.read())){
      displayInfo_GPS();
    }
  }
}


void Sensor_MPU() {
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  datos.ax = a.acceleration.x;
  datos.ay = a.acceleration.y;
  datos.az = a.acceleration.z;

  datos.gx = g.gyro.x;
  datos.gy = g.gyro.y;
  datos.gz = g.gyro.z;

  datos.tin = temp.temperature;
}

void Sensor_BME(){
  datos.temp = bme.readTemperature();
  datos.pres = bme.readPressure() / 100.0F;
  datos.altit = bme.readAltitude(SEALEVELPRESSURE_HPA);
  datos.hum = bme.readHumidity();
}

void Valores_Sensores(){
  Sensor_MPU();
  Sensor_BME();
}

void SerialDisplay(){
  Serial.println("------------------------------------------------------------------------------");

  Serial.println("Temperatura Int: " + String(datos.tin) );

  Serial.print("Aceleración (x, y, z): ");
  Serial.print(datos.ax);
  Serial.print(", ");
  Serial.print(datos.ay);
  Serial.print(", ");
  Serial.println(datos.az);

  Serial.print("Giroscopio (x, y, z): ");
  Serial.print(datos.gx);
  Serial.print(", ");
  Serial.print(datos.gy);
  Serial.print(", ");
  Serial.println(datos.gz);

  Serial.print("GPS (lat, lng): ");
  Serial.print(datos.lat);
  Serial.print(", ");
  Serial.println(datos.lon);

  Serial.print("HORA: ");
  Serial.print(datos.hora);
  Serial.print(", ");
  Serial.print(datos.minu);
  Serial.print(", ");
  Serial.println(datos.sec);

  Serial.print("TEMP: ");
  Serial.print(datos.temp);
  Serial.println(" °C");

  Serial.print("PRES: ");
  Serial.print(datos.pres);
  Serial.println(" hPa");

  Serial.print("ALT: ");
  Serial.print(datos.altit);
  Serial.println(" m");

  Serial.print("HUM: ");
  Serial.print(datos.hum);
  Serial.println(" %");

    
  Serial.print("SERVO: ");
  Serial.println(datos.servo_posicion);
}

void Recopilar_Datos(){
  mensaje = "";
  // Realiza lo mismo para cada variable, por ejemplo:
  mensaje += "TEMP_INT:" + String(datos.tin) + ",";
  mensaje += "HUM:" + String(datos.tin) + ",";
  mensaje += "Ax:" + String(datos.ax) + ",";
  mensaje += "Ay:" + String(datos.ay) + ",";
  mensaje += "Az:" + String(datos.az) + ",";
  mensaje += "Gx:" + String(datos.gx) + ",";
  mensaje += "Gy:" + String(datos.gy) + ",";
  mensaje += "Gz:" + String(datos.gz) + ",";
  mensaje += "LAT:" + String(datos.lat) + ",";
  mensaje += "LON:" + String(datos.lon) + ",";
  mensaje += "HR:" + String(datos.hora) + ",";
  mensaje += "MIN:" + String(datos.minu) + ",";
  mensaje += "SEC:" + String(datos.sec) + ",";
  mensaje += "TEMP:" + String(datos.temp) + ",";
  mensaje += "PRES:" + String(datos.pres) + ",";
  mensaje += "HUM:" + String(datos.hum) + ",";
  mensaje += "ALT:" + String(datos.altit) + ",";
}


