# Lec 03

教授：袁学东

2023/09/18



# Review

* **The von Neumann Model**
  * **Three hardware systems**:
    * A central processing unit (CPU) 
    * A main memory system
    * An I/O system
  * The capacity to carry out sequential instruction processing.
  * A **single data path** between the CPU and main memory. 
    * This single path is known as *the von Neumann bottleneck*.



# $\S$2. Data Representation in Computer Science



# $\S$4. MARIE: An Introduction to a Simple Computer

## 4.1

## 4.3 The Bus

* **Bus arbitration**:

  * In systems with more than one master device, **bus arbitration** is required. 

  * Bus arbitration schemes must provide priority to certain master devices and, at the same time, make sure lower priority devices are not starved out.

  * **Catagories**:

    **(1) Daisy chain arbitration**

    * This scheme uses a “grant bus” control line that is passed down the bus from the highest priority device to the lowest priority device.
    * Fairness is not ensured, and it is possible that low- priority devices are “starved out” and never allowed to use the bus.

    **(2) Centralized parallel arbitration**

    * Each device has a request control line to the bus and a **centralized arbiter** selects who gets the bus.

    **(3) Distributed arbitration using <font color=blue>self-selection</font>**

    * This scheme is similar to centralized arbitration but instead of a central authority selecting who gets the bus, **the devices themselves** determine who has highest priority and who should get the bus.

    **(4) Distributed arbitration using <font color=blue>collision detection</font>**

    * Each device is allowed to make a request for the bus. If the bus detects any **collisions** (multiple simultaneous requests), the device must make another request.



## 4.4 Clocks

* **Clock**:

  * Every computer contains an internal clock that **regulates how quickly instructions can be executed**.

  * The clock also synchronizes all of the components in the system. As the clock ticks, it sets the pace for everythingthat happens in the system.

  * Instruction performance is often measured in **clock cycles**—the time between clock ticks —instead of seconds.
  * **Formula**:
    * $\rm{CPU\ time = \frac{seconds}{program} \times \frac{average\ cycles}{instruction} \times \frac{seconds}{cycle}}\\$

## 4.5 The Input/Output Subsystem

* **Input and output (I/O) devices**:

  * **Input and output** (**I/O**) **devices** allow us to communicate with the computer system.

  * I/O is the transfer of data between primary memory and various I/O peripherals.

  * Performed in two ways:

    **(1) Memory-mapped I/O**

    * The registers in the interface appear in the computer’s memory map, and there is no real difference between accessing memory and accessing an I/O device.

    **(2) instruction-based I/O**

    * The CPU has specialized instructions that perform the input and output.

## 4.6 Memory Organization and Addressing

* **Memory location**
  * Each register (more commonly referred to as a **memory location**) has a **unique** address.
  * Memory addresses usually start at zero and progress upward.
* **Address**
  * An address is typically represented by an unsigned integer.
  * **Byte addressable**:
    * Each individual byte has a unique address.
    * most current machines are byte addressable (even though they have 32-bit or larger words).
  * **Word addressable**:
    *  Each word (not necessarily each byte) has its own address.
* **Memory Alignment**
  * 

* **Memory interleaving**

  * **Definition**: Splits memory across multiple memory modules (or banks), in which multiple banks can be accessed simultaneously.

  * **Catagory**:

    * **High-order interleaving**: The high-order bits of the address are used.

      * Array elements are sequential.

      ![Fig4.6](/Users/chris/Documents/Courses/Fall2023/计算机组成和体系结构/Notes/img/Fig4.6.png)

    * **Low-order interleaving**: The low-order bits of the address are used to select the bank.

      * Array elements are not sequential. (每个Module 中的Element 并不连续，理论上写入更快)
      * We can access the array elements in parallel because each array element is in a different module.

      ![Fig4.7](/Users/chris/Documents/Courses/Fall2023/计算机组成和体系结构/Notes/img/Fig4.7.png)

## 4.7 Interrupts

* **Interrupts**
  * Events that alter (or interrupt) the normal flow of execution in the system.
  * **Trigger**:
    * I/O requests
    * Arithmetic errors (e.g. division by 0)
    * Arithmetic underflow or overflow
    * Invalid instructions (usually resulting from pointer issues)
    * …
  * **Category**:
    * **maskable**: can be disabled or ignored.
    * **nonmaskable**: a high-priority interrupt that cannot be disabled and must be acknowledged

## MARIE

* MARIE (**M**achine **A**rchitecture that is **R**eally **I**ntuitive and **E**asy), is a simple architecture consisting of **memory** and a **CPU**.

#### 4.8.1 Architecture

* **Characteristics**:

  * Binary, two’s complement

  * Stored program, fixed word length

  * Word (but not byte) addressable

  * 4K words of main memory (this implies 12 bits per address) 

  * 16-bit data (words have 16 bits)

  * 16-bit instructions: 4 for the opcode and 12 for the address

  * **Seven registers**:

    * A 16-bit accumulator (AC)

    * A 16-bit instruction register (IR)

    * A 16-bit memory buffer register (MBR)

    * A 12-bit program counter (PC)

    * A 12-bit memory address register (MAR)

    * An 8-bit input register

    * An 8-bit output register

#### 4.8.2 Registers and Buses

* **AC:** The **accumulator**, which holds data values. This is a **general-purpose register,** and it holds data that the CPU needs to process. Most computers today have multiple general-purpose registers.
*  **MAR:** The **memory address register**, which holds the memory address of the data being referenced.
* **MBR:** The **memory buffer register**, which holds either the data just read from memory or the data ready to be written to memory.
* **PC:** The **program counter**, which holds the address of **<font color = blue>the next instruction</font>** to be executed in the program.
* **IR:** The **instruction register**, which holds the next instruction to be executed.
* **InREG:** The **input register**, which holds data from the input device.
* **OutREG:** The **output register**, which holds data for the output device.



