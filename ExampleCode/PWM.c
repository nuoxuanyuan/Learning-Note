/*
Here is a simple example of how to use the PWM in STM32F103C8T6.
The code generates a 1 kHz PWM signal with a 50% duty cycle on PA6 using TIM3.
The code uses the STM32 Standard Peripheral Library.
*/


// Initialize GPIO for PWM output
void PWM_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIOA and TIM3 clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // Configure PA6 as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// Initialize TIM3 for PWM generation
void PWM_TIM3_Init(uint16_t period, uint16_t pulse) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // Configure TIM3 time base
    TIM_TimeBaseStructure.TIM_Period = period - 1;      // Auto-reload value
    TIM_TimeBaseStructure.TIM_Prescaler = 71;          // Prescaler (72 MHz / (71 + 1) = 1 MHz)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // Configure TIM3 PWM mode
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   // PWM mode 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = pulse;             // Set the duty cycle (pulse width)
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    // Enable TIM3
    TIM_Cmd(TIM3, ENABLE);

    // Enable TIM3 PWM output on channel 1
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

int main(void) {
    // Initialize GPIO and TIM3 for PWM
    PWM_GPIO_Init();

    // Set PWM period and duty cycle
    uint16_t period = 1000;  // Period = 1000 µs (1 kHz PWM frequency)
    uint16_t pulse = 500;    // Duty cycle = 50% (500 µs high, 500 µs low)
    PWM_TIM3_Init(period, pulse);

    while (1) {
        // Main loop does nothing; PWM runs independently
    }
}
