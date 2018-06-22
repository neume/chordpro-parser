#include "first_set.cpp"
class Parser {
  Scanner * scanner;
  Token lookahead;
  FirstSet first_set;
public:
  Parser() {}
  Parser(Scanner *_scanner) {
    scanner = _scanner;
  }
  void parse() {
    // while(true) {
    //   Token token = scanner->scan();
    //   cout << token_string(value) << ": " << lexeme << endl;
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
    cout << token_string(value) << ": " << lookahead.lexeme << endl;
  }
  void song() {
    first(SONG);
    output_token();
    feed();
    while(value == OBRACE or value == LYRIC or value == NEWLINE or value == OBRACKET) {
      feed();
    }
  }
  void feed(){
    first(FEED);
    if(value == OBRACE){
      directive_group();
    } else if ( value == OBRACKET || value == LYRIC) {
      line();
    }

  }
  void line() {
    first(LINE);
    while(value == LYRIC or value == OBRACKET) {
      line_feed();
    }
    if(value == NEWLINE) match(NEWLINE);
    // scan_next();
    // output_token();
  }
  void line_feed() {
    first(LINE_FEED);

    if(value == LYRIC) {
      output_token();
    } else {
      // chord_group();
    }
    scan_next();
  }
  void directive_group() {
    first(DIRECTIVE_GROUP);

    match(ID);
    match(COLON);
    directive_value();
    match(CBRACE);
  }
  void directive_value(){
    first(DIRECTIVE_VALUE);
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
  void first(int production) {
    bool found = false;
    bool skipped = false;
    while(!found) {
      if(first_set.is_included(production, value)) {
        found = true;
        break;
      } else {
        skipped = true;
        if(value == EOF) {
          break;
        }
        scan_next();
      }

    }
  }
};
