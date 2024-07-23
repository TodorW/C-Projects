#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[256];
    int num_columns; 
    char** columns; 
    int num_rows; 
    char*** rows; 
} Table;
typedef struct {
    char name[256]; 
    int num_tables;
    Table** tables;
} Database;
Database* create_database(char* name) {
    Database* db = (Database*)malloc(sizeof(Database));
    strcpy(db->name, name);
    db->num_tables = 0;
    db->tables = (Table**)malloc(sizeof(Table*) * 10); 
    return db;}
Table* create_table(char* name, int num_columns, char** columns) {
    Table* table = (Table*)malloc(sizeof(Table));
    strcpy(table->name, name);
    table->num_columns = num_columns;
    table->columns = (char**)malloc(sizeof(char*) * num_columns);
    for (int i = 0; i < num_columns; i++) {
        table->columns[i] = (char*)malloc(sizeof(char) * 256);
        strcpy(table->columns[i], columns[i]);}
    table->num_rows = 0;
    table->rows = (char***)malloc(sizeof(char**) * 10); 
    return table;}
void add_row(Table* table, char** row_data) {
    table->num_rows++;
    table->rows = (char***)realloc(table->rows, sizeof(char**) * table->num_rows);
    table->rows[table->num_rows - 1] = (char**)malloc(sizeof(char*) * table->num_columns);
    for (int i = 0; i < table->num_columns; i++) {
        table->rows[table->num_rows - 1][i] = (char*)malloc(sizeof(char) * 256);
        strcpy(table->rows[table->num_rows - 1][i], row_data[i]);}}
void execute_query(Database* db, char* query) {
    char* token = strtok(query, " ");
    char* command = token;
    token = strtok(NULL, " ");
    char* table_name = token;
    token = strtok(NULL, " ");
    char* column_name = token;
    if (strcmp(command, "SELECT") == 0) {
        Table* table = find_table(db, table_name);
        if (table != NULL) {
            for (int i = 0; i < table->num_rows; i++) {
                printf("%s ", table->rows[i][find_column(table, column_name)]);}
            printf("\n");
        } else {
            printf("Table not found\n");}}
    else if (strcmp(command, "INSERT") == 0) {
        Table* table = find_table(db, table_name);
        if (table != NULL) {
            char** row_data = (char**)malloc(sizeof(char*) * table->num_columns);
            for (int i = 0; i < table->num_columns; i++) {
                row_data[i] = (char*)malloc(sizeof(char) * 256);
                strcpy(row_data[i], token);
                token = strtok(NULL, " ");}
            add_row(table, row_data);
        } else {
            printf("Table not found\n");}}
    else if (strcmp(command, "CREATE") == 0 && strcmp(token, "TABLE") == 0) {
        token = strtok(NULL, " ");
        char* table_name = token;
        token = strtok(NULL, " ");
        int num_columns = atoi(token);
        char** columns = (char**)malloc(sizeof(char*) * num_columns);
        for (int i = 0; i < num_columns; i++) {
            token = strtok(NULL, " ");
            columns[i] = (char*)malloc(sizeof(char) * 256);
            strcpy(columns[i], token);}
        Table* table = create_table(table_name, num_columns, columns);
        db->num_tables++;
        db->tables = (Table**)realloc(db->tables, sizeof(Table*) * db->num_tables);
        db->tables[db->num_tables - 1] = table;}
    else {
        printf("Unsupported query\n");}}
Table* find_table(Database* db, char* table_name) {
    for (int i = 0; i < db->num_tables; i++) {
        if (strcmp(db->tables[i]->name, table_name) == 0) {
            return db->tables[i];}}
    return NULL;}
int find_column(Table* table, char* column_name) {
    for (int i = 0; i < table->num_columns; i++) {
        if (strcmp(table->columns[i], column_name) == 0) {
            return i;}}
    return -1;}
int main() {
    Database* db = create_database("mydb");
    char* columns[] = {"id", "name", "age"};
    Table* table = create_table("users", 3, columns);
    db->num_tables++;
    db->tables = (Table**)realloc(db->tables, sizeof(Table*) * db->num_tables);
    db->tables[db->num_tables - 1] = table;
    char* row1[] = {"1", "Alice", "25"};
    char* row2[] = {"2", "Bob", "30"};
    char* row3[] = {"3", "Charlie", "35"};
    add_row(table, row1);
    add_row(table, row2);
    add_row(table, row3);
    execute_query(db, "SELECT name FROM users");
    execute_query(db, "INSERT INTO users (id, name, age) VALUES (4, 'David', 40)");
    execute_query(db, "SELECT * FROM users");
    return 0;}
