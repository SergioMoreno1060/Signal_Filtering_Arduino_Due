/*
 * FIRFilter.h - Filtro FIR optimizado con CMSIS-DSP para Arduino Due
 */

 #ifndef FIRFILTER_H
 #define FIRFILTER_H
 
 #include <Arduino.h>
 #include "arm_math.h"
 
 class FIRFilter {
 public:
     FIRFilter();
     ~FIRFilter();
     void init(const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize);
     void process(const q15_t *input, q15_t *output, uint32_t blockSize);
     static void filterStatic(const q15_t *input, q15_t *output, const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize);
     void end();
 
 private:
     arm_fir_instance_q15 firInstance;
     q15_t *stateBuffer;
     bool isInitialized;
 };
 
 #endif // FIRFILTER_H
 