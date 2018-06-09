#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
#include "token.cpp"
#include "enums.h"
using namespace std;

class DirectiveScanner {
  static const int NIL = -1;
  DFAMatrix delta;
  ifstream *in;
  int accepting_states;

public:

  DirectiveScanner() {
    in = new ifstream("directive.chordpro");
    delta = DFAMatrix("dfa/directive");
    accepting_states = 200;
  }

  Token scan() {
    // cout << "debug: --------------" << endl;
    string lexeme = "";
    char character;
    int state = 0;
    bool eof = false;
    while(true) {
      // cout << "\tdebug: --------------" << state << endl;
      character = (*in).get();
      int category = get_category(character);
      state = delta[state][category];
      // Accepting state
      if(state >= accepting_states) break;
      lexeme += character;
      // cout << character << "[" << int(character) << "]";

    }
    (*in).putback(character);
    return get_token(state, lexeme, 0, 0);
  }

  void print() {
    delta.print();
  }

  int get_category(char ch) {
    if ( 'a' <= ch && ch <= 'z') return 0;
    if ( 'A' <= ch && ch <= 'Z') return 0;
    if ( '0' <= ch && ch <= '9') return 0;
    switch (ch) {
      case '_': return 0;
      case ':': return 1;
      case ' ': return 2;
      case '{': return 3;
      case '}': return 4;
      case '\n': return 5;
      case EOF: return 5;
      default: cout << "Something is not right: (" << ch << ")" << endl;
    };
    return -1;
  }
  Token get_token(int value, string lexeme, int row, int column) {
    switch(value) {
      case 300: return Token(ID, lexeme, row, column);
      case 301: return Token(COLON, lexeme, row, column);
      case 302: return Token(SPACE, lexeme, row, column);
      case 303: return Token(OBRACE, lexeme, row, column);
      case 304: return Token(CBRACE, lexeme, row, column);
      case 310: return Token(EOF, lexeme, row, column);
      default:  return Token(OTHER, lexeme, row, column);
    }
  }
};
