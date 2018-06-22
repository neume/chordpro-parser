#include <vector>
#include "enums.h"
using namespace std;
class BaseSet {
protected:
  vector <vector <int> > set;

public:
  BaseSet() { }
  void print() {
    for(int i = 0; i < set.size(); i++) {
      for(int j = 0; j < set[i].size(); j++) {
        cout << set[i][j];
      }
      cout << endl;
    }
  }
  bool is_included(int production ,int type) {
    for(int i = 0; i <set[production].size(); i++) {
      if(set[production][i] == type) return true;
    }
    return false;
  }
};
