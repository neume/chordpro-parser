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
      {LYRIC, OBRACKET},            // LINE
      {LYRIC, OBRACKET},            // LINE_FEED
      {OBRACKET},                   // CHORD_GROUP
      {NOTE},                       // CHORD
      {QUALITY_DECL, EPSILON},      // QUALITY_DECL
      {ADDITIONS_DECL, EPSILON}     // ADDITIONS_DECL
    };
  }
};
