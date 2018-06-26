#include "base_set.cpp"
#include "first_set.cpp"
#include "follow_set.cpp"
class Parser {
  Scanner * scanner;
  Token lookahead;
  FirstSet first_set;
  FollowSet follow_set;
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
    start_of("song");
    first(SONG);
    output_token();
    feed();
    int ctr = 1;
    while(value == OBRACE or value == LYRIC or value == NEWLINE or value == OBRACKET) {
      feed();
      if(ctr-- == 0) break;
    }
  }
  void feed(){
    start_of("feed");
    first(FEED);
    if(value == OBRACE){
      directive_group();
    } else if ( value == OBRACKET || value == LYRIC) {
      line();
    }
    follow(FEED);
  }
  void line() {
    start_of("line");
    first(LINE);
    int ctr=20;
    while(value == LYRIC or value == OBRACKET) {
      line_feed();
      if(ctr-- == 0) break;
    }
    follow(LINE);

    // if(value == NEWLINE) match(NEWLINE);
    // scan_next();
    // output_token();
  }
  void line_feed() {
    start_of("line_feed");
    first(LINE_FEED);

    if(value == LYRIC) {
      match(LYRIC);
      output_token();
    } else {
      chord_group();
    }
    follow(LINE_FEED);
  }
  void chord_group() {
    start_of("chord_group");
    first(CHORD_GROUP);
    match(OBRACKET);
    match(CBRACKET);
    follow(CHORD_GROUP);
  }
  void directive_group() {
    start_of("directive_group");
    first(DIRECTIVE_GROUP);

    match(OBRACE);
    key_value();
    match(CBRACE);

    follow(DIRECTIVE_GROUP);

  }
  void key_value() {
    start_of("key_value");
    first(KEY_VALUE);
    directive_key();
    match(COLON);
    directive_value();
    follow(KEY_VALUE);
  }
  void directive_key() {
    start_of("directive_key");
    first(DIRECTIVE_KEY);
    match(ID);
    follow(DIRECTIVE_KEY);
  }
  void directive_value() {
    start_of("directive_value");
    first(DIRECTIVE_VALUE);
    while(value == ID) {
      match(ID);
    }
    follow(DIRECTIVE_VALUE);
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
          cout << "Unexpected end of input" << endl;
          exit(1);
        }
      }
      output_token();
      scan_next();
    }
  }
  void first(int production) {
    cout << "Start of first " << production <<endl;
    find_from_set(first_set, production);

  }

  void follow(int production) {
    cout << "Start of follow " << production <<endl;
    find_from_set(follow_set, production);
  }

  void find_from_set(BaseSet &base_set, int production) {
    bool found = false;
    bool skipped = false;
    while(!found) {
      if(base_set.is_included(production, value)) {
        found = true;
        break;
      } else {
        skipped = true;
        if(value == EOF) {
          break;
        }
        cout << "Skipping ------------------";
        output_token();
        scan_next();
      }

    }
  }
  void start_of(string s) {
    cout << "Start of " << s << endl;
  }
};
