/*
 * MedianFilter.h - Filtro de mediana optimizado para Arduino Due
 */

 #ifndef MEDIANFILTER_H
 #define MEDIANFILTER_H
 
 #include <Arduino.h>
 #include <algorithm>
 
 class MedianFilter {
 public:
     MedianFilter();
     ~MedianFilter();
     void init(uint32_t windowSize);
     void process(const q15_t *input, q15_t *output, uint32_t blockSize);
     static void filterStatic(const q15_t *input, q15_t *output, uint32_t windowSize, uint32_t blockSize);
     void end();
 
 private:
     uint32_t windowSize;
     q15_t *buffer;
     bool isInitialized;
 };
 
 #endif // MEDIANFILTER_H
 