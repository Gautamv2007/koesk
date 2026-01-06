#include <stdio.h>
#include "lexer.h"

int main(){
    FILE *fp = fopen("sample.tac", "r");
    if (!fp){
        perror("fopen");
        return 1;
    }
    print_lex(fp);

    fclose(fp);
    return 0;
}