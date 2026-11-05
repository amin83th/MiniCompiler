#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

#define INPUT_SIZE 4096

int main(void)
{
    char input[INPUT_SIZE];

    printf("Mini Compiler - Basic Version\n");
    printf("Enter an assignment (example: x = (y + 2) * 3):\n> ");

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
