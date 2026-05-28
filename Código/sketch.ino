// LIBRERIAS

#include <Wire.h> //Comunicación I2C
#include <LiquidCrystal_I2C.h> //Pantalla LCD
#include <DHT.h>//Sensor DHT22
#include <Servo.h> //Control servo
#include <PinChangeInterrupt.h>//Gestión de inerrupciones
#include <RTClib.h> //Reloj RTC
#include <EEPROM.h>

//CONFIG SENSOR DHT22
#define DHT_PIN 2 //Pin datos sensor
#define DHT_TYPE DHT22 //tipo de sensor

// CREACIÓN OBJETOS SENSORES Y ACTUADORES
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo miServo;
RTC_DS1307 rtc;

// PINES
int LDR_PIN = A0;
int PIR = 8;


// Pines pulsadores plantas(Botones)
int botonP1 = 3;
int botonP2 = 4;
int botonP3 = 5;
int botonP4 = 6;
int botonP5 = 7;


// LEDs indicadores
int ledCalor = 10;
int ledFrio = 11;
int ledLuz = 12;
int ledHumedad = 13;


// VARIABLES
int plantaActual = 1;//Inicializamos planta actual
bool frioActivo = false;//Control climatizacion
bool calorActivo = false;//Control climatizacion
bool luzActiva = false;
bool humedadActiva =false;
float setpointTemp = 25.0;



// INTERRUPCIONES
volatile bool llamadaP1 = false;
volatile bool llamadaP2 = false;
volatile bool llamadaP3 = false;
volatile bool llamadaP4 = false;
volatile bool llamadaP5 = false;


// DECLARACIÓN FUNCIONES
void leerSensores(float &temp, float &hum, int &luz, int &presencia);
void gestionarAscensor();
void controlTemperatura(float temp);
void controlIluminacion(int luz);
void actualizarLCD(float temp, int presencia);
void logSerialCSV(float temp, float hum, int luz, int presencia);
void configurarInterrupciones();
void configurarPines();
void controlHumedad(float hum);



// ISR
void irPlanta1();
void irPlanta2();
void irPlanta3();
void irPlanta4();
void irPlanta5();

const int pinPot = A1;


void setup() {
//Inicialización comunicación serie

  Serial.begin(9600);
  //Config e inicialización  Servo
  miServo.attach(9);
  miServo.write(0);
 // Inicialización  pantalla LCD

  lcd.init();
  lcd.backlight();

  //Inicialización del reloj RTC
  if (!rtc.begin()) {
    Serial.println("RTC no encontrado");
  }

  // Ajuste automático de fecha y hora (reinicio del RTC)
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
  pinMode(pinPot, INPUT);
    
  dht.begin();//Inicialización DHT
  configurarPines(); //Config pines
  configurarInterrupciones(); //Config interrupciones
  EEPROM.get(0, setpointTemp);
 

  // validaciones
if (setpointTemp < 10 || setpointTemp > 35) setpointTemp = 25;


  // Cabecera CSV
  Serial.println("fecha,hora,planta,temperatura,setPoint,AC,calefaccion,humedad,deshumidificacion,valorLuz,iluminacion,presencia");

}

//Bucle principal
void loop() {
   //Declaramos variables
  float temp;
  float hum;
  int luz;
  int presencia;
  static float setpointAnterior = -1;
  

int pot = analogRead(pinPot);
float nuevoSetpoint = map(pot, 0, 1023, 18, 30);

nuevoSetpoint = round(nuevoSetpoint);


if (nuevoSetpoint != setpointTemp) {
  setpointTemp = nuevoSetpoint;
}

  //Llamadas a las funciones pertinentes
  leerSensores(temp, hum, luz, presencia); //leemos sensores
  gestionarAscensor();//gestión ascensor
   if (setpointTemp != setpointAnterior) {
    EEPROM.put(0, setpointTemp);
    setpointAnterior = setpointTemp;
  }

  controlTemperatura(temp);//Control climatización
  controlHumedad(hum);//Control humedad
  controlIluminacion(luz);//Control iluminación
  actualizarLCD(temp, presencia);//Actualización pantalla lcd
  logSerialCSV(temp, hum, luz,presencia); //Datos puero serie
  delay(1000);

}

//Funciones del sistema

//Config entradas y salidas
void configurarPines() {

  pinMode(PIR, INPUT);

  pinMode(botonP1, INPUT_PULLUP);
  pinMode(botonP2, INPUT_PULLUP);
  pinMode(botonP3, INPUT_PULLUP);
  pinMode(botonP4, INPUT_PULLUP);
  pinMode(botonP5, INPUT_PULLUP);


  pinMode(ledCalor, OUTPUT);
  pinMode(ledFrio, OUTPUT);
  pinMode(ledLuz, OUTPUT);
  pinMode(ledHumedad, OUTPUT);

}

//Gestión interrupciones.(Simulación llamadas a plantas)

