/*
Here is a simple example of how to use the timer in STM32F103C8T6.
The code toggles an LED connected to PC13 every second using TIM2.
The code uses the STM32 Standard Peripheral Library.
*/

// Timer interrupt service routine
void TIM2_IRQHandler(void) {
    // Check if the timer overflow interrupt is triggered
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // Clear the timer update interrupt flag
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        // Handle the event triggered every second, such as toggling an LED
        // Example: Toggle the LED state
        GPIOC->ODR ^= GPIO_Pin_13;  // Assume an LED is connected to PC13
    }
}

// Initialize TIM2 as a 1-second timer
void TIM2_Init(void) {
    // Enable GPIOC and TIM2 clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Configure PC13 as push-pull output (used for connecting an LED)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Configure TIM2 as a timer that triggers an interrupt every second
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 7199; // Set the counter overflow value (72 MHz / 7200 = 10 kHz, 1s)
    TIM_TimeBaseStructure.TIM_Prescaler = 999; // Prescaler value (1000 / 1000 = 1Hz)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // Enable the timer update interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // Enable TIM2
    TIM_Cmd(TIM2, ENABLE);

    // Enable the interrupt in the interrupt controller
    NVIC_EnableIRQ(TIM2_IRQn);
}

int main(void) {
    // Initialize the timer
    TIM2_Init();

    while (1) {
        // The main loop does nothing; all work is handled by the interrupt
    }
}
