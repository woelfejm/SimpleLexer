#include "Lexer.h"
#include "Lexer.cc"

int main() {

  Lexer lex( "test.txt" );  //name of file to parse

  do {
    lex.lex();   // Get next token

    int tok = lex.getNextToken();
    string text = lex.getLexeme();
    printf("Next token is: %d, Next lexeme is %s\n",tok,text.c_str());
  } while( lex.getNextToken() != EOF );

}
