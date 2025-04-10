/*
 * FIR_filter.ino - Ejemplo de uso del filtro FIR con CMSIS-DSP en Arduino Due
 */

#include <Arduino.h>
#include "FIRFilter.h"

#define BLOCK_SIZE 32
#define NUM_TAPS 29

q15_t firState[BLOCK_SIZE + NUM_TAPS - 1];
q15_t firCoeffs[NUM_TAPS] = {
    327, 624, 1103, 1832, 2838, 4126, 5678, 7448, 9366, 11339,
    13360, 15313, 17075, 18521, 19529, 20000, 19860, 19074, 17637, 15582,
    12976,  9918,  6494,  2784, -1098, -5082, -9075, -12960, -16609
};

FIRFilter firFilter;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    firFilter.init(firCoeffs, firState, NUM_TAPS);
    Serial.println("Filtro FIR inicializado.");
}

void loop() {
    static q15_t inputSignal[BLOCK_SIZE] = {0};
    static q15_t outputSignal[BLOCK_SIZE] = {0};
    
    // Generar una señal de prueba (ejemplo: impulso unitario)
    inputSignal[0] = 32767;  // Impulso
    for (int i = 1; i < BLOCK_SIZE; i++) {
        inputSignal[i] = 0;
    }
    
    // Aplicar el filtro
    firFilter.process(inputSignal, outputSignal, BLOCK_SIZE);
    
    // Mostrar la señal filtrada
    Serial.println("Salida del filtro FIR:");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        Serial.println(outputSignal[i]);
    }
    
    delay(1000);
}
