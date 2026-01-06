#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"

bool check_keyword(char ch[]){
    if (strcmp(ch, "if") == 0) return true;
    else if (strcmp(ch, "while") == 0) return true;
    else if (strcmp(ch, "for") == 0) return true;
    else if (strcmp(ch, "else") == 0) return true;
    else if (strcmp(ch, "elif") == 0) return true;
    else if (strcmp(ch, "int") == 0) return true;
    else if (strcmp(ch, "main") == 0) return true;
    return false;
}

void print_lex(FILE *file) {
    if (!file) {
        perror("File open failed");
        return;
    }

    char temp[50];
    int ch;
    int i = 0;
    temp[0] = '\0';

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '/'){
            ch = fgetc(file);
            if (ch == '/'){
                while((ch = fgetc(file)) != EOF){
                    if (ch == '\n') break;
                    ch = fgetc(file);
                }
            }
            else if (ch == '*'){
                while((ch = fgetc(file)) != EOF){
                    if (ch == '*') break;
                    ch = fgetc(file);
                }
                ch = fgetc(file);
            }
        }

        if (isalpha((unsigned char)ch)) {
            if (i < sizeof(temp) - 1) {
                temp[i++] = ch;
                temp[i] = '\0';
            }
        }
        else if (isdigit(ch)){
            int num = 0;
            while(isdigit(ch) && ch >= '0' && ch <= '9'){
                num *= 10;
                num += (ch - '0');
                ch = fgetc(file);
            }
            printf("Number Value Found: %d\n", num);
            if (ch != EOF) ungetc(ch, file);
        }
        else {
            if (i > 0) {
                if (check_keyword(temp)) {
                    printf("Keyword Found: %s\n", temp);
                }
                else {
                    printf("Identifier Found: %s\n", temp);
                }
                i = 0;
                temp[0] = '\0';
            }

            if (ch == '=') {
                int next = fgetc(file);
                if (next == '='){
                    printf("Comparator Operator: ==\n");
                }
                else {
                    printf("Assignment operator: %c\n", ch);
                    ungetc(next, file);
                }
            }
            else if (ch == '<' || ch == '>'){
                int next = fgetc(file);
                if (next == '='){
                    printf("Comparator Operator: %c=\n", next);
                }
                else {
                    printf("Comparator Operator: %c\n", ch);
                    ungetc(next, file);
                }
            }
            else if (ch == ';'){
                printf("Semicolon Found: ;\n");
            }
            else if (ch == '{'){
                printf("Open curly brackets Found: {\n");
            }
            else if (ch == '}'){
                printf("Closed curly brackets Found: }\n");
            }
            else if (ch == '('){
                printf("Open Paren Found: (\n");
            }
            else if (ch == ')'){
                printf("Closed Paren Found: )\n");
            }
            else if (ch == '"'){
                char output[100];
                output[0] = ch;
                ch = fgetc(file);
                int j = 1;
                while(ch != EOF && ch != '"'){
                    output[j++] = ch;
                    ch = fgetc(file);
                }
                output[j++] = '"';
                output[j] = '\0';
                printf("String Found: %s\n", output);
            }
        }
    }
    if (i > 0 && check_keyword(temp)) {
        printf("Keyword Found: %s\n", temp);
    }
}
