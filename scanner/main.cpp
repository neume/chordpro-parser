#include <iostream>
#include "scan.cpp"
using namespace std;
string get_token_string(int value) {
  switch(value) {
    case CHORD:       return "CHORD";
    case LYRIC:       return "LYRIC";
    case NEWLINE:     return "NEWLINE";
    case DIRECTIVE:   return "DIRECTIVE";
    case EOF:         return "EOF";
    default:          return "DEFAULT";
  }
}
int main() {
  Scan scanner = Scan();
  // scanner.print();
  while(true) {
    Token token = scanner.scan();
    cout << get_token_string(token.value) << ": " << token.lexeme << endl;
    if (token.value == EOF) {
      break;
    }
  }
  // scanner.process();
}
