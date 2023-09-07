# Lec01 

教授：熊运余

2023.09.07

## $\S$0. Introduction

* **Operating system**:

  * An interface between application and hardware.

  * A program that controls the execution of application programs.

* **课程目标**：
  * Concepts 概念
  * Design issues and principles 设计问题和原则
  * Mechanism 机制
* 

## $\S$1.

### 1.2 Processor Register

* **Introduction**
  * What is Registers:
    * Memory inside CPU
  * Why Registers:
    * Enable CPU to minimize main-memory references.
  * Can be classified into:
    * **User-visible registers** 用户可见寄存器
    * **Control and status registers** 控制和状态寄存器



* **User-visible registers** 用户可见寄存器
  * How to use:
    * **May be referenced** (访问/存取) by machine / assemble language.
  * Who will use:
    * **Available to all programs**.
    * application programs / system programs



* **Control and Status Register** 控制和状态寄存器
  * How to use:
    * Are used to control the operations of the processor
  * Who will see:
    * **Most are not visible to the users**.
    * Some may be accessibly be machine instruction in control or system mode.
  * Classify:
    * **Program Counter** (**PC**)
      * Contains the address of an instruction to be fetched.
    * **Instruction Register** (**IR**)
      * Contains the instruction most recently fetched.
    * **Program Status Word** (**PSW**)

---------

### 1.3 Instruction Execution

* Two stages of **each** Instruction Execution
  * Processor reads / loads / **Fetches** instructions from memory
  * Processor **Executes** each instruction
  * **Instruction Cycle**:
    * The processing required for a single instruction execution.



* **Key point**:
  * **Program Counter** (**PC**) contains the address of an instruction to be fetched.
  * **Instruction Register** (**IR**) contains the instruction most recently fetched.
  * **Program counter (PC) of CPU is incremented after each fetch.**

---------

### 1.4 Interrupts

#### 1.4.0 Interrupt Introduction

* **Why Interrupt in computer system?**
  * Most I/O devices are slower than the processor, so interrupt can improve CPU’s utilization (提高 CPU 利用率)
    * $i.e.$ Processor must pause to wait for device.
  * Count / Clock (计数时钟中断)
  * Avoid some program to monopolize CPU (避免 CPU 被独占)

* **Interrupt**
  * **Definition**: A mechanism by which other modules (I/O, clock) may interrupt the normal sequencing of the processor.
    * <font color=red>An I/O device can stop what the CPU is operating to provide some necessary service.</font>
  * **Interrupt** and **Restore / Resume**: 中断和恢复
    * **Both software and hardware** are used to support it.



#### 1.4.1 Interrupts and the Instruction Cycle

#### 1.4.2 Interrupt Processing

#### 1.4.3 Multiple Interrupts

#### 1.4.4 Multiprogramming