#include <iostream>
#include "lib/chordpro_parser.cpp"
using namespace std;
int main() {
  ChordproParser parser = ChordproParser();
  parser.run();
  return 0;
}
