/*
 * LMSFilter.cpp - Implementación del filtro LMS adaptativo optimizado con CMSIS-DSP para Arduino Due
 */

 #include "LMSFilter.h"

 LMSFilter::LMSFilter() : stateBuffer(nullptr), isInitialized(false) {}
 
 LMSFilter::~LMSFilter() {
     end();
 }
 
 void LMSFilter::init(const q15_t *coeffs, q15_t *state, uint32_t numTaps, q15_t mu) {
     if (isInitialized) return;
     stateBuffer = state;
     arm_lms_init_q15(&lmsInstance, numTaps, const_cast<q15_t *>(coeffs), stateBuffer, mu, 1);
     isInitialized = true;
 }
 
 void LMSFilter::process(const q15_t *input, const q15_t *desired, q15_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     q15_t error[blockSize];
     arm_lms_q15(&lmsInstance, input, desired, output, error, blockSize);
 }
 
 void LMSFilter::filterStatic(const q15_t *input, const q15_t *desired, q15_t *output, const q15_t *coeffs, q15_t *state, uint32_t numTaps, q15_t mu, uint32_t blockSize) {
     arm_lms_instance_q15 lmsInstance;
     arm_lms_init_q15(&lmsInstance, numTaps, const_cast<q15_t *>(coeffs), state, mu, 1);
     q15_t error[blockSize];
     arm_lms_q15(&lmsInstance, input, desired, output, error, blockSize);
 }
 
 void LMSFilter::end() {
     stateBuffer = nullptr;
     isInitialized = false;
 }
 