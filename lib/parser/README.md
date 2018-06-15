# Syntax Analyzer
This folder includes syntax analyzer class that accepts a ```BaseScanner``` type class.
We will traverse the file using recursion instead of maintaining a data structure
to monitor the grammar depth.

## Context Free Grammar
This is the rough design of our grammar. It will change overtime.
```
song -> [directives | line ]+
directives -> OBRACE [key_value] CBRACE
key_value -> ID COLON d_value
d_value -> [ID]+
line -> [LYRIC | chord_group]*
chord_group -> OBRACKET [chord]+ CBRACKET
chord -> NOTE quality additions
quality -> QUALITY | e
additions -> ADDITONS | e
```

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