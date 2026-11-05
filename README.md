# Mini Compiler in C

A lightweight compiler front-end implementation written in **C**, developed as an academic project to explore the fundamental concepts of compiler design, including Lexical Analysis, Syntax Analysis, Tokenization, and Grammar Parsing.

The project implements two versions of a simple programming language:
- **Basic Version:** Supports variable assignments and arithmetic expressions.
- **Advanced Version:** Extends the basic language with conditional statements (`if`, `else`), loops (`while`), comparison operators, and code blocks.

The parser uses the **Recursive Descent Parsing** technique to validate input statements against a predefined grammar.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Compiler Architecture](#compiler-architecture)
- [Language Grammar](#language-grammar)
- [Supported Syntax](#supported-syntax)
- [Getting Started](#getting-started)
- [Compilation and Execution](#compilation-and-execution)
- [Test Cases](#test-cases)
- [Technologies](#technologies)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Academic Purpose](#academic-purpose)

---

## Project Overview

Mini Compiler is an educational project designed to demonstrate how a compiler processes source code at a basic level.

The main objective is to analyze user input, identify individual tokens, and verify whether the input follows the syntax rules of a predefined programming language.

The project focuses on two major stages of compiler design:

1. **Lexical Analysis (Lexer):** Converts source code into a sequence of tokens.
2. **Syntax Analysis (Parser):** Validates the token sequence according to the language grammar.

This implementation focuses on syntax validation rather than executing programs or generating machine code.

---

## Features

### Basic Version

- Variable assignment statements.
- Identifier recognition.
- Integer and decimal number recognition.
- Arithmetic operators:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`)
- Parenthesized expressions.
- Unary positive and negative operators.
- Syntax validation using Recursive Descent Parsing.
- Optional semicolons.

### Advanced Version

Includes all Basic Version features, plus:

- Conditional statements (`if`).
- Alternative branches (`else`).
- Loop statements (`while`).
- Comparison operators:
  - Less than (`<`)
  - Greater than (`>`)
  - Less than or equal (`<=`)
  - Greater than or equal (`>=`)
  - Equal (`==`)
  - Not equal (`!=`)
- Nested statements and blocks using curly braces (`{ }`).
- Multiple statements within a program.

---

## Project Structure

```text
MiniCompiler/
│
├── Basic/
│   ├── lexer.c
│   ├── lexer.h
│   ├── parser.c
│   ├── parser.h
│   └── main.c
│
├── Advanced/
│   ├── lexer.c
│   ├── lexer.h
│   ├── parser.c
│   ├── parser.h
│   └── main.c
│
└── README.md
```

Each version is organized into three main components:

| File | Responsibility |
|---|---|
| `main.c` | Program entry point and input handling |
| `lexer.c` | Implementation of lexical analysis |
| `lexer.h` | Token definitions and lexer declarations |
| `parser.c` | Implementation of syntax analysis |
| `parser.h` | Parser function declarations |

This separation improves code organization, maintainability, and readability.

---

## Compiler Architecture

The application follows a simplified compiler front-end pipeline:

```text
       Source Code
            |
            v
     +-------------+
     |    Lexer    |
     +-------------+
            |
            v
      Token Stream
            |
            v
     +-------------+
     |   Parser    |
     +-------------+
            |
            v
   Syntax Validation
            |
       +----+----+
       |         |
       v         v
     Valid    Invalid
    Syntax    Syntax
```

### 1. Lexical Analysis (Lexer)

The lexer reads the source code character by character and groups characters into meaningful tokens.

For example:

**Input:**

```c
result = x + 25;
```

**Token sequence:**

```text
ID(result)
ASSIGN(=)
ID(x)
PLUS(+)
NUMBER(25)
SEMICOLON(;)
```

The lexer recognizes identifiers, numbers, operators, parentheses, and other supported language symbols.

### 2. Syntax Analysis (Parser)

The parser receives tokens from the lexer and checks whether their arrangement follows the defined grammar.

The project uses Recursive Descent Parsing, a top-down parsing technique in which grammar rules are implemented as individual functions.

Examples of parser functions:

- `parse_primary()`
- `parse_unary()`
- `parse_term()`
- `parse_expression()`
- `parse_assignment()`
- `parse_statement()`
- `parse_condition()`

The parser also handles operator precedence, ensuring that multiplication and division are evaluated structurally before addition and subtraction.

---

## Language Grammar

The following grammar defines the supported language constructs.

### Basic Grammar

```text
assignment  -> id = expression

expression  -> term { (+ | -) term }

term        -> unary { (* | /) unary }

unary       -> (+ | -) primary
             | primary

primary     -> id
             | number
             | ( expression )
```

### Advanced Grammar

The advanced version extends the basic grammar with control-flow statements.

```text
statement   -> assignment
             | if_statement
             | while_statement
             | block

if_statement
            -> if ( condition ) statement
             | if ( condition ) statement
               else statement

while_statement
            -> while ( condition ) statement

block       -> { statement }

condition   -> expression relational_operator expression

relational_operator
            -> <
             | >
             | <=
             | >=
             | ==
             | !=
```

---

## Supported Syntax

### Basic Examples

**Valid Statements:**

```c
x = 10;
```

```c
result = x + y * 5;
```

```c
total = (a + b) * (c - d);
```

```c
value = -10 + 20 / 2;
```

**Invalid Statements:**

```c
10 = x + y;
```

```c
x = y +;
```

```c
x = y * / z;
```

```c
x = (a + b;
```

### Advanced Examples

**Conditional Statement:**

```c
if (x > 10) {
    y = x + 5;
}
```

**Conditional Statement with Else:**

```c
if (x > y) {
    result = x;
} else {
    result = y;
}
```

**While Loop:**

```c
while (counter < 10) {
    counter = counter + 1;
}
```

**Nested Control Structures:**

```c
while (x < 100) {
    if (x > 50) {
        y = x * 2;
    } else {
        y = x + 10;
    }

    x = x + 1;
}
```

---

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C compiler (GCC recommended).
- Visual Studio Code or another C-compatible editor.
- Windows, Linux, or another supported development environment.

This project was developed and tested using **GCC through MSYS2 UCRT64 on Windows**.

### Check GCC Installation

```bash
gcc --version
```

If GCC is not installed, you can install it through MSYS2.

Official website:

https://www.msys2.org/

---

## Compilation and Execution

### Basic Version

Navigate to the Basic directory:

```bash
cd Basic
```

Compile the source files:

```bash
gcc main.c lexer.c parser.c -o MiniCompiler.exe
```

Run the application:

```bash
./MiniCompiler.exe
```

### Advanced Version

Navigate to the Advanced directory:

```bash
cd Advanced
```

Compile the source files:

```bash
gcc main.c lexer.c parser.c -o MiniCompiler_Advanced.exe
```

Run the application:

```bash
./MiniCompiler_Advanced.exe
```

---

## Test Cases

The following examples demonstrate the expected syntax validation behavior.

| Test Case | Input | Expected Result |
|---|---|---|
| 1 | `x = 10 + 20` | Valid |
| 2 | `x = (a + b) * 2` | Valid |
| 3 | `x = y * / z` | Invalid |
| 4 | `25 = x + y` | Invalid |
| 5 | `if (x > 10) y = 5;` | Valid (Advanced) |
| 6 | `while (x < 10) { x = x + 1; }` | Valid (Advanced) |
| 7 | `if (x > ) y = 5;` | Invalid (Advanced) |

---

## Technologies

| Technology | Purpose |
|---|---|
| C | Core implementation |
| GCC | Compilation |
| MSYS2 UCRT64 | Windows development environment |
| Visual Studio Code | Code editing and development |
| Recursive Descent | Parsing technique |

---

## Limitations

This project is an educational compiler front-end and currently focuses on lexical and syntax analysis.

The following features are not implemented yet:

- Abstract Syntax Tree (AST) generation.
- Semantic analysis and type checking.
- Symbol table management.
- Intermediate code generation.
- Machine code generation.
- Runtime execution of source programs.
- Detailed error recovery and line/column diagnostics.

---

## Future Improvements

Potential enhancements include:

- Implementing Abstract Syntax Tree (AST) generation.
- Adding semantic analysis.
- Implementing symbol tables.
- Supporting more data types and language constructs.
- Improving syntax error reporting with line and column information.
- Generating intermediate code.
- Adding automated unit tests.

---

## Academic Purpose

This project was developed as part of a university assignment to explore the fundamental principles of Compiler Design.

It demonstrates practical implementations of:

- Tokenization
- Lexical Analysis
- Context-Free Grammar
- Recursive Descent Parsing
- Syntax Validation
- Operator Precedence

The project provides a foundation for understanding how programming languages are analyzed before execution or code generation.

---

**Author:** Mohammad Amin Taheri

**Language:** C

**Project Type:** Academic / Educational

**Focus:** Compiler Design and Implementation
