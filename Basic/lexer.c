#include "lexer.h"
#include <ctype.h>
#include <stddef.h>

static const char *source;
static size_t position;

void lexer_init(const char *input)
{
    source = input;
    position = 0;
}

Token lexer_next_token(void)
{
    Token token = { TOKEN_INVALID, "" };
    size_t i = 0;

    while (source[position] != '\0' &&
           isspace((unsigned char)source[position])) {
        position++;
    }

    char current = source[position];

    if (current == '\0') {
        token.type = TOKEN_END;
        return token;
    }

    if (isalpha((unsigned char)current) || current == '_') {
        while (isalnum((unsigned char)source[position]) ||
               source[position] == '_') {
            if (i < TOKEN_TEXT_SIZE - 1)
                token.text[i++] = source[position];
            position++;
        }
        token.text[i] = '\0';
        token.type = TOKEN_ID;
        return token;
    }

    if (isdigit((unsigned char)current)) {
        while (isdigit((unsigned char)source[position])) {
            if (i < TOKEN_TEXT_SIZE - 1)
                token.text[i++] = source[position];
            position++;
        }

        if (source[position] == '.' &&
            isdigit((unsigned char)source[position + 1])) {
            if (i < TOKEN_TEXT_SIZE - 1)
                token.text[i++] = source[position];
            position++;

            while (isdigit((unsigned char)source[position])) {
                if (i < TOKEN_TEXT_SIZE - 1)
                    token.text[i++] = source[position];
                position++;
            }
        }

        token.text[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    token.text[0] = current;
    token.text[1] = '\0';
    position++;

    switch (current) {
        case '+': token.type = TOKEN_PLUS; break;
        case '-': token.type = TOKEN_MINUS; break;
        case '*': token.type = TOKEN_MUL; break;
        case '/': token.type = TOKEN_DIV; break;
        case '=': token.type = TOKEN_ASSIGN; break;
        case '(': token.type = TOKEN_LPAREN; break;
        case ')': token.type = TOKEN_RPAREN; break;
        case ';': token.type = TOKEN_SEMICOLON; break;
        default:  token.type = TOKEN_INVALID; break;
    }

    return token;
}
