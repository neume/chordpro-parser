#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
using namespace std;

class Scan {
  static const int NIL = -1;
  DFAMatrix delta;
public:
  Scan() {
    delta = DFAMatrix("dfa_chordpro");
  }
  int process() {
    ifstream in;
    in.open("../sample.chordpro");
    bool eof = false;
    int ctr = 0;
    char character;
    while(true) {
      string lexeme = "";
      int character, state = 0;
      while(true) {
        character = in.get();
        int category = get_category(character);
        // cout << int(category)  <<":" << character << ":" << ctr << endl;
        state = delta[state][category];
        if(character == '\n' )
        ; // cout << "newline";
        if(state == 0) break;
        if(state == 104) eof = true;
        if(state > 100) break;
        lexeme += character;
      }
      string token = get_state_token(state);
      if(token != "Newln" and token != "EOF   ")
        cout << "[" << token << "]:   " << lexeme << endl;
      if(eof) {
        // cout << "breaked!";
        break;
      }
      in.putback(character);
    }

    return 0;
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
  string get_state_token(int state) {
    switch(state) {
      case 101: return "Chord";
      case 102: return "Dir  ";
      case 103: return "Lyric";
      case 104: return "EOF  ";
      case 105: return "Newln";
      default:  return "Other";
    }
  }
};
