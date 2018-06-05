#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dfa_matrix.cpp"
using namespace std;

class Scan {
  static const int NIL = -1;
  DFAMatrix delta;
public:
  Scan() {
    delta = DFAMatrix("dfa_chordpro");
  }
  void print() {
    delta.print();
  }
};
