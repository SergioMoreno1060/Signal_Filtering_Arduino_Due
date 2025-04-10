/*
 * WaveletFilter.cpp - Implementación del filtro Wavelet optimizado con CMSIS-DSP para Arduino Due
 */

 #include "WaveletFilter.h"

 WaveletFilter::WaveletFilter() : stateBuffer(nullptr), isInitialized(false) {}
 
 WaveletFilter::~WaveletFilter() {
     end();
 }
 
 void WaveletFilter::init(const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize) {
     if (isInitialized) return;
     stateBuffer = state;
     arm_fir_init_q15(&waveletInstance, numTaps, const_cast<q15_t *>(coeffs), stateBuffer, blockSize);
     isInitialized = true;
 }
 
 void WaveletFilter::process(const q15_t *input, q15_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     arm_fir_q15(&waveletInstance, input, output, blockSize);
 }
 
 void WaveletFilter::filterStatic(const q15_t *input, q15_t *output, const q15_t *coeffs, uint32_t numTaps, q15_t *state, uint32_t blockSize) {
     arm_fir_instance_q15 waveletInstance;
     arm_fir_init_q15(&waveletInstance, numTaps, const_cast<q15_t *>(coeffs), state, blockSize);
     arm_fir_q15(&waveletInstance, input, output, blockSize);
 }
 
 void WaveletFilter::end() {
     stateBuffer = nullptr;
     isInitialized = false;
 }
 