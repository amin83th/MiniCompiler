#include "parser.h"
#include "lexer.h"

static Token current_token;
static int syntax_error;

static void advance(void)
{
    current_token = lexer_next_token();
}

static int match(TokenType expected)
{
    if (current_token.type != expected) {
        syntax_error = 1;
        return 0;
    }

    advance();
    return 1;
}

static int parse_expression(void);
static int parse_statement(void);

static int parse_primary(void)
{
    if (current_token.type == TOKEN_ID ||
        current_token.type == TOKEN_NUMBER) {
        advance();
        return 1;
    }

    if (current_token.type == TOKEN_LPAREN) {
        advance();

        if (!parse_expression())
            return 0;

        return match(TOKEN_RPAREN);
    }

    syntax_error = 1;
    return 0;
}

static int parse_unary(void)
{
    if (current_token.type == TOKEN_PLUS ||
        current_token.type == TOKEN_MINUS) {
        advance();
    }

    return parse_primary();
}

static int parse_term(void)
{
    if (!parse_unary())
        return 0;

    while (current_token.type == TOKEN_MUL ||
           current_token.type == TOKEN_DIV) {
        advance();

        if (!parse_unary())
            return 0;
    }

    return 1;
}

static int parse_expression(void)
{
    if (!parse_term())
        return 0;

    while (current_token.type == TOKEN_PLUS ||
           current_token.type == TOKEN_MINUS) {
        advance();

        if (!parse_term())
            return 0;
    }

    return 1;
}

static int parse_condition(void)
{
    if (!parse_expression())
        return 0;

    switch (current_token.type) {
        case TOKEN_LESS:
        case TOKEN_GREATER:
        case TOKEN_LESS_EQUAL:
        case TOKEN_GREATER_EQUAL:
        case TOKEN_EQUAL:
        case TOKEN_NOT_EQUAL:
            advance();
            break;

        default:
            syntax_error = 1;
            return 0;
    }

    return parse_expression();
}

static int parse_assignment(void)
{
    if (!match(TOKEN_ID))
        return 0;

    if (!match(TOKEN_ASSIGN))
        return 0;

    if (!parse_expression())
        return 0;

    /* A semicolon separates statements; it may be omitted before '}'. */
    if (current_token.type == TOKEN_SEMICOLON)
        advance();
    else if (current_token.type != TOKEN_RBRACE &&
             current_token.type != TOKEN_END) {
        syntax_error = 1;
        return 0;
    }

    return 1;
}

static int parse_block(void)
{
    if (!match(TOKEN_LBRACE))
        return 0;

    while (current_token.type != TOKEN_RBRACE &&
           current_token.type != TOKEN_END) {
        if (!parse_statement())
            return 0;
    }

    return match(TOKEN_RBRACE);
}

static int parse_if(void)
{
    if (!match(TOKEN_IF))
        return 0;

    if (!match(TOKEN_LPAREN))
        return 0;

    if (!parse_condition())
        return 0;

    if (!match(TOKEN_RPAREN))
        return 0;

    if (!parse_statement())
        return 0;

    if (current_token.type == TOKEN_ELSE) {
        advance();

        if (!parse_statement())
            return 0;
    }

    return 1;
}

static int parse_while(void)
{
    if (!match(TOKEN_WHILE))
        return 0;

    if (!match(TOKEN_LPAREN))
        return 0;

    if (!parse_condition())
        return 0;

    if (!match(TOKEN_RPAREN))
        return 0;

    return parse_statement();
}

static int parse_statement(void)
{
    switch (current_token.type) {
        case TOKEN_ID:
            return parse_assignment();

        case TOKEN_IF:
            return parse_if();

        case TOKEN_WHILE:
            return parse_while();

        case TOKEN_LBRACE:
            return parse_block();

        default:
            syntax_error = 1;
            return 0;
    }
}

int parse_program(void)
{
    syntax_error = 0;
    advance();

    while (current_token.type != TOKEN_END) {
        if (!parse_statement())
            return 0;
    }

    return !syntax_error;
}
