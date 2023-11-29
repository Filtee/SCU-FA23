/* write.c
 *  Simple program to test whether the systemcall interface works.
  * *    Just do a write syscall that outputs a string to the console.
  *  */
 #include "syscall.h"
 
 int main()
 {
	int ConsleOutput=1;
	Write("\n\nHelloworld!\n\n",15,ConsleOutput);
	Halt();
 }
