// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

void
incrementPC() {
    /* set previous programm counter (debugging only)*/
    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

    /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(NextPCReg));

    /* set next programm counter for brach execution */
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(NextPCReg) + 4);
}

void
ExceptionHandler(ExceptionType which) {
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
        case SyscallException:
            switch (type) {
                case SC_Halt:
                    DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

                    SysHalt();

                    ASSERTNOTREACHED();
                    break;

                case SC_Add:
                    DEBUG(dbgSys,
                          "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5)
                                 << "\n");

                    /* Process SysAdd Systemcall*/
                    int result;
                    result = SysAdd(/* int op1 */(int) kernel->machine->ReadRegister(4),
                            /* int op2 */(int) kernel->machine->ReadRegister(5));

                    DEBUG(dbgSys, "Add returning with " << result << "\n");
                    /* Prepare Result */
                    kernel->machine->WriteRegister(2, (int) result);

                    /* Modify return point */
                    {
                        /* set previous programm counter (debugging only)*/
                        kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                        /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                        kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                        /* set next programm counter for brach execution */
                        kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    }

                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_Write:
                    /* Debug notation. */
                    DEBUG(dbgSys, "Write from buffer to consoleOutput" << kernel->machine->ReadRegister(4)
                                                                       << kernel->machine->ReadRegister(5)
                                                                       << kernel->machine->ReadRegister(6) << "\n");

                    /* Read from registers. */
                    int addr;
                    addr = (int) kernel->machine->ReadRegister(4);
                    int size;
                    size = (int) kernel->machine->ReadRegister(5);
                    OpenFileId output;
                    output = (OpenFileId) kernel->machine->ReadRegister(6);

                    /* System write and load the writing result onto register 2. */
                    kernel->machine->WriteRegister(2, SysWrite(addr, size, output));

                    /* Increment PC register by 1, and return the system writing result. */
                    incrementPC();
                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_Read:
                    /* Debug notation. */
                    DEBUG(dbgSys, "Read file to buffer" << kernel->machine->ReadRegister(4) << ","
                                                        << kernel->machine->ReadRegister(5) << "words" << "\n");

                    /* Read from registers. */
                    addr = (int) kernel->machine->ReadRegister(4);
                    size = (int) kernel->machine->ReadRegister(5);
                    OpenFileId input;
                    input = (OpenFileId) kernel->machine->ReadRegister(6);

                    /* Call System read and load the result onto register 2. */
                    result = SysRead(addr, size, input);
                    kernel->machine->WriteRegister(2, (int) result);

                    /* Increment PC register by 1, and return the system writing result. */
                    incrementPC();
                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_Exec:
                    /* Debug notation. */
                    DEBUG(dbgSys, "execute a command" << kernel->machine->ReadRegister(4) << "\n");

                    /* Read from register 4 => the address of the input buffer (input command). */
                    addr = kernel->machine->ReadRegister(4);

                    /* Call System Execute and load the child process id onto register 2. */
                    pid_t child;
                    child = SysExec(addr);
                    kernel->machine->WriteRegister(2, (int) child);

                    /* Increment PC register by 1, and return the system writing result. */
                    incrementPC();
                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_Join:
                    /* Debug notation. */
                    DEBUG(dbgSys, "join" << kernel->machine->ReadRegister(4) << "\n");

                    /* Read from register 4 => the input child process id. */
                    child = (pid_t) kernel->machine->ReadRegister(4);

                    /* Call System Join to wait the process to be executed. */
                    result = SysJoin(child);
                    kernel->machine->WriteRegister(2, (int) result);

                    /* Increment PC register by 1, and return the system writing result. */
                    incrementPC();
                    return;
                    ASSERTNOTREACHED();
                    break;

                default:
                    cerr << "Unexpected system call " << type << "\n";
                    break;
            }
            break;
        default:
            cerr << "Unexpected user mode exception" << (int) which << "\n";
            break;
    }
    ASSERTNOTREACHED();
}
// Machine::ReadMem
//	"addr" -- the virtual address to read from
//	"size" -- the number of bytes to read (1, 2, or 4)
//	"value" -- the place to write the result