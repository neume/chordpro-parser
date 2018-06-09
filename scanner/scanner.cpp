#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
#include "token.cpp"
#include "enums.h"
using namespace std;

class Scanner {
  static const int NIL = -1;
  DFAMatrix delta;
  ifstream *in;
  int accepting_states;

public:

  Scanner() {
    delta = DFAMatrix("scanner/dfa/chordpro");
    in = new ifstream("sample.chordpro");
    accepting_states = 100;
  }

  Token scan() {
    string lexeme = "";
    char character;
    int state = 0;
    bool eof = false;
    while(true) {
      character = (*in).get();
      int category = get_category(character);
      state = delta[state][category];
      // Accepting state
      if(state > accepting_states) break;
      lexeme += character;
    }
    (*in).putback(character);
    return get_token(state, lexeme, 0, 0);
  }

  void print() {
    delta.print();
  }

  int get_category(char ch) {
    if ( 'a' <= ch && ch <= 'z') return 1;
    if ( 'A' <= ch && ch <= 'Z') return 1;
    if ( '0' <= ch && ch <= '9') return 2;
    switch (ch) {
      case ' ': return 0;
      case ',': return 1;
      case '{': return 3;
      case '}': return 4;
      case '[': return 5;
      case ']': return 6;
      case ':': return 7;
      case EOF: return 8;
      case '\n': return 9;
      default: cout << "Something here: (" << ch << ")" << endl;
    };
    return -1;
  }
  Token get_token(int value, string lexeme, int row, int column) {
    switch(value) {
      case 101: return Token(CHORD, lexeme, row, column);
      case 102: return Token(DIRECTIVE, lexeme, row, column);
      case 103: return Token(LYRIC, lexeme, row, column);
      case 104: return Token(EOF, lexeme, row, column);
      case 105: return Token(NEWLINE, lexeme, row, column);
      default:  return Token(OTHER, lexeme, row, column);
    }
  }
};
