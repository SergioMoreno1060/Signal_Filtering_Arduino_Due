/*
 * NotchFilter.cpp - Implementación del filtro Notch optimizado con CMSIS-DSP para Arduino Due
 */

 #include "NotchFilter.h"

 NotchFilter::NotchFilter() : stateBuffer(nullptr), isInitialized(false) {}
 
 NotchFilter::~NotchFilter() {
     end();
 }
 
 void NotchFilter::init(const q31_t *coeffs, q31_t *state) {
     if (isInitialized) return;
     stateBuffer = state;
     arm_biquad_cascade_df1_init_q31(&notchInstance, 1, const_cast<q31_t *>(coeffs), stateBuffer, 1);
     isInitialized = true;
 }
 
 void NotchFilter::process(const q31_t *input, q31_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     arm_biquad_cascade_df1_q31(&notchInstance, input, output, blockSize);
 }
 
 void NotchFilter::filterStatic(const q31_t *input, q31_t *output, const q31_t *coeffs, q31_t *state, uint32_t blockSize) {
     arm_biquad_casd_df1_inst_q31 notchInstance;
     arm_biquad_cascade_df1_init_q31(&notchInstance, 1, const_cast<q31_t *>(coeffs), state, 1);
     arm_biquad_cascade_df1_q31(&notchInstance, input, output, blockSize);
 }
 
 void NotchFilter::end() {
     stateBuffer = nullptr;
     isInitialized = false;
 }
 