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

static int parse_assignment(void)
{
    if (!match(TOKEN_ID))
        return 0;

    if (!match(TOKEN_ASSIGN))
        return 0;

    if (!parse_expression())
        return 0;

    /* Semicolon is optional in the basic version. */
    if (current_token.type == TOKEN_SEMICOLON)
        advance();

    return 1;
}

int parse_program(void)
{
    syntax_error = 0;
    advance();

    if (!parse_assignment())
        return 0;

    return !syntax_error && current_token.type == TOKEN_END;
}
