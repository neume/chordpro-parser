#include <iostream>
#include <fstream>
using namespace std;
const int NIL = -1;
int get_category(char);
string get_state_token(int);
int main() {
  int delta[10][10] = {
    /*          0    1    2    3    4    5    6    7    8    9 */
    /*          s    a    0    {    }    [    ]    :  EOF   \n */
    /*  0 */ {  6,   6,   6,   3,   6,   1,   6,   6, 104,   9},
    /*  1 */ {  1,   1,   1,   1,   1,   1,   2,   1, 104, 105},
    /*  2 */ {101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
    /*  3 */ {  3,   3,   3,   3,   3,   3,   3,   4, 104, 105},
    /*  4 */ {  4,   4,   4,   4,   5,   4,   4,   4, 104, 105},
    /*  5 */ {102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
    /*  6 */ {  6,   6,   6, 103,   6, 103,   6,   6, 103, 103},
    /*  7 */ {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, 104, 105},
    /*  8 */ {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, 104, 105},
    /*  9 */ {105, 105, 105, 105, 105, 105, 105, 105, 104, 105},
  };

  ifstream in;
  in.open("sample.chordpro");
  bool eof = false;
  int ctr = 0;
  char character;
  while(true) {
    string lexeme = "";
    int character, state = 0;
    while(true) {
      ctr+= 1;
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
