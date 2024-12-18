# Introductory

This repository is used as my note while studying skills such as one-chip computer and neural network.I’m just an undergrad student in China and English is a little pool.So this reposity is also a chance to improve it.

If you found any grammatical error, I will thank you for correcting me.You can connect me by email: jinhao@stu.ouc.edu.cn

If you like my note, you can give me a star.Or if you are learning these too, I would be happy if we can have a discussion.

Again, my email: jinhao@stu.ouc.edu.cn

Telegram: @nuoxuanyuan

# Contents <a id="home"> </a>

- [STM32 and one-chip computer](#s1)
  - [1.Kind of memory](#s1_1)
    - [1.1 Random Access Memory ](#s1_1_1)
    - [1.2 Read-Only Memory ](#s1_1_2)
  - [2.General Purpose Inputs and Outputs ](#s1_2)
  - [3. External Interrupt](#s1_3)
  - [4. Internal Interrupt and Timers](#s1_4)
- [Upgrade Waiting](#sn)

# STM32 and one-chip computer <a id="s1"></a>

As it’s whole name called single-chip programmable computer, The one-chip computer is just a much smaller computer.It has the basic structure which the computer also has.
But in different, the main frequency of the microcontroller is lower,and it’s memory is also so low that it can only store some simple programs.It delete the computer’s keyboard, keypads, screen, and so on.As an alternative, the microcontroller add many wires as it’s input and output.Because it is common for both input and output, it is also called General Purpose Inputs and Outputs(GPIO).

Let’s see more details of the micricontroller.

[Return Contents](#home)

## 1.Kind of memory <a id="s1_1"></a>

To use circuits to finish some algorithmic, first we need digital circuits to remember our date.

### 1.1 Random Access Memory <a id="s1_1_1"></a>

In the beginning, people use triggers to make registers.
But these registers can only keep datas when there is electricity.
All of the date will lost when the power goes out.
These memory are called Random Access Memory(RAM).
Today they still used by most of the microcontrollers because of their high speed read/write capability.

When we evaluate the performance of a microcontroller, the size of it’s RAM is always an import criteria. It’s same as the running memory of computer. And the stack is saved on it when the program running.

[Return Contents](#home)

### 1.2 Read-Only Memory <a id="s1_1_2"></a>

As we know, the data will lost if the power goes out. This made too many trouble to programmers in that time. So people devise a new memory which can hold data while there are no electricity. But as a price, this storage can only be read but can’t be written twice. The program usually has been written down when factor generate it. So this memory is called Read-Only Memory(ROM).

Although this store can keep data without power, it can’t be written as we want. So people start try to design new memory. With time going to, the fuse write register appeared to the word. This store is made by some wire with very low melting point. When we want to write program into it, We just need to apply electricity to a specific wire, and then it will fuse. This is followed by a weak signal current, and conductivity and non-conductivity will correspond to 0 and 1. 

In this way, we can write to the store but only once chance. So it’s still not enough. Shortly after, engineers devise many ROM can be written many time by some special ways. For example, Erasable Programmable Read-Only Memory(EPROM) can be erased by UV, Electrically-Erasable Programmable Read-Only Memory(EEPROM also E2PROM) can be erased by electric. With these erasable ROM, the memory can be write many times.

Today, flash used by many microcontrollers as a ROM because it can be erased fast and is convenient to write and read. But it’s read/write speed is still slower than RAM. So we usually put our programs on the flash, but the program will put it’s variants into a stack and hold by RAM.

[Return Contents](#home)

## 2.General Purpose Inputs and Outputs <a id="s1_2"></a>
General Purpose Inputs and Outputs is usually called GPIO. There are nothing special to explain it as the basic inputs and outputs of a one-chip computer. 

As outputs, it can output a high level equal to the power supply potential or a low level with the same potential to ground. As we know, STM32 and many one-chip computers have not only one model to output and input. 

The output model has push-pull output, open-drain output, multiplexed push-pull output, and so on. If we use the push-pull mode and put a high level, the output port does get a high level. But if we use the open-drain mode to do that, we will get nothing from the port, neither high or low level but a high resistance stage. Because the high level output of a one-chip computer is just a high resistance stage. We need to external pull-up register to get a real high level. The push-pull mode can do that directly because it already has pull-up register in it's inner circuit. But the other mode need you to use pull-up register by yourself.

The input mode has floating input and open-drain input. When we set the GPIO as open-drain input, we will get a high resistance stage at the port too. With the input mode, ont-chip computer can read the potentiometric from the port. It will get 1 if it is high level and 0 with low level.

There is a interesting question I have got from online. Look at the following circuit. If we use output mode of GPIO to control this buzzer, no matter low level and high level will make the R1 has a 2.5v or 0.85v divider. This will allow several hundred microamps of current at the base of the triode, causing the triode to conduct. This will cause the buzzer to operate no matter what.  

![](/img/GPIO.png "")

But how do we turn it off? Maybe you will say if we have the microcontroller using a 5v power supply, and then the high level output will turn it off. To what if other peripherals of the microcontroler have a maximum withstand voltage of less than 5v? The best answer is to use the open-drain mode. When we output a high level, the port will at high-resistance stage and R1 has no divider, and the buzzer will not work. R1 will have a 2.5v divider and the buzzer will begin to work when we output a low level.

[Return Contents](#home)

## 3. External Interrupt <a id="s1_3"></a>
We always use a dead loop to prevent the microcontroller from doing nothing, when we write a program to control it. But in many times, there will be some other things it must to do while running the main program. Such as switching to constant light by pressing a button when the running light is in operation. This is when an external interrupt will fulfill our needs.

The external interrupt allow the main program can be interrupted at any time. When the port satisfies the external interrupt condition, the main function will pause and run the interrupt instruction directly. After the execution of the interrupt function is finished, the program returns to the main function to continue running.

Interrupts have a priority, which is divided into preemption priority and response priority. When multiple interrupt arrive at different times, the interrupt with the earliest arrival time is prioritized. When different external interrupts arrive at the same time, priority is given to executing the interrupt with a high response priority. If another interrupt occurs during the execution of an interrupt, the new interrupt is executed if the interrupt has a higher preemption priority, and vice versa, waiting for the current interrupt to finish execution before executing the new interrupt.

In this note, we will use the C standard library of the STM32F103C8 as an example.

The external Interrupt on STM32 is also called EXTI. We must set the output mode as floating input mode and use the general GPIO clock and AFIO clock before we use the EXTI on STM32. For example:
`RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);`

Then we should map the port to the external interrupt. Here we use PA0 and EXTI0:
`GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);`

We can set the line after these work:
`EXTI_InitStructure.EXTI_Line = EXTI_Line0;`
`EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;`
`EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;`
`EXTI_InitStructure.EXTI_LineCmd = ENABLE;`

And then enable and init the EXTI:
`EXTI_Init(&EXTI_InitStructure);`

Finally, we need to use the NVIC of STM32 to set up it's priority:
`NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;`
`NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;`
`NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;`
`NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;`

And don't forget to init it: 
`NVIC_Init(&NVIC_InitStructure);`

Now, the microcontroller can get the interrupt single, but how can it to run the interrupt task? In acturely, there is a interrupt function to do that. You can define the function as followed:
`void EXTI0_IRQHandler(void) {}`

In this example, the function is EXTI0. This name is must as same as the line of external interrupt line which we have setted just now. Then, the mircocontroller will pause the main function and run the interrupt function when the interrupt arrive.

As we know, each GPIO of STM32 has an external inpterrupt line and the C standard library has 18 EXTI functions. So the external interrupt is always enough on STM32. But other microcontroller maybe not so lucky as STM32, such as ARM C51 which only has 2 external interrupt line. What should we do when we need more interrupt but only be allowed to use these mirocontroller? In fact, we can repalce external interrupt with internal interrupt. We will discuss it in next chapters.

[Return Contents](#home)

# Internal interrupt and Timers <a id="s1_4"></a>

We can use delay function if we want to let the cpu to wait a few times. But this action will made the program in dead loop and can do nothing until finfish the wait. We can use.the timer to adress this issue. The timer in mircrocontroller can also be used as a register. It works by counting from one number to the other and counting at the same interval for each number. So it can be use for both Timers and Registers.

The numner at the begining of the count is called the preloaded value and the number which the count terminates is called reload value.

[Return Contents](#home)

# Updata Waiting <a id="sn"> </a>
