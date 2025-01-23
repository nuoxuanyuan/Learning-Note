/*
Here is a simple example of how to use the EXTI in STM32F103C8T6.
The code toggles the state of the onboard LED (PC13) when an external interrupt is triggered on PA0.
*/

// Initialize the LED pin
void LED_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable the GPIOC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configure PC13 as push-pull output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Set initial LED state to OFF
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

// Initialize external interrupt on PA0
void EXTI0_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // Enable GPIOA and AFIO clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // Configure PA0 as floating input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Map PA0 to EXTI0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    // Configure EXTI0 line
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Trigger on falling edge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // Configure NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // Highest priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;        // Highest sub-priority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// EXTI0 interrupt handler
void EXTI0_IRQHandler(void) {
    // Check if EXTI0 interrupt is triggered
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        // Toggle the LED state
        GPIOC->ODR ^= GPIO_Pin_13;

        // Clear the interrupt flag
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

int main(void) {
    // Initialize LED and external interrupt
    LED_Init();
    EXTI0_Init();

    while (1) {
        // Main loop does nothing, waiting for interrupts
    }
}