void configurarInterrupciones() {

  attachPCINT(
    digitalPinToPCINT(botonP1),
    irPlanta1,
    FALLING
  );

  attachPCINT(
    digitalPinToPCINT(botonP2),
    irPlanta2,
    FALLING
  );

  attachPCINT(
    digitalPinToPCINT(botonP3),
    irPlanta3,
    FALLING
  );

  attachPCINT(
    digitalPinToPCINT(botonP4),
    irPlanta4,
    FALLING
  );


  attachPCINT(
    digitalPinToPCINT(botonP5),
    irPlanta5,
    FALLING
  );

}

//Lectura sensores ambientales y presencia
void leerSensores(float &temp, float &hum, int &luz, int &presencia) {
  
  temp = dht.readTemperature();//Leer temperatura
  hum = dht.readHumidity();//Leer nivel humedad
  luz = analogRead(LDR_PIN);//Leer nivel de luz
  presencia = digitalRead(PIR); //Leer sensor PIR

}


//Gestión movimiento ascensor
void gestionarAscensor() {


  if (llamadaP1) {
    miServo.write(0);
    delay(300);
    plantaActual = 1;
    llamadaP1 = false;
  }

  if (llamadaP2) {
    miServo.write(45);
    delay(300);
    plantaActual = 2;
    llamadaP2 = false;

  }

  if (llamadaP3) {
    miServo.write(90);
    delay(300);
    plantaActual = 3;
    llamadaP3 = false;

  }

  if (llamadaP4) {
    miServo.write(135);
    delay(300);
    plantaActual = 4;
    llamadaP4 = false;
  }

  if (llamadaP5) {
    miServo.write(180);
    delay(300);
    plantaActual = 5;
    llamadaP5 = false;

  }

}

//Gestión temperatura(leds rojo y azul)

void controlTemperatura(float temp) {

// FRÍO
if (frioActivo) {
  if (temp <= setpointTemp) {
    frioActivo = false;
  }
} else {
  if (temp >= setpointTemp + 1.5) {
    frioActivo = true;
  }
}

// CALOR
if (calorActivo) {
  if (temp >= setpointTemp) {
    calorActivo = false;
  }
} else {
  if (temp <= setpointTemp - 2) {
    calorActivo = true;
  }
}

  // evitar ambos activos
  if (frioActivo) {
    calorActivo = false;
  }
  if (calorActivo) {
    frioActivo = false;
  }

  digitalWrite(ledFrio, frioActivo);
  digitalWrite(ledCalor, calorActivo);
}


//Gestión iluminacion
void controlIluminacion(int luz) {
 
   // SENSOR INVERTIDO:
  // valor alto = oscuridad
  // valor bajo = claridad

  // Encender iluminación
  if (luz > 525 && !luzActiva) {
    luzActiva = true;
    digitalWrite(ledLuz, HIGH);
   
  }

  // Apagar iluminación
  else if (luz < 475 && luzActiva) {
    luzActiva = false;
    digitalWrite(ledLuz, LOW);

  }

}

void actualizarLCD(float temp, int presencia) {

  static int plantaAnterior = -1;
  static int presenciaAnterior = -1;
  static float setpointAnterior = -1;

  if (plantaActual != plantaAnterior || 
      presencia != presenciaAnterior || 
      setpointTemp != setpointAnterior) {

    //  Línea 1
    lcd.setCursor(0, 0);
    lcd.print("P:");
    lcd.print(plantaActual);
    lcd.print(" SetP:");
    lcd.print(setpointTemp);
    lcd.print("   ");

    //  Línea 2
    lcd.setCursor(0, 1);
    lcd.print("Pres:");
    lcd.print(presencia ? "SI" : "NO");
    lcd.print("   ");

    plantaAnterior = plantaActual;
    presenciaAnterior = presencia;
    setpointAnterior = setpointTemp;
  }
}



// log
void logSerialCSV(float temp, float hum, int luz, int presencia) {

  DateTime now = rtc.now();
  Serial.print(now.year());
  Serial.print("-");
  Serial.print(now.month());
  Serial.print("-");
  Serial.print(now.day());
  Serial.print(",");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(",");
  Serial.print(plantaActual);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(setpointTemp); 
  Serial.print(",");
  Serial.print(frioActivo ? "SI" : "NO");
  Serial.print(",");
  Serial.print(calorActivo ? "SI" : "NO");
  Serial.print(",");
  Serial.print(hum);
  Serial.print(",");
  Serial.print(humedadActiva ? "SI" : "NO");
  Serial.print(",");
  Serial.print(luz);
  Serial.print(",");
  Serial.print(luzActiva ? "SI" : "NO");
  Serial.print(",");
  Serial.println(presencia ? "SI" : "NO");
 
 
}


void controlHumedad(float hum){
  // mantener activo
   if(humedadActiva){
      // desactivar humedad alta
      if(hum < 70){
         humedadActiva = false;
      }
   }
   else{
      // activar humedad alta
      if(hum > 80){
         humedadActiva = true;
      }
   }
   digitalWrite(ledHumedad, humedadActiva);
}


// ISR
void irPlanta1() {
  llamadaP1 = true;
}
void irPlanta2() {
  llamadaP2 = true;
}
void irPlanta3() {
  llamadaP3 = true;
}
void irPlanta4() {
  llamadaP4 = true;
}
void irPlanta5() {
  llamadaP5 = true;
}
