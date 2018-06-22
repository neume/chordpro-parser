class FirstSet : public BaseSet{
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
};
