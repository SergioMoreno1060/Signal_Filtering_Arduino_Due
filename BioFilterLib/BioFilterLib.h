#ifndef BIOFILTERLIB_H
#define BIOFILTERLIB_H

#include <Arduino.h>

#define DEFAULT_BUFFER_SIZE 128
#define DEFAULT_FILTER_LENGTH 64

class FIRFilter {
public:
    FIRFilter(int filterLength = DEFAULT_FILTER_LENGTH, int bufferSize = DEFAULT_BUFFER_SIZE);
    void setCoefficients(float *coefficients, int length);
    float applyFIRfilter(float newSample, const char *mode = "same");
    void resetBuffer();

private:
    float *h;                  // Coeficientes del filtro
    float *xBuffer;            // Buffer circular de muestras
    int bufferIndex;           // Índice del buffer
    int filterLength;          // Longitud del filtro
    int bufferSize;            // Tamaño del buffer
};

#endif // BIOFILTERLIB_H