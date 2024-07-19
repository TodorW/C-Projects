#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KERNEL_HEAP_SIZE 1024
#define KERNEL_STACK_SIZE 1024
typedef struct {
    int pid;
    char* name;
    int* stack;
    int stack_size;
    int state;
} PCB;
typedef struct {
    PCB* current_process;
    PCB* process_list;
    int process_count;
    char* heap;
    int heap_size;
} Kernel;
void kernel_init() {
    Kernel* kernel = (Kernel*)malloc(sizeof(Kernel));
    kernel->current_process = NULL;
    kernel->process_list = (PCB*)malloc(sizeof(PCB) * 10);
    kernel->process_count = 0;
    kernel->heap = (char*)malloc(KERNEL_HEAP_SIZE);
    kernel->heap_size = KERNEL_HEAP_SIZE;}
PCB* kernel_create_process(char* name, int stack_size) {
    PCB* process = &kernel->process_list[kernel->process_count++];
    process->pid = kernel->process_count;
    process->name = (char*)malloc(strlen(name) + 1);
    strcpy(process->name, name);
    process->stack = (int*)malloc(stack_size);
    process->stack_size = stack_size;
    process->state = 0;
    return process;}
void kernel_switch_process(PCB* new_process) {
    if (kernel->current_process != NULL) {}
    kernel->current_process = new_process;}
void kernel_main() {
    kernel_init();
    PCB* process1 = kernel_create_process("Process 1", 1024);
    PCB* process2 = kernel_create_process("Process 2", 1024);
    PCB* process3 = kernel_create_process("Process 3", 1024);
    kernel_switch_process(process1);
    printf("Running process %s\n", process1->name);
    kernel_switch_process(process2);
    printf("Running process %s\n", process2->name);
    kernel_switch_process(process3);
    printf("Running process %s\n", process3->name);}
int main() {
    kernel_main();
    return 0;}