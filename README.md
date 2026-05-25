# Actividad3
[Proyecto Wokwi](https://wokwi.com/projects/464805599220546561)

## Cambios realizados

## Bill of Materials *(BOM)*

| Designator | Componente | Cantidad | Función |
|---|---|---|---|
| U1 | Arduino UNO R3 | 1 | Control principal del sistema |
| U2 | LCD I2C 16x2 | 1 | Interfaz visual del ascensor |
| U3 | Sensor DHT22 | 1 | Medición de temperatura y humedad |
| U4 | RTC DS1307 | 1 | Gestión de fecha y hora |
| U5 | Sensor PIR | 1 | Detección de presencia |
| U6 | LDR | 1 | Detección de iluminación ambiental |
| U7 | Servo Motor SG90 | 1 | Simulación movimiento del ascensor |
| RV1 | Potenciómetro | 1 | Ajuste del setpoint de temperatura |
| SW1 | Pulsador Planta 1 | 1 | Llamada ascensor planta 1 |
| SW2 | Pulsador Planta 2 | 1 | Llamada ascensor planta 2 |
| SW3 | Pulsador Planta 3 | 1 | Llamada ascensor planta 3 |
| SW4 | Pulsador Planta 4 | 1 | Llamada ascensor planta 4 |
| SW5 | Pulsador Planta 5 | 1 | Llamada ascensor planta 5 |
| LED1 | LED rojo | 1 | Indicador calefacción |
| LED2 | LED azul | 1 | Indicador refrigeración |
| LED3 | LED amarillo | 1 | Indicador iluminación |
| LED4 | LED verde | 1 | Indicador humedad |
| R1-R4 | Resistencias 220Ω | 4 | Limitación de corriente LEDs |
| R5 | Resistencia LDR 10kΩ | 1 | Divisor de tensión LDR |
| J1 | Bus I2C | 1 | Comunicación LCD y RTC |
| MEM1 | EEPROM interna Arduino | 1 | Persistencia de configuración |

### **Características principales**

- Alimentación: 5V
- Plataforma: Arduino UNO
- Comunicación I2C
- Sensores ambientales integrados
- Control mediante interrupciones
- Persistencia EEPROM
