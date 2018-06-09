#include <iostream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
#include "token.cpp"
#include "enums.h"
using namespace std;

class BaseScanner {
protected:
  DFAMatrix delta;
  stringstream *in;
  int accepting_states;

public:
  string lexeme2;
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
  void print2() {
    cout << "hello";
  };
  void print() {
    delta.print();
  }

  virtual int get_category(char ch) = 0;
  virtual Token get_token(int value, string lexeme, int row, int column) = 0;
};
