# Lexical Analyzer
This section scans a source file and classifies group of characters into a token type.

## Our problem
Our analyzer should identify if a ```word``` or ```group of words``` is a ```lyric``` or a ```chord```.
It should analyze ```[C#m]See me falling a[F#m-B]way``` as:
``` yml
obracket: "["
note: "C#"
quality: "C#"
cbracket: "]"
lyric: "See me falling a"
obracket: "["
note: "F#"
quality: "m"
delim: "-"
note: "B"
cbracket: "]"
lyric: "way"
```
But because ```C#m``` is a ```lyric``` and ```[C#m]``` is a ```obracket```, ```note```, ```quality``` and a ```cbracket```, we coudn't design a DFA that correctly identifies it.

## Our solution
We will design an analyzer that analyzes the main input and the lexeme of the token if necessary.

Let us define token object first. A ```token``` object has a ```lexeme: string```, ```token_type: [regular, composite]``` and ```name: [chord, lyric, obracket, ...]```.

If the token is ```composite```, the analyzer will push it to a buffer and analyzes its ```lexeme```. It will return the name of the token before it proceeds to the first token of the lexeme.

We should manage a stack of lexemes to be analyzed. It will serve as the analyzer's todo list. We could have design it recursively to eliminate the stack but I don't think it can support the ```on demand processing``` of our input file. 
