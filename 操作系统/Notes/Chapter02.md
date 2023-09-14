# Chapter02

2023.09.14

教授：熊运余



[TOC]

# $\S$2. Operating System Overview

* **2.1 Operating System Objectives and Functions**
* **2.2 The Evolution of Operating Systems**
* **2.3 Major Achievements**
* **2.4 Developments Leading to Modern Operating Systems**
* **2.5 Load of APP & OS**
* **2.6 Other topic**

----------------

## 2.1 OS Objectives and Functions

* **2.1.0 Introduction**
* **2.1.1 Operating System as a User/Computer interface**
* **2.1.2 Operating System as a Resource Manager**
* **2.1.3 Ease of Evolution of an Operating System**

---------

#### 2.1.0 Introduction

* **Operating System definition**: A program that …
  * Controls the execution of application programs.
  * Acts as an interface between applications and hardware.

* **Operating System Objectives** 
  * **As User/Computer Interface** —— Convenience / 方便
    * Makes the computer more convinient to use.
  * **As Resource Manager** —— Efficiency / 有效可靠
    * Allows computer system resources to be used in efficient manner.
  * **As System Software** —— Ability to evolve / 扩展
    * Permit effective development, testing and introduction of new system functions without interfering with services.

#### 2.1.1 Operating System as a User/Computer interface



#### 2.1.2 Operating System as a Resource Manager

* **Operating System as Resource Manager**

  * Responsible for managing resources / hardware.
  * Work in the same way as ordinary computer software.
    * It is program that is executed

  * Frequently relinquishes (放弃) and regains control of the processor

<img src="./image/Chapter02/Fig2.2.png" alt="Figure2.2" style="zoom:50%;" />

* **Kernel** (内核)
  * Portion of operating system that is in main memory
  * Contains most frequently used functions
  * Also called the nucleus (核子)
* **Shell** (外壳)
  * **CLI**: command line interface
  * **GUI**: graphical user interface

#### 2.1.3 Ease of Evolution of an Operating System

* **Why?**
  * hardware upgrades + new types of hardware
  * new services
  * to fix bug
* **How?**
  * Modularizaion
  * OS Architecture



-----------

## 2.2 The Evolution of Operating Systems

* **2.2.1 Serial Processing: No Operating Systems**
* **2.2.2 Simple Batch Systems**
* **2.2.3 Multiprogrammed Batch Systems**
* **2.2.4 Time-Sharing Systems**

--------

#### 2.2.1 Serial Processing: No Operating Systems

* **命名**: user have access to the system in series
* **特点**: programmer interacted directly with the computer hardware 
* **操作**: Machines run from a console with display lights, toggle switches (拨码开关), input device, and printer
* **<font color = red>Problem</font>**
  * **Scheduling**: Most installations used a hardcopy sign-up sheet to reserve computer time
  * **Setup time**: included loading the compiler, source program, saving compiled program, and loading and linking



#### 2.2.2 Simple Batch Systems

* **Central idea**:  <img align = "right" rightsrc="./image/Chapter02/Fig2.3.png" alt="Figure2.3" style="zoom:80%;" />
  * **<font color=red>Batch</font>**: made up by many jobs from users (批)
    * A job may use several program
    
  * The use of a piece of software known as the <font color = red>**monitor**</font>, that controls the sequence of events.
  
* **Process**:
* The monitor reads a job from the batch 
  * Then control is passed to this job
* When the job is completed, it returns control to the monitor
  * The monitor reads in the next job

* **Job Control Language** (JCL) 
  * Special type of programming language
  * Provides instruction to the monitor
  * What compiler to use
  * What data to use
  * …….
  
* **CPU mode** 
  * **User program executes in user mode** (用户模式)
    * Certain instructions may not be executed
    * Some memory can not be accessed
  
  * **Monitor executes in system mode** (系统模式)
    * Kernel mode (内核模式)
    * Privileged instructions are executed
    * Protected areas of memory may be accessed
  

* **Hardware Features**
  * **Memory protection**
    * Do not allow the memory area containing the monitor to be altered
  * **Timer**
    * Prevents a job from monopolizing (独占) the system
  * **Privileged instructions**
    * Certain machine level instructions can only be executed by the monitor
  * **Interrupts**
    * This feature gives the OS more flexibility in relinquishing (放弃) control to and regaining control from user programs



#### 2.2.3 Multiprogrammed Batch Systems

* **Central idea**:
  * Multiple jobs in memory at a time

<img src="./image/Chapter02/Fig2.6.png" alt="Figure2.6" style="zoom:60%;" />

* **Classify**:
  * **Uniprogramming**:
    * Processor must wait for I/O instruction to complete before preceding
  * **Multiprogramming**:
    * When one job needs to wait for I/O, the processor can switch to the other job
    * Also known as **Mutitasking**.

<img src="./image/Chapter02/Tab2.2.png" alt="Table2.2" style="zoom:50%;" />

<img src="./image/Chapter02/Tab2.3.png" alt="Table2.3" style="zoom:57%;" />



#### 2.2.4 Time-Sharing Systems

---------

## 2.3 Major Achievements



----------

## 2.4 Developments Leading to Modern Operating Systems



---------

## 2.5 Load of APP & OS



--------

## 2.6 Other topic