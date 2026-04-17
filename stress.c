#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "Starting Memory Stress Test...\n");
    printf(1, "Attempting to allocate massive amounts of RAM.\n");

    int total_allocated = 0;
    
    // Loop 250 times, asking for 100 Pages (400KB) every single loop
    // Total request: ~100 Megabytes (More than enough to trigger pressure)
    for(int i = 1; i <= 250; i++) {
        char *mem = malloc(4096 * 100); 
        
        if(mem == 0) {
            printf(1, "CRITICAL: System entirely out of RAM and Swap Space at %d KB.\n", total_allocated);
            exit();
        }

        // Write to the memory to force the hardware to set the "Accessed" bit (PTE_A)
        mem[0] = 'X'; 
        
        total_allocated += 400;
        printf(1, "Allocated: %d KB without crashing...\n", total_allocated);
    }

    printf(1, "SUCCESS! The OS juggled the memory to the disk and survived!\n");
    exit();
}
