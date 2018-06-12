#include "base_scanner.cpp"
#include "directive_scanner.cpp"
#include "chord_group_scanner.cpp"
using namespace std;
class Scanner : public BaseScanner{
  ifstream *in;
  BaseScanner *base_scanner;
  int scanner_state;
public:

  Scanner() {
    delta = DFAMatrix("lib/scanner/dfa/chordpro");
    in = new ifstream("sample.chordpro");
    accepting_states = 100;
  }
  ~Scanner() {
    in->close();
    delete in;
  }
  Token scan() {
    Token token;

    if(scanner_state == 1) {
      token = base_scanner->scan();
      if(token.value == EOF) {
        scanner_state = 0;
        token = scan();
      }
    } else {
      token = process();
      switch(token.value) {
        case CHORDGROUP:
          delete base_scanner;
          base_scanner = new ChordGroupScanner(token.lexeme);
          scanner_state = 1;
          token = base_scanner->scan();
          break;

        case DIRECTIVE:
          base_scanner = new DirectiveScanner(token.lexeme);
          scanner_state = 1;
          token = base_scanner->scan();
          break;
      }
    }
    return token;
  }
  Token process() {
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
      case 'b': return 5; // refactor should be in different state
      case '#': return 5; //
      case ']': return 6;
      case ':': return 7;
      case EOF: return 8;
      case '\n': return 9;
      default: return 1;
    };
    return -1;
  }
  Token get_token(int value, string lexeme, int row, int column) {
    switch(value) {
      case 101: return Token(CHORDGROUP, lexeme, row, column);
      case 102: return Token(DIRECTIVE, lexeme, row, column);
      case 103: return Token(LYRIC, lexeme, row, column);
      case 104: return Token(EOF, lexeme, row, column);
      case 105: return Token(NEWLINE, lexeme, row, column);
      default:  return Token(OTHER, lexeme, row, column);
    }
  }
};
