struct Token {
  int value;
  string lexeme;
  int row, column;
  Token() {}
  Token (int _value, string _lexeme, int _row, int _column) {
    value  = _value;
    lexeme = _lexeme;
    row    = _row;
    column = _column;
  }
};
