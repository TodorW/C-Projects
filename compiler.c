#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
    TOK_KEYWORD,
    TOK_IDENTIFIER,
    TOK_CONSTANT,
    TOK_OPERATOR,
    TOK_EOF
} TokenType;
typedef struct {
    TokenType type;
    char* value;
} Token;
Token* lex(char* source_code) {
    Token* tokens = (Token*)malloc(sizeof(Token));
    int token_count = 0;
    char* current_char = source_code;
    while (*current_char != '\0') {
        while (*current_char == ' ' || *current_char == '\t' || *current_char == '\n') {
            current_char++;}
        if (strncmp(current_char, "if", 2) == 0 || strncmp(current_char, "else", 4) == 0 || strncmp(current_char, "while", 5) == 0) {
            Token token;
            token.type = TOK_KEYWORD;
            token.value = (char*)malloc(strlen(current_char) + 1);
            strcpy(token.value, current_char);
            tokens[token_count++] = token;
            current_char += strlen(token.value);}
        else if ((*current_char >= 'a' && *current_char <= 'z') || (*current_char >= 'A' && *current_char <= 'Z') || *current_char == '_') {
            Token token;
            token.type = TOK_IDENTIFIER;
            token.value = (char*)malloc(256);
            int i = 0;
            while ((*current_char >= 'a' && *current_char <= 'z') || (*current_char >= 'A' && *current_char <= 'Z') || *current_char == '_' || (*current_char >= '0' && *current_char <= '9')) {
                token.value[i++] = *current_char;
                current_char++;}
            token.value[i] = '\0';
            tokens[token_count++] = token;}
        else if (*current_char >= '0' && *current_char <= '9') {
            Token token;
            token.type = TOK_CONSTANT;
            token.value = (char*)malloc(256);
            int i = 0;
            while (*current_char >= '0' && *current_char <= '9') {
                token.value[i++] = *current_char;
                current_char++;}
            token.value[i] = '\0';
            tokens[token_count++] = token;}
        else if (strchr("+-*/<>=", *current_char) != NULL) {
            Token token;
            token.type = TOK_OPERATOR;
            token.value = (char*)malloc(2);
            token.value[0] = *current_char;
            token.value[1] = '\0';
            tokens[token_count++] = token;
            current_char++;}
        else {
            printf("Error: unknown character '%c'\n", *current_char);
            exit(1);}}
    Token token;
    token.type = TOK_EOF;
    token.value = NULL;
    tokens[token_count++] = token;
    return tokens;}
void print_tokens(Token* tokens) {
    int i = 0;
    while (tokens[i].type != TOK_EOF) {
        switch (tokens[i].type) {
            case TOK_KEYWORD:
                printf("Keyword: %s\n", tokens[i].value);
                break;
            case TOK_IDENTIFIER:
                printf("Identifier: %s\n", tokens[i].value);
                break;
            case TOK_CONSTANT:
                printf("Constant: %s\n", tokens[i].value);
                break;
            case TOK_OPERATOR:
                printf("Operator: %s\n", tokens[i].value);
                break;}
        i++;}}
int main() {
    char source_code[] = "if x > 5 then y = 10";
    Token* tokens = lex(source_code);
    print_tokens(tokens);
    return 0;}
