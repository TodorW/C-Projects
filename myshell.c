#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 1024
#define MAX_ARGS 64
#define MAX_ARG_LENGTH 128
void split_line(char* line, char** args) {
    int i = 0;
    char* token = strtok(line, " \t\n");
    while (token!= NULL && i < MAX_ARGS) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");}
    args[i] = NULL;}
void execute_command(char** args) {
    pid_t pid = fork();
    if (pid == 0) { 
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        wait(NULL);}}
void shell_loop() {
    char line[MAX_LINE];
    char* args[MAX_ARGS];
    while (1) {
        printf("myshell> ");
        fgets(line, MAX_LINE, stdin);
        line[strlen(line) - 1] = '\0'; 
        split_line(line, args);
        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            chdir(args[1]);
        } else {
            execute_command(args);}}}
int main() {
    shell_loop();
    return 0;}
