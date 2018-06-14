#include "scanner/scanner.cpp"
#include "parser/parser.cpp"
class ChordproParser {
public:
  void run() {
    Scanner *scanner = new Scanner();
    Parser parser = Parser(scanner);
    // scanner.print();
    parser.parse();
  }
};
