class FollowSet : public BaseSet{
public:
  FollowSet() {
    set = {
      {EOF},                          // SONG
      {OBRACE, LYRIC, OBRACKET, EOF}, // FEED
      {OBRACE, LYRIC, OBRACKET, EOF}, // DIRECTIVE_GROUP
      {ID, CBRACE},                   // KEY_VALUE
      {COLON},                        // DIRECTIVE_KEY
      {ID, CBRACE},                   // DIRECTIVE_VALUE
      {LYRIC, OBRACKET, EOF},         // LINE
      {LYRIC, OBRACKET, EOF},         // LINE_FEED
      {LYRIC, OBRACKET, EOF},         // CHORD_GROUP
      {CBRACKET},                     // CHORD
      {CBRACKET},                     // QUALITY_DECL
      {CBRACKET}                      // ADDITIONS_DECL
    };
  }
};
