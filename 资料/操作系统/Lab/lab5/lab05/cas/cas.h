#ifndef CAS_H_INCLUDED
#define CAS_H_INCLUDED


char CAS(int* addr, int old_val, int new_val) {
    char result;
    asm volatile (
       "lock;\n"
        "cmpxchg %3, %1;\n"
        "sete %0\n"
        :"=q"(result) /*out*/
        :"m"(*addr),"a"(old_val),"r"(new_val) /*in*/
        :"memory"
    );
    return result;
}

#endif // CAS_H_INCLUDED
