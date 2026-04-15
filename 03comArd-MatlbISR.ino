const uint16_t HEADER = 2000; // Valor mayor a 10 bits para evitar confusión
const uint8_t NUM_SAMPLES = 100; // Tamaño del paquete

volatile uint8_t bufferA[NUM_SAMPLES];
volatile uint8_t bufferB[NUM_SAMPLES];
volatile bool useBufferA = true;
volatile uint8_t indexBuffer = 0;
volatile bool packetReady = false;

// Puntero al buffer listo para enviar
volatile uint8_t* sendBuffer = nullptr;

void setup() {
  Serial.begin(115200); // Configurar igual en Matlab

  // Configuración ADC en modo free running con interrupciones
  ADMUX = (1 << REFS0); // Referencia AVcc, canal ADC0
  ADCSRA = (1 << ADEN)  // Habilitar ADC
         | (1 << ADATE) // Auto trigger
         | (1 << ADIE)  // Interrupción habilitada
// Prescaler 64 (1 1 0) (~19.2 kHz); Modificar considerando la tabla del anexo A.       
         | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
  ADCSRB = 0;           // Free running
  ADCSRA |= (1 << ADSC); // Iniciar conversión
}

ISR(ADC_vect) {
  uint8_t val = ADC>>2; // Lectura de 0–1023

  if (useBufferA) {
    bufferA[indexBuffer] = val;
  } else {
    bufferB[indexBuffer] = val;
  }

  indexBuffer++;

  if (indexBuffer >= NUM_SAMPLES) {
    indexBuffer = 0;
    packetReady = true;

    // Seleccionar buffer a enviar
    if (useBufferA) {
      sendBuffer = bufferA;
      useBufferA = false;
    } else {
      sendBuffer = bufferB;
      useBufferA = true;
    }
  }
}

void loop() {
  if (packetReady) {
    sendPacket(sendBuffer);
    packetReady = false;
  }
}

void sendPacket(volatile uint8_t* buf) {
  // Enviar header (2 bytes)
Serial.write(lowByte(HEADER));
  Serial.write(highByte(HEADER));

  // Enviar número de muestras (2 bytes)
  Serial.write(lowByte(100));
  //Serial.write(highByte(NUM_SAMPLES));

  // Enviar datos (2 bytes cada uno)
  Serial.write(lowByte(buf[i]));
  //Serial.write((uint8_t*)buf,100);
}
