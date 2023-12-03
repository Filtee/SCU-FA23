#ifndef FSTEST_H
#define FSTEST_H

#include "filesys.h"
#include "disk.h"
//#include "stats.h"
#include "kernel.h"
#include "syscall.h"
#include "string.h"


//#define FileName 	"TestFile"
//#define Contents 	"1234567890"
//#define ContentSize 	strlen(Contents)
//#define FileSize 	((int)(ContentSize * 150))
//#define FileSize ((int)(ContentSize * 50))

extern Kernel *kernel;

void PerformanceTest(char *FileName);
static void FileWrite(char *FileName);
static void FileRead(char *FileName);

#endif // FSTEST_H