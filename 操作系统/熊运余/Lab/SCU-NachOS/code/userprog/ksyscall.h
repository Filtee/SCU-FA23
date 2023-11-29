/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/file.h>
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>

#define BUF_SIZE 60

void SysHalt() {
    kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2) {
    return op1 + op2;
}

int SysWrite(int addr, int size, OpenFileId output) {
    /* Load memory into buffer. */
    char buffer[BUF_SIZE];
    for (int i = 0; i < size; ++i) {
        kernel->machine->ReadMem(addr, 1, (int *) &buffer[i]);
        addr++;
    }
    /* Return result of write. */
    return write(output, buffer, (size_t) size);
}

int SysRead(int addr, int size, OpenFileId input) {
    /* Load input into buffer (as an array). */
    char buffer[BUF_SIZE];
    read(input, buffer, (size_t) size);
    /* Write buffer into the given address. */
    if (input == ConsoleInput) {
        int i = 0;
        while (i < size && buffer[i] != '\0') {
            kernel->machine->WriteMem(addr, 1, buffer[i]);
            addr++, i++;
        }
        kernel->machine->WriteMem(addr, 1, (char) NULL);
    }
    return 1;
}


SpaceId SysExec(int addr) {
    /* Load command (char array form) into buffer. */
    char buffer[BUF_SIZE];
    int ch;
    int i = 0;

    do {
        kernel->machine->ReadMem(addr, 1, (int *) &ch);
        buffer[i] = *((char *) &ch);
        addr++, i++;
    } while (*((char *) &ch) != '\0');

    /* Fork the process to execute. */
    pid_t child;
    child = vfork();

    if (child == 0) {
        execl("/bin/sh", "/bin/sh", "-c", buffer, NULL);
        _exit(EXIT_FAILURE);
    } else if (child < 0) {
        return EPERM;
    }
    return (SpaceId) child;
}

int SysJoin(SpaceId id) {
    return waitpid((pid_t) id, (int *) 0, 0);
}


#endif /* ! __USERPROG_KSYSCALL_H__ */
