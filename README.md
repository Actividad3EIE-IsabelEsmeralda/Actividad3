# Actividad3
[Proyecto Wokwi](https://wokwi.com/projects/464805599220546561)

## Cambios realizados


## Arquitectura hardware

Imágenes/Circuito.png

El sistema está basado en un Arduino UNO como controlador principal, integrando sensores ambientales, módulos de comunicación I2C, actuadores y sistemas de señalización.

### **Conexiones**

| Componente | Pin Arduino |
|---|---|
| DHT22 | D2 |
| Servo Motor | D9 |
| PIR | D8 |
| LED calefacción | D10 |
| LED refrigeración | D11 |
| LED iluminación | D12 |
| LED humedad | D13 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| RTC SDA | A4 |
| RTC SCL | A5 |

## Bill of Materials *(BOM)*

| Designator | Componente | Part Number | Cantidad | Proveedor | Función |
|---|---|---|---|---|---|
| U1 | Arduino UNO R3 | A000066 | 1 | Arduino / Wokwi | Control principal del sistema |
| U2 | LCD I2C 16x2 | LCD1602-I2C | 1 | AZDelivery / Wokwi | Interfaz visual del ascensor |
| U3 | Sensor DHT22 | AM2302 | 1 | Adafruit / Wokwi | Medición de temperatura y humedad |
| U4 | RTC DS1307 | DS1307 RTC | 1 | Maxim Integrated / Wokwi | Gestión de fecha y hora |
| U5 | Sensor PIR | HC-SR501 | 1 | HC / Wokwi | Detección de presencia |
| U6 | LDR | GL5528 | 1 | Generic / Wokwi | Detección de iluminación ambiental |
| U7 | Servo Motor SG90 | SG90 | 1 | TowerPro / Wokwi | Movimiento simulado del ascensor |
| RV1 | Potenciómetro | WH148 B10K | 1 | Generic / Wokwi | Ajuste del setpoint de temperatura |
| SW1 | Pulsador Planta 1 | PBS-110 | 1 | Generic / Wokwi | Llamada ascensor planta 1 |
| SW2 | Pulsador Planta 2 | PBS-110 | 1 | Generic / Wokwi | Llamada ascensor planta 2 |
| SW3 | Pulsador Planta 3 | PBS-110 | 1 | Generic / Wokwi | Llamada ascensor planta 3 |
| SW4 | Pulsador Planta 4 | PBS-110 | 1 | Generic / Wokwi | Llamada ascensor planta 4 |
| SW5 | Pulsador Planta 5 | PBS-110 | 1 | Generic / Wokwi | Llamada ascensor planta 5 |
| LED1 | LED rojo | 5mm Red LED | 1 | Generic / Wokwi | Indicador calefacción |
| LED2 | LED azul | 5mm Blue LED | 1 | Generic / Wokwi | Indicador refrigeración |
| LED3 | LED amarillo | 5mm Yellow LED | 1 | Generic / Wokwi | Indicador iluminación |
| LED4 | LED verde | 5mm Green LED | 1 | Generic / Wokwi | Indicador humedad |
| R1-R4 | Resistencias 220Ω | CFR-220R | 4 | Generic / Wokwi | Limitación de corriente LEDs |
| R5 | Resistencia 10kΩ | CFR-10K | 1 | Generic / Wokwi | Divisor de tensión LDR |
| J1 | Bus I2C | I2C Bus | 1 | Integrado | Comunicación LCD y RTC |
| MEM1 | EEPROM interna Arduino | ATmega328P EEPROM | 1 | Integrado | Persistencia de configuración |

### **Características principales**

- Alimentación: 5V
- Plataforma: Arduino UNO
- Comunicación I2C
- Sensores ambientales integrados
- Control mediante interrupciones
- Persistencia EEPROM

## **Diagrama de flujo**

```text
┌───────────────────────┐
│       INICIO          │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Inicialización sistema│
│ - Serial              │
│ - LCD                 │
│ - RTC                 │
│ - DHT22               │
│ - Servo               │
│ - Pines               │
│ - Interrupciones      │
│ - EEPROM              │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Lectura sensores      │
│ - Temperatura         │
│ - Humedad             │
│ - LDR                 │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Gestión ascensor      │
│ ¿Botón pulsado?       │
└──────────┬────────────┘
           │ SI
           ▼
┌───────────────────────┐
│ Mover servo a planta  │
│ correspondiente       │
│ Actualizar planta     │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Guardar configuración │
│ en EEPROM             │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Control temperatura   │
│ - Activar frío        │
│ - Activar calor       │
│ - Histéresis          │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Control humedad       │
│ - Activar LED humedad │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Control iluminación   │
│ mediante LDR          │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Actualizar LCD        │
│ - Planta actual       │
│ - Presencia           │
│ - Setpoint            │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│ Registro monitor serie│
│ CSV + RTC             │
└──────────┬────────────┘
           │
           ▼
┌───────────────────────┐
│       LOOP            │
└───────────────────────┘
