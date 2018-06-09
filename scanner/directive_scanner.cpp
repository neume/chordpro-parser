#include "base_scanner.cpp"
using namespace std;

class DirectiveScanner : public BaseScanner {
public:
  DirectiveScanner(string lexeme = ""){
    delta = DFAMatrix("dfa/directive");
    in = new stringstream(lexeme);
    accepting_states = 300;
    cout << lexeme;
  }

  int get_category(char ch) override {
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
  
  Token get_token(int value, string lexeme, int row, int column) override {
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
