#include <iostream>
#include "chord_group_scanner.cpp"
using namespace std;
string get_token_string(int value) {
  switch(value) {
    case CHORD:       return "CHORD";
    case LYRIC:       return "LYRIC";
    case NEWLINE:     return "NEWLINE";
    case DIRECTIVE:   return "DIRECTIVE";
    case CBRACKET:    return "CBRACKET";
    case OBRACKET:    return "OBRACKET";
    case ADDS:        return "ADDS";
    case CDELIMETER:  return "CDELIMETER";
    case QUALITY:     return "QUALITY";
    case NOTE:        return "NOTE";
    case EOF:         return "EOF";
    default:          return "DEFAULT";
  }
}
int main() {
  ChordGroupScanner scanner = ChordGroupScanner();
  // scanner.print();
  int tokens_to_scan = 1000;
  int scanned_token = 0;
  while(true and scanned_token < tokens_to_scan) {
    scanned_token++;
    // cout << "scanned count: " << scanned_token << endl;
    Token token = scanner.scan();
    cout << get_token_string(token.value) << ": " << token.lexeme << endl;
    if (token.value == EOF or token.value == CBRACKET) {
      break;
    }
  }
  // scanner.process();
}
