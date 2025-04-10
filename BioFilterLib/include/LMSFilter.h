/*
 * LMSFilter.h - Filtro LMS adaptativo optimizado con CMSIS-DSP para Arduino Due
 */

 #ifndef LMSFILTER_H
 #define LMSFILTER_H
 
 #include <Arduino.h>
 #include "arm_math.h"
 
 class LMSFilter {
 public:
     LMSFilter();
     ~LMSFilter();
     void init(const q15_t *coeffs, q15_t *state, uint32_t numTaps, q15_t mu);
     void process(const q15_t *input, const q15_t *desired, q15_t *output, uint32_t blockSize);
     static void filterStatic(const q15_t *input, const q15_t *desired, q15_t *output, const q15_t *coeffs, q15_t *state, uint32_t numTaps, q15_t mu, uint32_t blockSize);
     void end();
 
 private:
     arm_lms_instance_q15 lmsInstance;
     q15_t *stateBuffer;
     bool isInitialized;
 };
 
 #endif // LMSFILTER_H
 