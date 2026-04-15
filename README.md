# ComunicacionArduino-Matlab_DobleBufer
Este trabajo presenta un método eficiente de adquisición de datos entre Arduino y MATLAB mediante comunicación serial asíncrona (UART). Se emplea una técnica de doble búfer con el ADC configurado en modo de ejecución libre y controlado por interrupciones, lo que permite una tasa de muestreo constante de hasta 9.6 kHz.

<img width="686" height="221" alt="imagen" src="https://github.com/user-attachments/assets/d8846907-6f43-4641-b89e-e0c2cd628472" />
Figura 1. Esquema de conexión entre la señal de entrada (Generador de funciones), Arduino (Canal analgico A0) y Matlab (Conexión UART).

<img width="921" height="224" alt="imagen" src="https://github.com/user-attachments/assets/c4841627-daee-4fda-8962-289ae1bf5fc0" />
Diag. de Flujo  1. Ciclo de trabajo general del código de Arduino

<img width="921" height="147" alt="imagen" src="https://github.com/user-attachments/assets/82d0b28a-1217-4922-ba70-6b3dba710fe7" />
Diag. de Flujo  2. Lógica interna de la ISR.

<img width="1050" height="74" alt="imagen" src="https://github.com/user-attachments/assets/9f2110fc-e751-4f5a-934e-f21a82dc578e" />
Figura 2. Tren de datos transmitidos y recibidos por Arduino y Matlab respectivamente.

Tabla 2. Velocidades máximas de transmisión de datos, velocidad máxima de la frecuencia de entrada y recomendación de pre-escala ADC con relación de factibilidad.

Velocidad de comunicación (Vcom)	Convertidor Analógico Digital (ADC)	Factibilidad	Frecuencia analógica máxima sugerida
[baud]	[bytes/s]
	Pre-escala	Frecuencia de muestreo (Fs)
[Ks/s]	
Fs<Vcom	
Fa<=Fs/10
9600	9600/8=1,200	128	9.6	No	960 Hz
19200	19200/8=2,400	128	9.6	No	960 Hz
38400	38400/8=4,800	128	9.6	No	960 Hz
57600	57600/8=7,200	128	9.6	No	960 Hz
74880	74880/8=9,360	128	9.6	Posibles pérdidas de datos poco significativas	960 Hz
		64	19.2	No	1,920 Hz
115200	115200/8=14,400	128	9.6	Si	960 Hz
		
64	19.2	Posibles pérdidas de datos poco significativas	1,920 Hz
		32	38.4	No	3,840 Hz
230400	230400/8=28,800	128	9.6	Si	960 Hz
		64	19.2	Si	1920 Hz
		32	38.4	Posibles pérdidas de datos medianamente significativas	3,840 Hz
		16	76.9	No	7690 Hz

Anexo A: Tabla de pre-escalas del ADC, valor de registros para seleccionarlo y sus características

ADPS2	ADPS1	ADPS0	Valor binario	Pre- escala	f_ADC (Hz)	Tiempo conversión (µs)	Muestras/s
0	0	0	000	2	8 MHz	1.625	~615 kS/s
0	0	1	001	2	8 MHz	1.625	~615 kS/s
0	1	0	010	4	4 MHz	3.25	~307 kS/s
0	1	1	011	8	2 MHz	6.5	~153 kS/s
1	0	0	100	16	1 MHz	13	~76.9 kS/s
1	0	1	101	32	500 kHz	26	~38.4 kS/s
1	1	0	110	64	250 kHz	52	~19.2 kS/s
1	1	1	111	128	125 kHz	104	~9.6 kS/s


