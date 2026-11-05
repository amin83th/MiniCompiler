#ifndef LEXER_H
#define LEXER_H

#define TOKEN_TEXT_SIZE 128

typedef enum {
    TOKEN_ID,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_ASSIGN,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char text[TOKEN_TEXT_SIZE];
} Token;

void lexer_init(const char *source);
Token lexer_next_token(void);

#endif
