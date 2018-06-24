# Syntax Analyzer
This folder includes syntax analyzer class that accepts a ```BaseScanner``` type class.
We will traverse the file using recursion instead of maintaining a data structure
to monitor the grammar depth.

## Context Free Grammar
This is the rough design of our grammar.  I forgot how should the grammar will end up like. This is the best iteration for now. It will change overtime.
``` ruby
:song -> :feed+
:feed -> :directive_group | :line
:directive_group -> OBRACE [:key_value] CBRACE
:key_value -> :directive_key COLON :directive_value
:directive_key -> ID
:directive_value -> [ID]+
:line -> :line_feed*
:line_feed -> LYRIC | :chord_group
:chord_group -> OBRACKET [:chord]+ CBRACKET
:chord -> NOTE :quality_decl :additions_decl
:quality_decl -> QUALITY | e
:additions_decl -> ADDITONS | e
```
### First Sets
``` ruby
:song =[OBRACE, LYRIC, OBRACKET]
:feed = [OBRACE, LYRIC, OBRACKET]
:directive_group = [OBRACE, LYRIC, OBRACKET]
:key_value =[ID]
:directive_key = [ID]
:directive_value = [ID]
:line = [LYRIC, OBRACKET]
:line_feed = [LYRIC, OBRACKET]
:chord_group = [OBRACKET]
:chord = [NOTE]
:quality_decl = [QUALITY, e]
:additions_decl = [ADDITIONS, e]
```
These sets are necessary to synchronize the parser head to the next expected token or symbol.
### Follow Sets
``` ruby
:song = [EOF]
:feed = [OBRACE, LYRIC, OBRACKET, EOF]
:directive_group = [OBRACE, LYRIC, OBRACKET, EOF]
:key_value = [CBRACE]
:directive_key = [COLON]
:directive_value = [CBRACE]
:line = [LYRIC, OBRACKET, EOF]
:line_feed = [LYRIC, OBRACKET, EOF]
:chord_group = [LYRIC, OBRACKET, EOF]
:chord = [CBRACKET]
:quality_decl = [CBRACKET]
:additions_decl = [CBRACKET]
```
These two sets of sets may be wrong. I find it hard to understand well the first and follow sets creation instuctions.These sets were created by observation only. I might missed a step to fully list the elements of the sets. I'll review this later.

## Output
This analyzer will output syntax errors if any.

## Translator and Intermediate Code Generator???
I don't know yet if we will include the translator code here or make the analyzer output
data to be used by the translator. Then the translator will pass the data to the ICG.
These are our options:
 + Pass the fully parsed data. The responsibility of the scanner and parser ends here.
   - Using an array or other DS. This might eat some memory.
   - String with delimeters and parse it AGAIN.
 + Parse on demand. Just like our scanner. Return the next data when requested.
  The responsibility of scanner and parser will only end if it meets an End of Input(EOI)
  or error while the Translator is running.
 + Merge all the three here in one class. Parser, Translator and Intermediate Code generator.

Note:
Our translator here is defined as an interface for ICG. ICG may have a specific task,
to generate an XML or YML. It will also  enable other developers to use our parser
as a library and create their own ICG.
