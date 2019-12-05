/*
 * dma.h
 *
 * Created: 11/12/2019 3:39:43 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>
#ifndef DMA_H_
#define DMA_H_

#define byte0(w) ((uint8_t) ((uint32_t) (w) & 0xFF))
#define byte1(w) ((uint8_t) ((uint32_t) (w) >> 8))
#define byte2(w) ((uint8_t) ((uint32_t) (w) >> 16))

void dma_init(uint16_t * LUT, uint16_t dest_addr);




#endif /* DMA_H_ */