#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#define KERNEL_HEAP_SIZE 1024
#define KERNEL_STACK_SIZE 1024
#define MAX_PROCESSES 10
#define TIME_SLICE 5
typedef enum {
    READY,
    RUNNING,
    TERMINATED
} ProcessState;
typedef struct {
    int pid;
    char* name;
    int* stack;
    int stack_size;
    ProcessState state;
} PCB;
typedef struct {
    PCB* current_process;
    PCB* process_list;
    int process_count;
    char* heap;
    int heap_size;
    int current_index; 
} Kernel;
Kernel* kernel;
void kernel_init() {
    kernel = (Kernel*)malloc(sizeof(Kernel));
    kernel->current_process = NULL;
    kernel->process_list = (PCB*)malloc(sizeof(PCB) * MAX_PROCESSES);
    kernel->process_count = 0;
    kernel->heap = (char*)malloc(KERNEL_HEAP_SIZE);
    kernel->heap_size = KERNEL_HEAP_SIZE;
    kernel->current_index = 0; 
}
PCB* kernel_create_process(char* name, int stack_size) {
    if (kernel->process_count >= MAX_PROCESSES) {
        printf("Error: Maximum process limit reached.\n");
        return NULL;
    }
    PCB* process = &kernel->process_list[kernel->process_count++];
    process->pid = kernel->process_count;
    process->name = (char*)malloc(strlen(name) + 1);
    strcpy(process->name, name);
    process->stack = (int*)malloc(stack_size);
    process->stack_size = stack_size;
    process->state = READY;
    return process;
}
void kernel_terminate_process(PCB* process) {
    if (process) {
        process->state = TERMINATED;
        free(process->name);
        free(process->stack);
        process->name = NULL;
        process->stack = NULL;
    }
}
void kernel_switch_process(PCB* new_process) {
    if (kernel->current_process != NULL) {
        kernel->current_process->state = READY; 
    }
    kernel->current_process = new_process;
    kernel->current_process->state = RUNNING; 
}
void kernel_schedule() {
    if (kernel->process_count == 0) {
        printf("No processes to schedule.\n");
        return;
    }
    int original_index = kernel->current_index;
    do {
        if (kernel->process_list[kernel->current_index].state == READY) {
            kernel_switch_process(&kernel->process_list[kernel->current_index]);
            printf("Running process %s\n", kernel->current_process->name);
            break;
        }
        kernel->current_index = (kernel->current_index + 1) % kernel->process_count;
    } while (kernel->current_index != original_index);
}
void kernel_display_processes() {
    printf("Process List:\n");
    for (int i = 0; i < kernel->process_count; i++) {
        PCB* p = &kernel->process_list[i];
        printf("PID: %d, Name: %s, State: %s\n", p->pid, p->name, 
               p->state == READY ? "READY" : (p->state == RUNNING ? "RUNNING" : "TERMINATED"));
    }
}
void kernel_main() {
    kernel_init();
    PCB* process1 = kernel_create_process("Process 1", 1024);
    PCB* process2 = kernel_create_process("Process 2", 1024);
    PCB* process3 = kernel_create_process("Process 3", 1024);
    kernel_schedule(); 
    kernel_schedule(); 
    kernel_schedule(); 
    kernel_terminate_process(process2);
    kernel_display_processes(); 
    kernel_schedule(); 
}
int main() {
    kernel_main();
    free(kernel->process_list);
    free(kernel-> heap);
    free(kernel);
    return 0;
}