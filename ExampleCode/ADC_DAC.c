/*
Here is a simple example of how to use the ADC in STM32F103C8T6.
The code reads the ADC value from ADC Channel 0 (PA0) and prints it to the console.
The ADC is configured in continuous conversion mode, and the ADC clock is set to 12 MHz.
The code uses the STM32 Standard Peripheral Library.

The DAC example is below the ADC example.
*/
void RCC_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // Set ADC clock to PCLK2/6 = 12 MHz (72 MHz / 6)
}

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;    // Configure PA0 (ADC Channel 0)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // Analog input mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_Config(void) {
    ADC_InitTypeDef ADC_InitStructure;

    // Configure ADC basic parameters
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;              // Independent mode
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                   // Single channel mode
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;              // Continuous conversion mode
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // No external trigger
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;          // Data right alignment
    ADC_InitStructure.ADC_NbrOfChannel = 1;                         // Number of conversion channels = 1
    ADC_Init(ADC1, &ADC_InitStructure);

    // Configure ADC channel and sampling time
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // Channel 0, sampling time 55.5 cycles

    // Enable ADC
    ADC_Cmd(ADC1, ENABLE);

    // Calibrate ADC
    ADC_ResetCalibration(ADC1); // Reset calibration
    while (ADC_GetResetCalibrationStatus(ADC1)); // Wait for reset to complete

    ADC_StartCalibration(ADC1); // Start calibration
    while (ADC_GetCalibrationStatus(ADC1)); // Wait for calibration to complete

    // Start ADC conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t Read_ADC_Value(void) {
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); // Wait for conversion to complete
    return ADC_GetConversionValue(ADC1); // Return ADC conversion value
}

int main(void) {
    uint16_t adc_value;

    RCC_Config();  // Configure clocks
    GPIO_Config(); // Configure GPIO
    ADC_Config();  // Configure ADC

    while (1) {
        adc_value = Read_ADC_Value(); // Get ADC conversion value
        // Process adc_value here, e.g., send via UART or use in control logic
    }
}


/*
Here is a simple example of how to use the DAC in STM32F103C8T6.
The code outputs a static voltage level on DAC Channel 1 (PA4).
The DAC is configured in basic mode with no external trigger and output buffer enabled.
The code uses the STM32 Standard Peripheral Library.
*/

void RCC_Config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE); // Enable DAC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable GPIOA clock
}

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;    // Configure PA4 (DAC Channel 1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // Analog input mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DAC_Config(void) {
    DAC_InitTypeDef DAC_InitStructure;

    // Configure DAC Channel 1 basic parameters
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;             // No external trigger
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None; // No wave generation
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; // Enable output buffer
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    // Enable DAC Channel 1
    DAC_Cmd(DAC_Channel_1, ENABLE);
}

void Set_DAC_Value(uint16_t value) {
    DAC_SetChannel1Data(DAC_Align_12b_R, value); // Set 12-bit right-aligned data for DAC Channel 1
}

int main(void) {
    uint16_t dac_value = 2048; // Initial DAC value (middle of 12-bit range)

    RCC_Config();  // Configure clocks
    GPIO_Config(); // Configure GPIO
    DAC_Config();  // Configure DAC

    while (1) {
        Set_DAC_Value(dac_value); // Output DAC value
        // Modify dac_value here if needed to generate dynamic signals
    }
}

