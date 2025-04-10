/*
 * FIRFilter.cpp - Implementación del filtro FIR optimizado con CMSIS-DSP para Arduino Due
 */

 #include "FIRFilter.h"

 FIRFilter::FIRFilter() : stateBuffer(nullptr), isInitialized(false) {}
 
 FIRFilter::~FIRFilter() {
     end();
 }
 
 void FIRFilter::init(const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize) {
     if (isInitialized) return;
     stateBuffer = state;
     arm_fir_init_q15(&firInstance, numTaps, const_cast<q15_t *>(coeffs), stateBuffer, blockSize);
     isInitialized = true;
 }
 
 void FIRFilter::process(const q15_t *input, q15_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     arm_fir_q15(&firInstance, input, output, blockSize);
 }
 
 void FIRFilter::filterStatic(const q15_t *input, q15_t *output, const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize) {
     arm_fir_instance_q15 firInstance;
     arm_fir_init_q15(&firInstance, numTaps, const_cast<q15_t *>(coeffs), state, blockSize);
     arm_fir_q15(&firInstance, input, output, blockSize);
 }
 
 void FIRFilter::end() {
     stateBuffer = nullptr;
     isInitialized = false;
 }
 