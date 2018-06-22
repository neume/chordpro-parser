#include "base_set.cpp"
class FollowSet : public BaseSet{
public:
  FollowSet() {
    set = {
      {EOF},
      {OBRACE, LYRIC, OBRACKET, EOF},
      {OBRACE, LYRIC, OBRACKET, EOF},
      {CBRACE},
      {COLON},
      {CBRACE},
      {LYRIC, OBRACKET, EOF},
      {LYRIC, OBRACKET, EOF},
      {CBRACKET},
      {CBRACKET},
      {CBRACKET}
    };
  }
};
