# Lec01

2023.09.06

教授：李晓华



## $\S$0. 课程简介

Email:  lxhw@scu.edu.cn

* **成绩考核**：
  * **平时成绩**：考勤和作业（15%）+ 实验（20%）+ 期中和课堂测验（15%）
  * **期末考试**：50%

* **作业**：
  * **布置**：每次课堂末
  * **截止**：下周三晚12点

* **实验**：两个题目，以小组位单位完成



## $\S$1. Introduction

* **1.1 Why do we …**
* **1.2 Basic Concept**

-------

### 1.1 Why do we learn this course

…

-------

### 1.2 Basic Concepts

#### 1.2.1 Abstact Data Type & Data Structure

* **ADT**: Data (D) + Relation (R) + Operations (O)
  * **D**: 数据对象（数据集）
  * **R**: D上的关系集（逻辑结构）
  * **O**: 对D的基本操作集
* **Data Structure**
  * **Data Structure **ususally refers to an organization for Data in <font color=red>main memory</font>（存储结构） and Operations implementation.
  * **Data Structure** is a <font color=red>physical implementation</font> of an ADT.
    * Each Operatino associated with the ADT is implemented by one or more <font color=red>subroutines</font>.
    * An ADT may have <font color=red>multi</font> data structure.
* **Abstact Data Type vs. Data Structure**
  * **ADT**: What a data type can do.
  * **Data Structure**: How it is done.

* **Data Structure Philosophy**: 
  * Each data structure for a particular ADT has costs and benefits.

#### 1.2.2 Logical & Physical Form

* **Logical form** (数据的逻辑结构): 
  * definition of the data item within an ADT.
  * 从逻辑关系上描述数据，与数据的存储无关
  * **Ex**: 线性 (List) & 非线形 (Tree, Graph)
* **Physical form** (数据的物理/存储结构):
  * organization of the data items within a data structure.
  * 指数据在计算机内存中的结构
  * **Ex**: Array-based list (顺序表) & Linked list (链表) / 顺序存储 & 链式存储 & 索引存储 & 散式存储

#### 1.2.3 Algorithm & Program

* **Algorithm**: 
  * A method or a process followed to solve a problem
  * An algorithm takes in <font color=red> the input </font> to a problem and transforms it to <font color = red>the output</font>.
  * A problem can have many algorithm.
  * **Properties**:
    * 正确 & 具体步骤 & 确定性 & 有穷性 & 可终止 & 有输入输出

* **Program**:
  * An instance, or concrete representation for an algorithm in some programming language.
  * Can <font color=red>run</font>



----------

## $\S$3. Algorithm Analysis

* **3.1 Introduction**
* **3.2 Growth rate**
* **3.3 Algorithm analysis**
* **3.4 Space cost analysis**

------

### 3.1 Introduction — Algorithm Efficiency

* **Algorithm efficiency**

  * **Method 1**: Empirical analysis, stimulation
    * program, run and get a result.
  * **Method 2**: Asymptotic analysis (渐进分析)
    * Step 1: convert algotithm to Time / Space cost function.
    * Step 2: analyze cost function using Asymptotic analysis.

* **Algorithm Time Cost Function** (时间代价函数)

  * **General format**: $f(n)$

    * $n$ is the size of a problem (the number that determines the size of input data) / 问题规模	

  * **Best, Average, Worst Cases**:

    * eg.

    ```c
    int search(int K, int array[], int n) {
      for (int i = 0; i < n; i++) {
        if (K == array[i]) {
          return i;
        }
        return -1;
      }
    }
    ```
    
    * **Best case** $f_{best} (n)$: given $n$, $f(n)$ is smallest.
    * **Worst case** $f_{worst} (n)$: given $n$, $f(n)$ is largest.
    * **Average case** $f_{ave} (n)$: given $n$, $f(n)$ is in between.

----

### 3.2 Growth rate

* 做算法性能分析时关心的不是 $f(n)$ 的具体形式，而是 $f(n)$ 的 $growth\ rate$ (增长率)
  * **Linear Growth Rate**: $f(n) = n$
  * **Logarithm Growth Rate**: $f(n) = log(n)$
  * **Linear Logarithmic Growth Rate**: $f(n) = nlog(n)$
  * **Quadratic Growth Rate**: $f(n) = n^{2}$

* $c < log(n) < n < nlog(n) < n^2,\ n^3 \dots n^k,\ \dots,\ k^{n} < n!$

------

### 3.3 Algorithm Asymptotic Analysis

#### 3.3.1 Big-$\rm{O}$ Notation

* **Definition**: 
  * For $f(n) ≥ 0$， if there exists two positice constants $c$ and $n_0$ such that $f(n) ≤ c\cdot g(n)$ for all $n > n_0$, then we note $f(n) = \rm{O}(g(n))$, or we say $f(n)$ is in $\rm{O}(g(n)) - f(n)$.
* **Meaning**:
  * **An upper bound!** (上限)
  * For all input data sets big enough ($i.e., n>n_0$), the algorithm always executes in <font color = red>less than</font> $c\cdot g(n)$ steps.

#### 3.3.2 Big-$\rm{\Omega}$ Notation

* **Definition**:
  * For $f(n) ≥ 0$， if there exists two positice constants $c$ and $n_0$ such that $f(n) ≥ c\cdot g(n)$ for all $n > n_0$, then we note $f(n) = \rm{\Omega}(g(n))$.
* **Meaning**:
  * **An lower bound!** (下限)
  * For all input data sets big enough ($i.e., n>n_0$), the algorithm always executes in <font color = red>more than</font> $c\cdot g(n)$ steps.

#### 3.3.3 Big-$\rm{\Theta}$ Notation

* **Definition**:
  * If $f(n) = \rm{O}(h(n))$ and $f(n) = \rm{\Omega}(h(n))$, we say $f(n) = \rm{\Theta}(h(n))$









