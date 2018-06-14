#include "scanner/scanner.cpp"
#include "parser/parser.cpp"
enum { CFILE, STRING };
class ChordproParser {
  string source;
  int type;
public:
  ChordproParser() {}
  ChordproParser(string _source, int _type=CFILE) {
    source = _source;
    type = _type;
  }
  void run() {
    Scanner *scanner = new Scanner();
    Parser parser = Parser(scanner);
    // Translator translator = Translator(Parser);

    parser.parse();
  }
};
