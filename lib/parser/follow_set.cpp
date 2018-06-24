class FollowSet : public BaseSet{
public:
  FollowSet() {
    set = {
      {EOF},                          // SONG
      {OBRACE, LYRIC, OBRACKET, EOF}, // FEED
      {OBRACE, LYRIC, OBRACKET, EOF}, // DIRECTIVE_GROUP
      {CBRACE},                       // KEY_VALUE
      {COLON},                        // DIRECTIVE_KEY
      {CBRACE},                       // DIRECTIVE_VALUE
      {LYRIC, OBRACKET, EOF},
      {LYRIC, OBRACKET, EOF},
      {CBRACKET},
      {CBRACKET},
      {CBRACKET}
    };
  }
};
