#include <cstdlib>
#include "Lexer.h"
#include <string>
#include <stdio.h>
#include <string.h>
Lexer::Lexer( const string & fileName ): nextToken(EOF), charClass(UNKNOWN), nextChar(' ') {
  inputStream.open( fileName.c_str(), ifstream::in );
}

Lexer::~Lexer() {
  inputStream.close();
}

int Lexer::getNextToken() const {
  return nextToken;
}

string Lexer::getLexeme() const {
  return lexeme;
}

// lookup - a function to lookup operators and parentheses
//          and return the token
int Lexer::lookup(char ch)
{
  switch( ch )
  {
    case '(':
      addChar();
      nextToken=LEFT_PAREN;
      break;
    case ')':
      addChar();
      nextToken=RIGHT_PAREN;
      break;
    case '+':
      addChar();
      nextToken=ADD_OP;
      break;
    case '-':
      addChar();
      nextToken=SUB_OP;
      break;
    case '*':
      addChar();
      nextToken=MULT_OP;
      break;
    case '/':
      addChar();
      nextToken=DIV_OP;
      break;
    case '.':
      addChar();
      nextToken=PERIOD;
      break;
    case '{':
      addChar();
      nextToken=LEFT_BRACK;
      break;
    case '}':
      addChar();
      nextToken=RIGHT_BRACK;
      break;
    case ',':
      addChar();
      nextToken=COMMA;
      break;
    case ';':
      addChar();
      nextToken=SEMICOLON ;
      break;
    case '=':
      addChar();
      nextToken=ASSIGN_OP;
      break;

    default:
      addChar();
      nextToken=EOF;
      break;
  }
  return nextToken;
}

// addChar() - a function to add nextChar to lexeme
void Lexer::addChar()
{
  lexeme.push_back(nextChar);
}

// getChar() - a function to get the next character of
//             input and determine its character class
void Lexer::getChar()
{
  nextChar = inputStream.get();

  if( inputStream.good() ) {
    if( isalpha(nextChar)) charClass=LETTER;
    else if( isdigit(nextChar) ) charClass=DIGIT;
    else if(nextChar == '.') charClass=PERIOD;
    else if(nextChar == '"') charClass=QUOTE;
    else charClass=UNKNOWN;
  } else {
    charClass = EOF;
  }
}

// getNonBlank - a function to call getChar until it
//               returns a non-whitespace character
void Lexer::getNonBlank()
{
  while( isspace(nextChar) ) getChar();
}

//checks if string is a key word
bool Lexer::isKeyWord(){
  const char *reserved[11] ={"if", "else", "for", "do", "while", "switch", "case", "default", "break", "void", "return"};
  const char * s = lexeme.c_str();
  int len = sizeof(reserved)/sizeof(reserved[0]);
  for(int i = 0; i < len; ++i)
  {
      if(!strcmp(reserved[i], s))
      {
          return true;
      }
  }
  //printf("%d",lex.length());
  return false;
}
//method to check if a value is a floating point number
bool Lexer::isFloat(){
  addChar();
  getChar();
  if(charClass != DIGIT) //check at least one digit follows
    return false;
  while( charClass == DIGIT ){  //as many digits can follow the period
    addChar();
    getChar();
  }
  if(nextChar == 'f' || nextChar =='F' ){ //followed by an f
    addChar();
    getChar();
    return true;
  }
  else {//||lookup(nextChar) !=LETTER || lookup(nextChar) !=DIGIT){ //followed by whitespace or semicolo/comma
    return true;
  }
  /*
  else{
    printf("Invalid Float\n");
    exit(1);  //end program
  }
  */
}

// lex() - a simple lexical analyzer
int Lexer::lex()
{
  getNonBlank();
  lexeme = "";
  //printf("CharClass: %d\n", charClass);
  switch( charClass )
  {
    case LETTER:
        addChar();
        getChar();
        while( charClass == LETTER || charClass == DIGIT ){
          addChar();
          getChar();
        }
        if(isKeyWord()){ //check if the identity value is reserved
          nextToken=KEYWORD;
          break;
        }
        nextToken=IDENT;
        break; // identifiers

    case DIGIT:
      addChar();
      getChar();
      while( charClass == DIGIT ){ //stop looping once it since something not a digit
        addChar();
        getChar();
      }
      if(nextChar!= '.'){  //not floating point number
        nextToken=INT_LIT;
        break;
      }  //continue to period

    case PERIOD:
      if(isFloat()){     //check if its a floating point
        nextToken = FLOAT;
        break;
      } //if it isn't a float, program ends
      printf("This message should never appear");
    case QUOTE:
      addChar();
      getChar();
      while(charClass != QUOTE && charClass !=EOF){
        //printf("h");
        addChar();
        getChar();
      }
      addChar();
      getChar();
      nextToken =FLOAT;
      break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break; // Other characters
    case EOF:
        nextToken=EOF;
        lexeme = "EOF";
        break;
  }

  return nextToken;
}
