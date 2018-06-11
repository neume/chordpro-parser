#include "scanner/scanner.cpp"
class ChordproParser {
public:
  void run() {
    Scanner scanner = Scanner();
    // scanner.print();
    while(true) {
      Token token = scanner.scan();
      cout << get_token_string(token.value) << ": " << token.lexeme << endl;
      if (token.value == EOF) {
        break;
      }
    }
  }
  string get_token_string(int value) {
    switch(value) {
      case CHORDGROUP:       return "CHORDGROUP";
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
      case OTHER:         return "OTHER";
      default:          return "DEFAULT";
    }
  }
};
