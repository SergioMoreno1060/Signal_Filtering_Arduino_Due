#include <Arduino.h>
#include "BioFilterLib.h"
#include "Waveforms.h"

#define ECG_SIGNAL_INDEX 4  // Índice de la señal ECG en waveformsTable
#define SIGNAL_LENGTH 1000 // Longitud de la señal
#define FIR_LENGTH 120      // Longitud del filtro FIR

float firCoefficients[FIR_LENGTH] = {
    // Aquí va tu lista de coeficientes FIR
      0.0000, -0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000,
      0.0000, -0.0000, -0.0000, -0.0000, -0.0000, -0.0000, -0.0000, -0.0000,
      -0.0000, 0.0000, 0.0000, 0.0010, 0.0010, 0.0010, 0.0020, 0.0010, 0.0010,
      0.0000, -0.0010, -0.0020, -0.0030, -0.0040, -0.0040, -0.0040, -0.0030,
      -0.0010, 0.0010, 0.0040, 0.0060, 0.0080, 0.0090, 0.0090, 0.0070, 0.0040,
      -0.0010, -0.0070, -0.0130, -0.0180, -0.0210, -0.0220, -0.0190, -0.0130,
      -0.0020, 0.0120, 0.0300, 0.0490, 0.0690, 0.0870, 0.1020, 0.1130, 0.1190,
      0.1190, 0.1130, 0.1020, 0.0870, 0.0690, 0.0490, 0.0300, 0.0120, -0.0020,
      -0.0130, -0.0190, -0.0220, -0.0210, -0.0180, -0.0130, -0.0070, -0.0010,
      0.0040, 0.0070, 0.0090, 0.0090, 0.0080, 0.0060, 0.0040, 0.0010, -0.0010,
      -0.0030, -0.0040, -0.0040, -0.0040, -0.0030, -0.0020, -0.0010, 0.0000,
      0.0010, 0.0010, 0.0020, 0.0010, 0.0010, 0.0010, 0.0000, 0.0000, -0.0000,
      -0.0000, -0.0000, -0.0000, -0.0000, -0.0000, -0.0000, -0.0000, 0.0000,
      0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, -0.0000, 0.0000
};

FIRFilter ecgFilter(FIR_LENGTH, SIGNAL_LENGTH);

void setup() {
    Serial.begin(115200);
    ecgFilter.setCoefficients(firCoefficients, FIR_LENGTH);
    
    // Encabezado CSV
    Serial.println("Original,Filtrada");
}

void loop() {
    for (int i = 0; i < SIGNAL_LENGTH; i++) {
        float originalSample = waveformsTable[ECG_SIGNAL_INDEX][i];
        float filteredSample = ecgFilter.applyFIRfilter(originalSample);
        
        // Imprimir datos en formato CSV
        Serial.print(originalSample);
        Serial.print(",");
        Serial.println(filteredSample);
    }

    delay(1000); // Esperar para no saturar la consola
}
