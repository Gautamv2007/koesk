#include <stdio.h>
#include "lexer.h"
#include "paren_checker.h"

int main(){
    FILE *fp = fopen("sample.tac", "r");
    if (!fp){
        perror("fopen");
        return 1;
    }
    //print_lex(fp);
    check_paren(fp);
    fclose(fp);
    return 0;
}