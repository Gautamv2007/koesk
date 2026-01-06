#include <stdio.h>
#include <stdbool.h>

char stack[100];
int top = 0;

void push(char c){
    if(top >= 100){
        printf("Stack overflow\n");
        return;
    }
    stack[top++] = c;
}

char pop(){
    if(top <= 0){
        return '\0';
    }
    return stack[--top];
}

char peek(){
    if(top <= 0) return '\0';
    return stack[top - 1];
}

int line_stack[100];
int t = 0;
void push_l(int n){
    stack[t++] = n;
}

int pop_l(){
    return line_stack[--t];
}

int peek_l(){
    return line_stack[t-1];
}

void check_paren(FILE *file){
    int count = 1;
    int ch;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n') count++;
        
        if (ch == '(' || ch == '{' || ch == '['){
            push(ch);
            push_l(count);
        }
        else if (ch == ')' || ch == '}' || ch == ']'){
            char temp = peek();
            if ((temp == '(' && ch == ')') ||
                (temp == '{' && ch == '}') ||
                (temp == '[' && ch == ']')) {
                pop();
                pop_l();
            } else {
                printf("The bracket in line %d is not closed...ERROR\n", peek_l());
                return;
            }
        }
    }

    if(top != 0){
        printf("Some brackets were not closed...ERROR\n");
    } else {
        printf("Paren checking is done. All the paren are closed properly\n");
    }
}
