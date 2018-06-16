class Parser {
  Scanner * scanner;
  Token lookahead;
public:
  Parser() {}
  Parser(Scanner *_scanner) {
    scanner = _scanner;
  }
  void parse() {
    // while(true) {
    //   Token token = scanner->scan();
    //   cout << get_token_string(token.value) << ": " << token.lexeme << endl;
    //   if (token.value == EOF) {
    //     break;
    //   }
    // }
    scan_next();
    song();
  }

private:
  int value;
  string lexeme;
  void scan_next() {
    lookahead = scanner->scan();
    lexeme = lookahead.lexeme;
    value = lookahead.value;
  }
  string token_string(int value) {
    switch(value) {
      case CHORDGROUP:  return "CHORDGROUP";
      case LYRIC:       return "LYRIC";
      case NEWLINE:     return "NEWLINE";
      case DIRECTIVE:   return "DIRECTIVE";
      case CBRACKET:    return "CBRACKET";
      case OBRACKET:    return "OBRACKET";
      case ADDS:        return "ADDS";
      case CDELIMETER:  return "CDELIMETER";
      case QUALITY:     return "QUALITY";
      case NOTE:        return "NOTE";
      case OBRACE:      return "OBRACE";
      case CBRACE:      return "CBRACE";
      case SPACE:       return "SPACE";
      case COLON:       return "COLON";
      case ID:          return "ID";
      case EOF:         return "EOF";
      case OTHER:       return "OTHER";
      default:          return "DEFAULT";
    }
  }
  void output_token(){
    cout << token_string(value) << ": " << lexeme << endl;
  }
  void song() {
    output_token();
    while(value != OBRACE or value != LYRIC or value != NEWLINE or value != OBRACKET or value != EOF) {

      feed();
       scan_next();
      // scan_next();
    }
  }
  void feed(){
    if(value == OBRACE) {
      directive();
      scan_next();
    } else if ( value == OBRACKET || value == LYRIC) {
      line();
    }

  }
  void line() {
    while(value == LYRIC or value == OBRACKET) {
      line_feed();
    }
    if(value == NEWLINE) match(NEWLINE);
    // scan_next();
    // output_token();
  }
  void line_feed() {
    if(value == LYRIC) {
      output_token();
    } else {
      // chord_group();
    }
    scan_next();
  }
  void directive() {
    match(ID);
    match(COLON);
    d_value();
    match(CBRACE);
  }
  void d_value(){
    while(value == ID or value == SPACE) {
      output_token();
      scan_next();
    }
  }

  void match(int type) {
    if(value == type) {
      output_token();
      scan_next();
    } else {
      while(value != type) {
        scan_next();
        if (value == EOF)
        {
          cout << "EOI" << endl;
          exit(1);
        }
      }
      output_token();
      scan_next();
    }
  }

};
