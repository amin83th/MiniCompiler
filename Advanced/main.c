#include <stdio.h>
#include "lexer.h"
#include "parser.h"

#define INPUT_SIZE 4096

int main(void)
{
    char input[INPUT_SIZE];

    printf("Mini Compiler - Advanced Version\n");
    printf("Enter a statement or a program:\n");
    printf("Example: if (x > 10) { y = x + 1; }\n> ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }

    lexer_init(input);

    if (parse_program())
        printf("Valid Syntax!\n");
    else
        printf("Invalid Syntax!\n");

    return 0;
}
