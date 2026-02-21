#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"


typedef struct PARSER_STRUCT
{
    lexer_T* lexer;
    token_T* current_token;
} parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int token_type); /*This function expects a certain token. If it doesn't get the expected token it just dies.
If we get the correct token we eat and advance to the next token*/

AST_T* parser_parse(parser_T* parser); //This parser will return the whole code as a AST_TREE 

AST_T* parser_parse_statement(parser_T* parser);

AST_T* parser_parse_statements(parser_T* parser);

AST_T* parser_parse_expr(parser_T* parser); /*expressions are for the whole result. ex: 1 + 3 * 7 */

AST_T* parser_parse_factor(parser_T* parser); /*factors are things that you multiply. ex: 1*2*(3+4) */

AST_T* parser_parse_term(parser_T* parser); /*terms are things that you add ex: 1 + 2 + (3*4) */

AST_T* parser_parse_function_call(parser_T* parser);

AST_T* parser_parse_variable(parser_T* parser);

AST_T* parser_parse_string(parser_T* parser);

#endif