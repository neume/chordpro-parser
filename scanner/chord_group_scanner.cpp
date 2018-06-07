#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
#include "token.cpp"
#include "enums.h"
using namespace std;

class ChordGroupScanner {
  static const int NIL = -1;
  DFAMatrix delta;
  ifstream *in;
  int accepting_states;

public:

  ChordGroupScanner() {
    delta = DFAMatrix("dfa_chord_group");
    in = new ifstream("chord_group.chordpro");
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
    if ( 'A' <= ch && ch <= 'G') return 0;
    // there is a collition with 1 but that's ok
    if ( 'a' <= ch && ch <= 'z') return 2;
    if ( 'A' <= ch && ch <= 'Z') return 2;
    if ( '0' <= ch && ch <= '9') return 4;
    switch (ch) {
      case '#': return 1;
      case 'b': return 1;
      case '[': return 5;
      case ']': return 6;
      case ' ': return 3;
      case '/': return 3;
      case '-': return 3;
      case '\n': return 7;
      case EOF: return 7;
      default: cout << "Something is not right: (" << ch << ")" << endl;
    };
    return -1;
  }
  Token get_token(int value, string lexeme, int row, int column) {
    switch(value) {
      case 200: return Token(NOTE, lexeme, row, column);
      case 201: return Token(QUALITY, lexeme, row, column);
      case 202: return Token(ADDS, lexeme, row, column);
      case 203: return Token(CDELIMETER, lexeme, row, column);

      case 204: return Token(OBRACKET, lexeme, row, column);
      case 205: return Token(CBRACKET, lexeme, row, column);
      case 210: return Token(EOF, lexeme, row, column);
      default:  return Token(OTHER, lexeme, row, column);
    }
  }
};
