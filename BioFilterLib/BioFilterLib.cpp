#include "BioFilterLib.h"

FIRFilter::FIRFilter(int filterLength, int bufferSize)
    : filterLength(filterLength), bufferSize(bufferSize), bufferIndex(0) {
    h = new float[filterLength]();
    xBuffer = new float[bufferSize]();
}

void FIRFilter::setCoefficients(float *coefficients, int length) {
    if (length <= filterLength) {
        memcpy(h, coefficients, length * sizeof(float));
    }
}

float FIRFilter::applyFIRfilter(float newSample, const char *mode) {
    xBuffer[bufferIndex] = newSample;
    float output = 0.0;
    int index = bufferIndex;

    // Convolución discreta
    for (int i = 0; i < filterLength; i++) {
        output += h[i] * xBuffer[index];
        index = (index == 0) ? bufferSize - 1 : index - 1;
    }

    bufferIndex = (bufferIndex + 1) % bufferSize;

    if (strcmp(mode, "same") == 0) {
        return output; // Devuelve la salida filtrada centrada
    } else if (strcmp(mode, "full") == 0) {
        return output / filterLength; // Normaliza para "full"
    }
    return output;
}

void FIRFilter::resetBuffer() {
    memset(xBuffer, 0, bufferSize * sizeof(float));
    bufferIndex = 0;
}