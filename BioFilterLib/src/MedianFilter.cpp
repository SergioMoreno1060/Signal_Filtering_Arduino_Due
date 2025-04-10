/*
 * MedianFilter.cpp - Implementación del filtro de mediana optimizado para Arduino Due
 */

 #include "MedianFilter.h"
 #include <cstdlib>
 
 MedianFilter::MedianFilter() : buffer(nullptr), isInitialized(false), windowSize(0) {}
 
 MedianFilter::~MedianFilter() {
     end();
 }
 
 void MedianFilter::init(uint32_t windowSize) {
     if (isInitialized) return;
     this->windowSize = windowSize;
     buffer = (q15_t*)malloc(windowSize * sizeof(q15_t));
     if (buffer) {
         isInitialized = true;
     }
 }
 
 void MedianFilter::process(const q15_t *input, q15_t *output, uint32_t blockSize) {
     if (!isInitialized) return;
     for (uint32_t i = 0; i < blockSize; i++) {
         uint32_t halfWindow = windowSize / 2;
         uint32_t start = (i < halfWindow) ? 0 : (i - halfWindow);
         uint32_t end = (i + halfWindow >= blockSize) ? blockSize - 1 : (i + halfWindow);
         uint32_t currentWindowSize = end - start + 1;
         
         for (uint32_t j = 0; j < currentWindowSize; j++) {
             buffer[j] = input[start + j];
         }
         
         std::sort(buffer, buffer + currentWindowSize);
         output[i] = buffer[currentWindowSize / 2];
     }
 }
 
 void MedianFilter::filterStatic(const q15_t *input, q15_t *output, uint32_t windowSize, uint32_t blockSize) {
     q15_t *buffer = (q15_t*)malloc(windowSize * sizeof(q15_t));
     if (!buffer) return;
     
     for (uint32_t i = 0; i < blockSize; i++) {
         uint32_t halfWindow = windowSize / 2;
         uint32_t start = (i < halfWindow) ? 0 : (i - halfWindow);
         uint32_t end = (i + halfWindow >= blockSize) ? blockSize - 1 : (i + halfWindow);
         uint32_t currentWindowSize = end - start + 1;
         
         for (uint32_t j = 0; j < currentWindowSize; j++) {
             buffer[j] = input[start + j];
         }
         
         std::sort(buffer, buffer + currentWindowSize);
         output[i] = buffer[currentWindowSize / 2];
     }
     
     free(buffer);
 }
 
 void MedianFilter::end() {
     if (buffer) {
         free(buffer);
         buffer = nullptr;
     }
     isInitialized = false;
 }
 