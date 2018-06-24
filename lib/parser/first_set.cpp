class FirstSet : public BaseSet{
public:
  FirstSet() {
    set = {
      {OBRACE, LYRIC, OBRACKET},    // SONG
      {OBRACE, LYRIC, OBRACKET},    // FEED
      {OBRACE, LYRIC, OBRACKET},    // DIRECTIVE_GROUP
      {ID},                         // KEY_VALUE
      {ID},                         // DIRECTIVE_KEY
      {ID},                         // DIRECTIVE_VALUE
      {LYRIC, OBRACKET},
      {LYRIC, OBRACKET},
      {OBRACKET},
      {NOTE},
      {QUALITY_DECL, EPSILON},
      {ADDITIONS_DECL, EPSILON}
    };
  }
};
