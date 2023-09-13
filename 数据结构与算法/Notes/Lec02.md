# Lec02

2023.09.06

教授：李晓华



----

## $\S$0. C++ Review

e.g. Class 类

```cpp
class rectangle {
	private:
  	int w;
  	int h;
  
  public:
  	rectangle(int a, int b) {
      w = a;
      h = b;
		}
  
  	int getArea() {
      return w * h;
    }
  
  	int getPerimeter() {
      return 2 * (w + h);
    }
}

```

e.g. Template 模版

```cpp
// 函数模版
template <class T>
  T max(T a, T b) {
  	return (a > b) ? a : b;
	}

```

```cpp
// 类模版
template <class T> class rectangle {
  private:
  	T w;
  	T h;
  
  public :
  	rectangle(T a, T b) {
      w = a;
      h = b;
    }
  
  	T getArea() {
      return w * h;
    }
}

// 实例化
void main() {
  rectangle<int> r(1, 4);
  cout<<r.getArea()<<endl;
}

```



-----

## $\S$4. Lists, Stacks and Queue

* **4.1 List**
* **4.2 Stack**
* **4.3 Queue**

------

### 4.1 List

#### 4.1.1 List ADT

* **定义**： 
  * $n$ (≥ 0) 个元素的有限序列，记作 $(a_0, a_1, a_2, \cdots, a_{n-1})$
  * $a_i$ 是表中的第 $i$ 个元素，$n$ 是表长度，$n =0$ 时称为空表
* **特点**：
  * 除第一个元素外，其他每一个元素有且仅有一个直接前驱
  * 除最后一个元素外，其他每一个元素有且仅有一个直接后继
* **Components**:
  * **Data**: $n$ (≥ 0) 个元素
  * **Relation**: 序列，线形，1-1
  * **Operation**: 插入，删除，查找

```cpp
template <typename E> class List { // List ADT
private:
  void operator =(const List&) {}      // Protect assignment
  List(const List&) {}           // Protect copy constructor
public:
  List() {}          // Default constructor
  virtual  ̃List() {} // Base destructor
  // Clear contents from the list, to make it empty.
  virtual void clear() = 0;
  // Insert an element at the current location.
  // item: The element to be inserted
  virtual void insert(const E& item) = 0;
  // Append an element at the end of the list.
  // item: The element to be appended.
  virtual void append(const E& item) = 0;
  // Remove and return the current element.
  // Return: the element that was removed.
  virtual E remove() = 0;
  // Set the current position to the start of the list
  virtual void moveToStart() = 0;
  // Set the current position to the end of the list
  virtual void moveToEnd() = 0;
  // Move the current position one step left. No change
  // if already at beginning.
  virtual void prev() = 0;
  // Move the current position one step right. No change
  // if already at end.
  virtual void next() = 0;
  // Return: The number of elements in the list.
  virtual int length() const = 0;
  // Return: The position of the current element.
  virtual int currPos() const = 0;
  // Set current position.
  // pos: The position to make current.
  virtual void moveToPos(int pos) = 0;
  // Return: The current element.
  virtual const E& getValue() const = 0;
};

```

#### 4.1.2 Array-based / Sequential list

* **定义**：将线形表中的元素相继存放在一个连续的存储空间中

  * 可用<font color = red>一维数组</font>描述此存储结构
  * **特点**：在物理空间顺序存储

* **一般用一个数组、三个整型变量描述顺序表**

  * <font color=blue>**listArray**</font> 存放各个元素值
  * <font color=blue>**maxSize**</font> 存放数组的大小
  * <font color=blue>**listSize**</font> 存放顺序表的实际长度
    * **listSize ≤ maxSize**
  * <font color=blue>**curr**</font> 存放顺序表的实际长度

* **顺序表各种操作的实现及其时间复杂度**

  * **增删** —— <font color=blue>**insert**</font>  <font color=blue>**remove**</font>
    * $\rm{O}(n)$: <font color=blue>**listArray**</font>，<font color=blue>**listSize**</font> 的值会改变
  * **改变当前位置** —— <font color=blue>**prev**</font>  <font color=blue>**next**</font>  <font color=blue>**moveToPos**</font>  <font color=blue>**moveToStart**</font>  <font color=blue>**moveToEnd**</font>
    * $\rm{O}(1)$: 根据要求改变变量  <font color=blue>**curr**</font> 的值
  * **获取当前位置元素及索引** ——  <font color=blue>**getValue**</font>  <font color=blue>**currPos**</font> 
    * $\rm{O}(1)$
  * **获取线性表长度** ——  <font color=blue>**length**</font> 
    * $\rm{O}(1)$

* **Implementation**

  ```cpp
  template<typename E> // Array-based list implementation
  class AList : public List<E> {
  private:
      int maxSize;    // Maximum size of list
      int listSize;   // Number of list items now
      int curr;       // Position of current element
      E *listArray;   // Array holding list elements
  
  public:
      // Constructor
      AList(int size = defaultSize) {
          maxSize = size;
          listSize = curr = 0;
          listArray = new E[maxSize];
      }
  
      // Destructor
      ̃AList() { delete[] listArray; }
  
      // Reinitialize the list.
      void clear() {
          delete[] listArray;                  // Remove the array
          listSize = curr = 0;                 // Reset the size
          listArray = new E[maxSize];  				 // Recreate array
      }
  
      // Insert "it" at current position.
      void insert(const E &it) {
          Assert(listSize < maxSize, "List capacity exceeded");
          for (int i = listSize; i > curr; i--)  // Shift elements up
              listArray[i] = listArray[i - 1];   // to make room
          listArray[curr] = it;
          listSize++;                            // Increment list size
      }
  
      // Append "it".
      void append(const E &it) {
          Assert(listSize < maxSize, "List capacity exceeded");
          listArray[listSize++] = it;
      }
  
      // Remove and return the current element.
      E remove() {
          Assert((curr >= 0) && (curr < listSize), "No element");
          E it = listArray[curr];                    // Copy the element
          for (int i = curr; i < listSize - 1; i++)  // Shift them down
              listArray[i] = listArray[i + 1];
          listSize--;                                // Decrement size
          return it;
      }
  
      // Reset position.
      void moveToStart() { curr = 0; }
  
      // Set at end.
      void moveToEnd() { curr = listSize; }
  
      // Back up.
      void prev() { if (curr != 0) curr--; }
  
      // Next.
      void next() { if (curr < listSize) curr++; }
  
      // Return list size.
      int length() const { return listSize; }
  
      // Return current position.
      int currPos() const { return curr; }
  
      // Set current list position to "pos".
      void moveToPos(int pos) {
          Assert((pos >= 0) && (pos <= listSize), "Pos out of range");
          curr = pos;
      }
  
      // Return current element.
      const E &getValue() const {
          Assert((curr >= 0) && (curr < listSize), "No current element");
          return listArray[curr];
      }
  };
  
  ```

#### 4.1.3 Linked list

#### 4.1.4 Freelists

#### 4.1.5 Double linked list

















 
