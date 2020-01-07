#include <CurrentController.h>


volatile CurrContParams CCParams = { 0 }; //global instance definition


void initADC() {

	LL_ADC_EnableInternalRegulator(ADC1);
	LL_mDelay(1);	//wait at least 10us for regulator

	while(!LL_ADC_IsInternalRegulatorEnabled(ADC1)) {}	//ensure regulator is on
	while(LL_ADC_IsEnabled(ADC1)) {}	//if enabled, halt
	LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
	while(LL_ADC_IsCalibrationOnGoing(ADC1)) {} //wait for end of calibration
	LL_mDelay(10);

	LL_ADC_EnableIT_EOC(ADC1); //enable interrupt

	LL_ADC_Enable(ADC1);

	while(!LL_ADC_IsActiveFlag_ADRDY(ADC1)) {}	//wait for ADC ready

	LL_ADC_REG_StartConversion(ADC1);	//enable conversions

}

void initDMA_ADC(uint32_t addr, uint32_t sz) {

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, addr);

	  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA));
	  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);
	  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
	  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sz);
	  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void initTIM_FLYWHEEL() {
	  LL_TIM_ClearFlag_UPDATE(TIM_FLYWHELL_PWM);	//set by init function
	  LL_TIM_CC_EnableChannel(TIM_FLYWHELL_PWM, LL_TIM_CHANNEL_CH1);	//enable PWM channels
	  LL_TIM_CC_EnableChannel(TIM_FLYWHELL_PWM, LL_TIM_CHANNEL_CH4);
	  LL_TIM_EnableAllOutputs(TIM_FLYWHELL_PWM);		//enable outputs
	  LL_TIM_GenerateEvent_UPDATE(TIM_FLYWHELL_PWM);	//generate an update event to sych adc to first address in dma
	  LL_TIM_EnableCounter(TIM_FLYWHELL_PWM);
}


void initTIM_CurrCont() {
	  LL_TIM_EnableIT_UPDATE(TIM_CC_LOOP);
	  LL_TIM_EnableCounter(TIM_CC_LOOP);
}
