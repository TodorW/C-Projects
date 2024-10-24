// kernel.c
#include "scheduler/scheduler.h"
#include "interrupts/interrupts.h"
#include "syscalls/syscalls.h"
#include "process_management/process.h"
#include "memory_management/memory.h"

void kernel_main() {
    // Initialize memory management
    memory_init();

    // Initialize the process management system
    process_init();

    // Initialize interrupts
    interrupts_init();

    // Initialize the scheduler
    scheduler_init();

    // Start the first process (usually the shell or init)
    start_first_process();

    // Main loop of the kernel
    while (1) {
        // Scheduler will handle process switching
        schedule();
    }
}