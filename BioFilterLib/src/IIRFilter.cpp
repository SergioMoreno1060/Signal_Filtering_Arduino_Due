/*
 * IIRFilter.cpp - Implementación del filtro IIR optimizado con CMSIS-DSP para Arduino Due
 */

 #include "IIRFilter.h"

 IIRFilter::IIRFilter() : stateBuffer(nullptr), isInitialized(false) {}
 
 IIRFilter::~IIRFilter() {
     end();
 }
 
 void IIRFilter::init(const q31_t *coeffs, q31_t *state, uint32_t numStages) {
     if (isInitialized) return;
     stateBuffer = state;
     arm_biquad_cascade_df1_init_q31(&iirInstance, numStages, const_cast<q31_t *>(coeffs), stateBuffer, 1);
     isInitialized = true;
 }
 
 void IIRFilter::process(const q31_t *input, q31_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     arm_biquad_cascade_df1_q31(&iirInstance, input, output, blockSize);
 }
 
 void IIRFilter::filterStatic(const q31_t *input, q31_t *output, const q31_t *coeffs, q31_t *state, uint32_t numStages, uint32_t blockSize) {
     arm_biquad_casd_df1_inst_q31 iirInstance;
     arm_biquad_cascade_df1_init_q31(&iirInstance, numStages, const_cast<q31_t *>(coeffs), state, 1);
     arm_biquad_cascade_df1_q31(&iirInstance, input, output, blockSize);
 }
 
 void IIRFilter::end() {
     stateBuffer = nullptr;
     isInitialized = false;
 }
 