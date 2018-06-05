#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class DFAMatrix {
  vector <vector <int> > delta;
public:
  DFAMatrix(){}
  DFAMatrix(string filename) {
    ifstream infile;
    infile.open(filename);
    string line = "";
    // ignore first 3 lines
    getline(infile, line);
    getline(infile, line);
    getline(infile, line);
    while(getline(infile, line)) {
      stringstream sstream;
      sstream << line;
      string tmp;
      int element;
      vector <int> row;
      sstream >> tmp;
      while(sstream >> element) {
        row.push_back(element);
      }
      delta.push_back(row);
    }
  }

  void print() {
    for(int i = 0; i < delta.size(); i++) {
      for(int j = 0; j < delta[i].size(); j++) {
        cout << delta[i][j] << " ";
      }
      cout << endl;
    }
  }
  vector <int> operator [](int index) {
    return delta[index];
  }
};
