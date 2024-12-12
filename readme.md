# readme

# Introductory

This repository is used as my note while studying skills such as one-chip computer and neural network.
I’m just an undergrad student in China and English is a little pool.
So this reposity is also a chance to improve it.

If you found any grammatical error, I will thank you for correcting me.
You can connect me by email: jinhao@stu.ouc.edu.cn

Again, my email: jinhao@stu.ouc.edu.cn

Telegram: @nuoxuanyuan

# Contents

- [STM32 and one-chip computer](#s1)
    - [1.Kind of memory](#s1_1)
        - [1.1 Random Access Memory](#s1_1_1)
        - [1.2 Read-Only Memory](#s1_1_2)
    - [2.General Purpose Inputs and Outputs](#s1_2)

<a id="s1"></a>
# STM32 and one-chip computer

As it’s whole name called single-chip programmable computer, The one-chip computer is just a much smaller computer.
It has the basic structure which the computer also has.
But in different, the main frequency of the microcontroller is lower,
and it’s memory is also so low that it can only store some simple programs.
It delete the computer’s keyboard, keypads, screen, and so on.
As an alternative, the microcontroller add many wires as it’s input and output.
Because it is common for both input and output, it is also called General Purpose Inputs and Outputs(GPIO).

Let’s see more details of the micricontroller.

<a id="s1_1"></a>
## 1.Kind of memory

To use circuits to finish some algorithmic, first we need digital circuits to remember our date.

### 1.1 Random Access Memory <a id="s1_1_1"></a>

If you like my note, you can give me a star.
Or if you are learning these too, I would be happy if we can have a discussion.

In the beginning, people use triggers to make registers.
But these registers can only keep datas when there is electricity.
All of the date will lost when the power goes out.
These memory are called Random Access Memory(RAM).
Today they still used by most of the microcontrollers because of their high speed read/write capability.

When we evaluate the performance of a microcontroller, the size of it’s RAM is always an import criteria. It’s same as the running memory of computer. And the stack is saved on it when the program running.

### 1.2 Read-Only Memory <a id="s1_1_2"></a>

As we know, the data will lost if the power goes out. This made too many trouble to programmers in that time. So people devise a new memory which can hold data while there are no electricity. But as a price, this storage can only be read but can’t be written twice. The program usually has been written down when factor generate it. So this memory is called Read-Only Memory(ROM).

Although this store can keep data without power, it can’t be written as we want. So people start try to design new memory. With time going to, the fuse write register appeared to the word. This store is made by some wire with very low melting point. When we want to write program into it, We just need to apply electricity to a specific wire, and then it will fuse. This is followed by a weak signal current, and conductivity and non-conductivity will correspond to 0 and 1. 

In this way, we can write to the store but only once chance. So it’s still not enough. Shortly after, engineers devise many ROM can be written many time by some special ways. For example, Erasable Programmable Read-Only Memory(EPROM) can be erased by UV, Electrically-Erasable Programmable Read-Only Memory(EEPROM also E2PROM) can be erased by electric. With these erasable ROM, the memory can be write many times.

Today, flash used by many microcontrollers as a ROM because it can be erased fast and is convenient to write and read. But it’s read/write speed is still slower than RAM. So we usually put our programs on the flash, but the program will put it’s variants into a stack and hold by RAM.

## 2.General Purpose Inputs and Outputs <a id="s1_2"></a>

# Upgrade Waiting
