#include <vector>
using namespace std;
class FirstSet {
  vector <vector <int> > set;

public:
  FirstSet() {
    set = {
      {OBRACE, LYRIC, OBRACKET},
      {OBRACE, LYRIC, OBRACKET},
      {ID},
      {ID},
      {ID},
      {LYRIC, OBRACKET},
      {LYRIC, OBRACKET},
      {OBRACKET},
      {NOTE},
      {QUALITY_DECL, EPSILON},
      {ADDITIONS_DECL, EPSILON}
    };
  }
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
