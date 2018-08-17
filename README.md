# SimpleLexer
Parses through a text file to match lexemes with tokens in both a C++ and ANTLR implementation. 

This lexer reads the following charecters and categorizes the lexemes to the following tokens 
// Character classes
#define LETTER 0
#define DIGIT 1
#define PERIOD 30
#define QUOTE 29
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LEFT_BRACK 27
#define RIGHT_BRACK 28
#define SEMICOLON 100
#define COMMA 60
#define KEYWORD 50
#define FLOAT 41
#define STRING 40

The lexer then prints all of the tokens to the command line.

The C++ implementation can be ran by changing the name of the file in main.cc to the text filing containing the text file to parse.
