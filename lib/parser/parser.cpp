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
    scan_next();
    song();
  }

private:
  int value;
  string lexeme;

  /** Scans the next token of the input stream. It modifies the
   *  current lexeme and current value
   */
  void scan_next() {
    lookahead = scanner->scan();
    lexeme = lookahead.lexeme;
    value = lookahead.value;
  }
  /** Returns the token as string
   *  @param value is the numerical value of the token
   *  @return an string representation of the token
   */
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

  /** Outputs the token in TOKEN: LEXEME format */
  void output_token(){
    cout << token_string(value) << ": " << lookahead.lexeme << endl;
  }


  /** The entry point of parser */
  void song() {
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
    first(FEED);
    if(value == OBRACE){
      directive_group();
    } else if ( value == OBRACKET || value == LYRIC) {
      line();
    }
    follow(FEED);
  }

  void line() {
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
    first(CHORD_GROUP);
    match(OBRACKET);
    chord();
    match(CBRACKET);
    follow(CHORD_GROUP);
  }

  void chord() {
    first(CHORD);
    match(NOTE);
    quality_decl();
    additions_decl();
    follow(CHORD);
  }

  void quality_decl() {
    // first(QUALITY_DECL);
    if(value == QUALITY) match(QUALITY);
    // follow(QUALITY_DECL);
  }

  void additions_decl() {
    // first(ADDITIONS_DECL);
    if(value == ADDS) match(ADDS);
    // follow(ADDITIONS_DECL);
  }

  void directive_group() {
    first(DIRECTIVE_GROUP);

    match(OBRACE);
    key_value();
    match(CBRACE);

    follow(DIRECTIVE_GROUP);

  }

  void key_value() {
    first(KEY_VALUE);
    directive_key();
    match(COLON);
    directive_value();
    follow(KEY_VALUE);
  }

  void directive_key() {
    first(DIRECTIVE_KEY);
    match(ID);
    follow(DIRECTIVE_KEY);
  }

  void directive_value() {
    first(DIRECTIVE_VALUE);
    while(value == ID) {
      match(ID);
    }
    follow(DIRECTIVE_VALUE);
  }

  /** Finds and matches the token
    * @params type is the numerical representation of the token
  */
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
  /** First sets synchronizer
    * @params production is the numerical representation of the current production
  */
  void first(int production) {
    find_from_set(first_set, production);
  }

  /** Follow sets synchronizer
    * @params production is the numerical representation of the current production
  */
  void follow(int production) {
    find_from_set(follow_set, production);
  }


  /** The generic token finder based on follow and first sets.
    * @params &base_set the set to be used. It is either first_set or follow_set
    * @params production is the numerical representation of the current production
  */
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
        // cout << "Skipping ------------------";
        // output_token();
        scan_next();
      }

    }
  }
};
