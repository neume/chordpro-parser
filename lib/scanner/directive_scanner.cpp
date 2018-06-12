class DirectiveScanner : public BaseScanner {
public:
  DirectiveScanner(string lexeme = ""){
    delta = DFAMatrix("lib/scanner/dfa/directive");
    in = new stringstream(lexeme);
    accepting_states = 300;
  }

  ~DirectiveScanner() {
    delete in;
  }

  /** It identifies the category of a character
   *  @param ch is the character to be categorized
   *  @return an int that reperesents the category -- The column in our DFA table
   */
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

  /** It returns a token according to its value/state
   *  @param value is the name or identifier of the state
   *  @param lexeme the string representation of the token
   *  @param row is the row number of the lexeme
   *  @param column is the column number of the lexeme
   *  @return an int that reperesents the category -- The column in our DFA table
   */
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
