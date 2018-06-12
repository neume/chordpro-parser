/** A sub scanner that specializes in scanning chords. Input text is expected to
 *  be enclosed in brackets.
 */
class ChordGroupScanner : public BaseScanner  {
public:
  ChordGroupScanner(string lexeme="") {
    delta = DFAMatrix("lib/scanner/dfa/chord_group");
    in = new stringstream(lexeme);
    accepting_states = 200;
    lexeme2 = lexeme;
  }

  ~ChordGroupScanner() {
    delete in;
  }

  /** It identifies the category of a character
   *  @param ch is the character to be categorized
   *  @return an int that reperesents the category -- The column in our DFA table
   */
  int get_category(char ch) override {
    if ( 'A' <= ch && ch <= 'G') return 0;
    // there is a collition with 1 but that's ok
    if ( ch == 'b' or ch == '#')return 1;
    if ( 'a' <= ch && ch <= 'z') return 2;
    if ( 'A' <= ch && ch <= 'Z') return 2;
    if ( '0' <= ch && ch <= '9') return 4;
    switch (ch) {
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

  /** It returns a token according to its value/state
   *  @param value is the name or identifier of the state
   *  @param lexeme the string representation of the token
   *  @param row is the row number of the lexeme
   *  @param column is the column number of the lexeme
   *  @return an int that reperesents the category -- The column in our DFA table
   */
  Token get_token(int value, string lexeme, int row, int column) override {
    switch(value) {
      case 200: return Token(NOTE, lexeme, row, column);
      case 201: return Token(QUALITY, lexeme, row, column);
      case 203: return Token(ADDS, lexeme, row, column);
      case 202: return Token(CDELIMETER, lexeme, row, column);
      case 204: return Token(OBRACKET, lexeme, row, column);
      case 205: return Token(CBRACKET, lexeme, row, column);
      case 210: return Token(EOF, lexeme, row, column);
      default:  return Token(OTHER, lexeme, row, column);
    }
  }
};
