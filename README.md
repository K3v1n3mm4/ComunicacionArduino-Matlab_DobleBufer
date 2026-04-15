# ComunicacionArduino-Matlab_DobleBufer
Este trabajo presenta un método eficiente de adquisición de datos entre Arduino y MATLAB mediante comunicación serial asíncrona (UART). Se emplea una técnica de doble búfer con el ADC configurado en modo de ejecución libre y controlado por interrupciones, lo que permite una tasa de muestreo constante de hasta 9.6 kHz.

<img width="686" height="221" alt="imagen" src="https://github.com/user-attachments/assets/7d55d1b2-4462-4816-accb-d1766fc772e0" />

Figura 1. Esquema de conexión entre la señal de entrada (Generador de funciones), Arduino (Canal analgico A0) y Matlab (Conexión UART).

<img width="921" height="224" alt="imagen" src="https://github.com/user-attachments/assets/5dd90cbe-4f22-4d21-86cb-ed003d2b1090" />

Diag. de Flujo  1. Ciclo de trabajo general del código de Arduino

<img width="921" height="147" alt="imagen" src="https://github.com/user-attachments/assets/78d6a782-bfd9-4b42-b054-06c12e4b58c3" />

Diag. de Flujo  2. Lógica interna de la ISR.

<img width="1050" height="74" alt="imagen" src="https://github.com/user-attachments/assets/a0159130-3244-4f26-b804-b05a7c2fcee2" />

Figura 2. Tren de datos transmitidos y recibidos por Arduino y Matlab respectivamente.

Tabla 2. Velocidades máximas de transmisión de datos, velocidad máxima de la frecuencia de entrada y recomendación de pre-escala ADC con relación de factibilidad.

## Tabla de Factibilidad de Comunicación vs ADC

| Vcom (baud) | Vcom (bytes/s) | Pre-escala | Fs (Ks/s) | Condición (Fs < Vcom) | Fa máx sugerida (Hz) |
|------------|---------------|------------|-----------|----------------------|----------------------|
| 9600       | 1200          | 128        | 9.6       | No                   | 960                  |
| 19200      | 2400          | 128        | 9.6       | No                   | 960                  |
| 38400      | 4800          | 128        | 9.6       | No                   | 960                  |
| 57600      | 7200          | 128        | 9.6       | No                   | 960                  |
| 74880      | 9360          | 128        | 9.6       | Pérdidas mínimas     | 960                  |
| 74880      | 9360          | 64         | 19.2      | No                   | 1920                 |
| 115200     | 14400         | 128        | 9.6       | Sí                   | 960                  |
| 115200     | 14400         | 64         | 19.2      | Pérdidas mínimas     | 1920                 |
| 115200     | 14400         | 32         | 38.4      | No                   | 3840                 |
| 230400     | 28800         | 128        | 9.6       | Sí                   | 960                  |
| 230400     | 28800         | 64         | 19.2      | Sí                   | 1920                 |
| 230400     | 28800         | 32         | 38.4      | Pérdidas moderadas   | 3840                 |
| 230400     | 28800         | 16         | 76.9      | No                   | 7690                 |

> **Notas:**
> - Se asume transmisión de 8 bits por byte.
> - La condición de factibilidad se basa en: `Fs < Vcom`.
> - La frecuencia analógica máxima se estima como: `Fa ≤ Fs / 10`.

Anexo A: Tabla de pre-escalas del ADC, valor de registros para seleccionarlo y sus características

## Configuración del Prescaler del ADC

| ADPS2 | ADPS1 | ADPS0 | Valor binario | Pre-escala | f_ADC (Hz) | Tiempo de conversión (µs) | Muestras/s |
|------|------|------|---------------|------------|------------|----------------------------|------------|
| 0    | 0    | 0    | 000           | 2          | 8 MHz      | 1.625                      | ~615 kS/s  |
| 0    | 0    | 1    | 001           | 2          | 8 MHz      | 1.625                      | ~615 kS/s  |
| 0    | 1    | 0    | 010           | 4          | 4 MHz      | 3.25                       | ~307 kS/s  |
| 0    | 1    | 1    | 011           | 8          | 2 MHz      | 6.5                        | ~153 kS/s  |
| 1    | 0    | 0    | 100           | 16         | 1 MHz      | 13                         | ~76.9 kS/s |
| 1    | 0    | 1    | 101           | 32         | 500 kHz    | 26                         | ~38.4 kS/s |
| 1    | 1    | 0    | 110           | 64         | 250 kHz    | 52                         | ~19.2 kS/s |
| 1    | 1    | 1    | 111           | 128        | 125 kHz    | 104                        | ~9.6 kS/s  |



