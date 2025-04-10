/*
 * IIRFilter.h - Filtro IIR optimizado con CMSIS-DSP para Arduino Due
 */

 #ifndef IIRFILTER_H
 #define IIRFILTER_H
 
 #include <Arduino.h>
 #include "arm_math.h"
 
 class IIRFilter {
 public:
     IIRFilter();
     ~IIRFilter();
     void init(const q31_t *coeffs, q31_t *state, uint32_t numStages);
     void process(const q31_t *input, q31_t *output, uint32_t blockSize);
     static void filterStatic(const q31_t *input, q31_t *output, const q31_t *coeffs, q31_t *state, uint32_t numStages, uint32_t blockSize);
     void end();
 
 private:
     arm_biquad_casd_df1_inst_q31 iirInstance;
     q31_t *stateBuffer;
     bool isInitialized;
 };
 
 #endif // IIRFILTER_H
 