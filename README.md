# Actividad3
## Introducción

En la actualidad, los sistemas de control ambiental juegan un papel fundamental en la automatización de edificios inteligentes, permitiendo mejorar la eficiencia energética y el confort de los usuarios. Estos sistemas integran sensores, actuadores y unidades de control para monitorizar y regular distintas variables del entorno.

En la práctica 3 se se mejora la simulación de un ascensor basado en Arduino. Se integran diferentes elementos hardware y lógicas de control en una única solución. Está orientado a la monitorización y control de variables ambientales como la temperatura, la humedad, la iluminación y la presencia.

El sistema ha sido diseñado siguiendo una arquitectura modular, donde cada subsistema (sensores, control, visualización y actuación) cumple una función específica. A partir de una implementación inicial, se han introducido mejoras orientadas a aumentar la interactividad, la estabilidad y el realismo del sistema.

Entre estas mejoras destaca la incorporación de un control dinámico del setpoint de temperatura mediante un potenciómetro, la modificación de la histéresis para estabilizar el comportamiento del sistema de temperatura, y el uso de memoria EEPROM para mantener la configuración tras reinicios de la simulación.

El resultado de estas mejoras es un sistema más flexible, robusto e interactivo. Reproduce de forma simplificada el funcionamiento de un sistema real de control ambiental.

[Proyecto Wokwi Práctica 3](https://wokwi.com/projects/464805599220546561)

## Cambios realizados
En la práctica 2 (https://wokwi.com/projects/463563467769274369)que se ha usado como base, se implementó un sistema básico de control ambiental con lectura de sensores, control de actuadores y visualización en LCD, sin posibilidad de modificar parámetros ni almacenar información. En la práctica 3 (https://wokwi.com/projects/464805599220546561 se han introducido mejoras:

- Se ha añadido un potenciómetro para modificar el setpoint de temperatura en tiempo real. El sistema de climatización pasa a depender no solo de la temperatura medida por el sensor, sino también del valor de consigna (setpoint) definido por el usuario. La función `controlTemperatura` se ha modificado para adaptar la histéresis a este nuevo comportamiento dinámico. Se ha añadido el valor del setPoint al serial.

  Ahora, la histéresis se implementa mediante dos umbrales distintos alrededor del setpoint: uno para activar el sistema y otro para desactivarlo. Esto crea una zona de estabilidad que evita cambios constantes cuando la temperatura oscila cerca del valor objetivo.

- Se ha implementado almacenamiento persistente mediante EEPROM, permitiendo conservar el setpoint de temperatura tras reiniciar el sistema.

- Se ha optimizado la visualización en la pantalla LCD, eliminando el parpadeo mediante una actualización condicional de los datos mostrados.

- Se ha corregido un conflicto de hardware separando el potenciómetro y el sensor de luz en distintas entradas analógicas, garantizando lecturas estables.

Estas mejoras permiten que el usuario interactue activamente con el sistema.

## Arquitectura hardware

<img width="692" height="490" alt="Circuito" src="https://github.com/user-attachments/assets/108de504-5274-4956-b837-1e479f341db2" />


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
| Potenciómetro | A1 |
| LDR | A0 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| RTC SDA | A4 |
| RTC SCL | A5 |

### **Características principales**

- Alimentación: 5V
- Plataforma: Arduino UNO
- Comunicación I2C
- Sensores ambientales integrados
- Control mediante interrupciones
- Persistencia EEPROM para el setpoint de temperatura
- Control dinámico mediante setpoint ajustable

---

## Bill of Materials *(BOM)*

| Designator | Componente | Part Number | Cantidad | Proveedor | Función |
|---|---|---|---|---|---|
| U1 | Arduino UNO R3 | A000066 | 1 | Arduino / Wokwi | Control principal del sistema |
| U2 | LCD I2C 16x2 | LCD1602-I2C | 1 | AZDelivery / Wokwi | Interfaz visual del sistema |
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
| MEM1 | EEPROM interna Arduino | ATmega328P EEPROM | 1 | Integrado | Almacenamiento del setpoint |

---

##  Diagrama de flujo

```mermaid
flowchart TD

A[Inicio] --> B[Inicialización]

B --> C[Lectura sensores]

C --> D[Gestión ascensor]
D --> E{Botón pulsado}

E -->|Sí| F[Mover servo y actualizar planta]
E -->|No| H[Continuar]

F --> I
H --> I

I[Actualizar setpoint] --> J[Guardar en EEPROM]

J --> K[Control temperatura]
K --> L[Control humedad]
L --> M[Control iluminación]

M --> N[Actualizar LCD]
N --> O[Monitor serie]

O --> P[Loop]
P --> C
```


## Conclusiones
En este proyecto se ha desarrollado un sistema de control ambiental basado en Arduino, capaz de monitorizar variables como temperatura, humedad, iluminación y presencia, así como de actuar sobre distintos elementos del sistema. A partir de la versión inicial (práctica 2), se han introducido mejoras significativas que han permitido evolucionar el sistema hacia una solución más completa, flexible y robusta.

La incorporación de un potenciómetro para el ajuste del setpoint ha permitido transformar el sistema en un controlador dinámico, donde el comportamiento ya no depende de valores fijos, sino de una consigna definida por el usuario en tiempo real. Esto aporta mayor interactividad y realismo al sistema.

Además, la implementación de histéresis dinámica basada en el setpoint ha mejorado la estabilidad del control, evitando oscilaciones rápidas en los actuadores y asegurando un funcionamiento más eficiente y cercano a aplicaciones reales.

El uso de memoria EEPROM ha permitido dotar al sistema de persistencia, conservando la configuración del setpoint tras reinicios, lo que supone una mejora importante en términos de usabilidad.

Por otro lado, la optimización de la pantalla LCD y la corrección de conflictos de hardware han contribuido a mejorar la estabilidad general del sistema y la calidad de la visualización.

En conjunto, el sistema final presenta un comportamiento más robusto, adaptable e interactivo, acercándose al funcionamiento de un sistema real de control ambiental.
