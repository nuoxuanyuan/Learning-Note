#include "stm32f10x.h"
/*
Here is a simple example of how to use the USART1 peripheral on the STM32F103C8T6 microcontroller.
The USART1 peripheral is configured to receive a character and send it back to the sender.
The baud rate is set to 9600 bps.
The USART1 peripheral is connected to the PC via an FTDI USB to serial converter.
The PC sends a character to the microcontroller, and the microcontroller sends the received character back to the PC.

The SPI and IIC examples are below this example.
*/


// Function prototypes
void USART1_Config(void);
void USART1_SendChar(uint8_t ch);
uint8_t USART1_ReceiveChar(void);

int main(void) {
    USART1_Config(); // Configure USART1

    while (1) {
        // Check if there is data received
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
            uint8_t received = USART1_ReceiveChar(); // Receive character
            USART1_SendChar(received);              // Send back the received character
        }
    }
}

// USART1 Configuration
void USART1_Config(void) {
    // Enable clocks for USART1, GPIOA, and AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // Configure PA9 (TX) as alternate function push-pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PA10 (RX) as input floating
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART1 configuration
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600; // Set baud rate
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    // Enable USART1
    USART_Cmd(USART1, ENABLE);
}

// Function to send a character via USART1
void USART1_SendChar(uint8_t ch) {
    // Wait until the transmit data register is empty
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, ch);
}

// Function to receive a character via USART1
uint8_t USART1_ReceiveChar(void) {
    // Wait until data is received
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (uint8_t)USART_ReceiveData(USART1);
}



/*
Here is a simple example of how to use the SPI1 peripheral on the STM32F103C8T6 microcontroller.
The SPI1 peripheral is configured as a master with the following settings:
- Full-duplex communication
- 8-bit data size
- Clock polarity low
- First clock edge
- Software NSS management
- Prescaler for SPI clock: 16
- MSB first
The SPI1 peripheral is connected to an SPI device (e.g., an SPI flash memory).
The microcontroller sends dummy data (0xFF) to the SPI device and receives data from the SPI device.

The IIC example is below this example
*/


// Function prototypes
void SPI1_Config(void);
uint8_t SPI1_TransmitReceive(uint8_t data);

int main(void) {
    SPI1_Config(); // Configure SPI1

    while (1) {
        // Transmit and receive data via SPI
        uint8_t receivedData = SPI1_TransmitReceive(0xFF); // Dummy data 0xFF
        SPI1_TransmitReceive(receivedData);               // Send back received data
    }
}

// SPI1 Configuration
void SPI1_Config(void) {
    // Enable clocks for SPI1 and GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

    // Configure GPIOA for SPI1: PA5 (SCK), PA6 (MISO), PA7 (MOSI)
    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure PA5 (SCK) as Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PA6 (MISO) as Input Floating
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PA7 (MOSI) as Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // SPI1 configuration
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // Full-duplex
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      // Master mode
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  // 8-bit data size
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                         // Clock polarity low
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                       // First clock edge
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                          // Software NSS management
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // Prescaler for SPI clock
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                 // MSB first
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    // Enable SPI1
    SPI_Cmd(SPI1, ENABLE);
}

// SPI1 Transmit and Receive Function
uint8_t SPI1_TransmitReceive(uint8_t data) {
    // Wait until the transmit buffer is empty
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    // Send data
    SPI_I2S_SendData(SPI1, data);

    // Wait until a data is received
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    // Return the received data
    return SPI_I2S_ReceiveData(SPI1);
}


/*
Here is a simple example of how to use the I2C1 peripheral on the STM32F103C8T6 microcontroller.
The I2C1 peripheral is configured as a slave with the following settings:
- 100kHz standard mode
- 7-bit slave address: 0x30
The I2C1 peripheral is connected to an I2C master device (e.g., an Arduino).
The microcontroller receives data from the I2C master and sends the received data back to the master.
*/


// Function prototypes
void I2C1_Config(void);
void I2C1_WriteData(uint8_t data);
uint8_t I2C1_ReadData(void);

int main(void) {
    I2C1_Config(); // Configure I2C1

    while (1) {
        // Wait until data is received
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == SET) {
            uint8_t receivedData = I2C1_ReadData(); // Read received data
            I2C1_WriteData(receivedData);          // Send the received data back
        }
    }
}

// I2C1 Configuration
void I2C1_Config(void) {
    // Enable clocks for I2C1 and GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Configure GPIOB for I2C1: PB6 (SCL) and PB7 (SDA)
    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure PB6 (SCL) and PB7 (SDA) as Alternate Function Open-Drain
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // I2C1 configuration
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_ClockSpeed = 100000; // 100kHz standard mode
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x30;  // Slave address
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStructure);

    // Enable I2C1
    I2C_Cmd(I2C1, ENABLE);
}

// Function to write data to I2C
void I2C1_WriteData(uint8_t data) {
    // Wait until the data register is empty
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) == RESET);
    I2C_SendData(I2C1, data);
}

// Function to read data from I2C
uint8_t I2C1_ReadData(void) {
    // Wait until data is received
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET);
    return (uint8_t)I2C_ReceiveData(I2C1);
}
