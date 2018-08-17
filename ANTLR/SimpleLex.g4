lexer grammar SimpleLex;

// Skip white space
WS: [ \t\n\r]+ -> skip;

// Simple tokens
LEFT_PAREN:  '(';
RIGHT_PAREN: ')';
ADD_OP:      '+';
SUB_OP:      '-';
MULT_OP:     '*';
DIV_OP:      '/';

// Identifiers and integer literals
IDENT:    LETTER (LETTER | DIGIT)*;
INT_LIT:  DIGIT+;

// Fragments used in above rules, these do not
// define tokens, instead they are just fragments
// used by other token definitions.
fragment LETTER: [a-zA-Z];
fragment DIGIT:  [0-9];
