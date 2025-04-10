/*
 * NotchFilter.h - Filtro Notch optimizado con CMSIS-DSP para Arduino Due
 */

 #ifndef NOTCHFILTER_H
 #define NOTCHFILTER_H
 
 #include <Arduino.h>
 #include "arm_math.h"
 
 class NotchFilter {
 public:
     NotchFilter();
     ~NotchFilter();
     void init(const q31_t *coeffs, q31_t *state);
     void process(const q31_t *input, q31_t *output, uint32_t blockSize);
     static void filterStatic(const q31_t *input, q31_t *output, const q31_t *coeffs, q31_t *state, uint32_t blockSize);
     void end();
 
 private:
     arm_biquad_casd_df1_inst_q31 notchInstance;
     q31_t *stateBuffer;
     bool isInitialized;
 };
 
 #endif // NOTCHFILTER_H
 