#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINES 100
#define MAX_LINE_LENGTH 1024
typedef struct {
    char text[MAX_LINE_LENGTH];
} Line;
typedef struct {
    Line lines[MAX_LINES];
    int num_lines;
} TextEditor;
void init_text_editor(TextEditor* editor) {
    editor->num_lines = 0;}
void add_line(TextEditor* editor, char* text) {
    if (editor->num_lines < MAX_LINES) {
        strcpy(editor->lines[editor->num_lines].text, text);
        editor->num_lines++;}}
void delete_line(TextEditor* editor, int line_number) {
    if (line_number >= 0 && line_number < editor->num_lines) {
        for (int i = line_number; i < editor->num_lines - 1; i++) {
            strcpy(editor->lines[i].text, editor->lines[i + 1].text);}
        editor->num_lines--;}}
void print_editor(TextEditor* editor) {
    for (int i = 0; i < editor->num_lines; i++) {
        printf("%d: %s\n", i + 1, editor->lines[i].text);}}
void handle_input(TextEditor* editor) {
    char command[1024];
    printf("Enter a command (add, delete, print, quit): ");
    fgets(command, 1024, stdin);
    command[strlen(command) - 1] = '\0';
    if (strcmp(command, "add") == 0) {
        char text[MAX_LINE_LENGTH];
        printf("Enter a line of text: ");
        fgets(text, MAX_LINE_LENGTH, stdin);
        text[strlen(text) - 1] = '\0';
        add_line(editor, text);
    } else if (strcmp(command, "delete") == 0) {
        int line_number;
        printf("Enter the line number to delete: ");
        scanf("%d", &line_number);
        delete_line(editor, line_number - 1);
    } else if (strcmp(command, "print") == 0) {
        print_editor(editor);
    } else if (strcmp(command, "quit") == 0) {
        exit(0);
    } else {
        printf("Invalid command\n");}}
int main() {
    TextEditor editor;
    init_text_editor(&editor);
    while (1) {
        handle_input(&editor);}
    return 0;}
