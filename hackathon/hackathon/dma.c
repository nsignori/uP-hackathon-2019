/*
 * dma.c
 *
 * Created: 11/12/2019 3:39:59 PM
 *  Author: sharoncomora
 */ 
#include "dma.h"
//#include "lut_8_1.h"

void dma_init(uint16_t * LUT, uint16_t dest_addr) {
	
	DMA.CTRL |= DMA_RESET_bm;
	
	/*	repeat off - doesn't work
		repeat on -
	*/
	DMA.CH0.CTRLA =	DMA_CH_SINGLE_bm | 
					DMA_CH_BURSTLEN_2BYTE_gc |
					DMA_CH_REPEAT_bm;

	DMA.CH0.TRIGSRC = DMA_CH_TRIGSRC_EVSYS_CH0_gc;
	//uint8_t LUT_size = (uint8_t) (512);
	DMA.CH0.TRFCNT = 512;
	DMA.CH0.SRCADDR0 = byte0(LUT);
	DMA.CH0.SRCADDR1 = byte1(LUT);
	DMA.CH0.SRCADDR2 = byte2(LUT);
	
	DMA.CH0.DESTADDR0 = byte0(dest_addr);
	DMA.CH0.DESTADDR1 = byte1(dest_addr);
	DMA.CH0.DESTADDR2 = byte2(dest_addr);
	
	while(DMA.CH0.CTRLB & DMA_CH_CHBUSY_bm);
	
	DMA.CH0.REPCNT = 0;
	DMA.CH0.ADDRCTRL =	DMA_CH_SRCRELOAD_BURST_gc | 
						DMA_CH_SRCDIR_INC_gc | 
						DMA_CH_DESTRELOAD_NONE_gc | 
						DMA_CH_DESTDIR_FIXED_gc;
	DMA.CH0.CTRLA |= DMA_CH_REPEAT_bm;
	
	//DMA.CH0.CTRLB |= DMA_CH_TRNINTLVL_LO_gc;
	//DMA.CH0.CTRLB = DMA_CH_TRNINTLVL_LO_gc;
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	DMA.CTRL |= DMA_ENABLE_bm;
}