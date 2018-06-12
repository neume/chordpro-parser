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
  virtual ~BaseScanner() {}
  string lexeme2;

    /** Scans and processes the input until it gets a token
     *  This is the default scanning algorithm. This method can be overriden by
     *  the child class.
     *  @return token a valid input token. It returns 1 token at a time.
     */
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
      if(state >= accepting_states) break;
      lexeme += character;
    }
    (*in).putback(character);
    return get_token(state, lexeme, 0, 0);
  }

  /** Prints the DFA of the scanner
   *  This should be removed in the future
   */
  void print() {
    delta.print();
  }

  /** Virtual methods
  *   These should be implemented by the child class
   */
  virtual int get_category(char ch) = 0;
  virtual Token get_token(int value, string lexeme, int row, int column) = 0;
};
