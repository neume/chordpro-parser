# Syntax Analyzer
This folder includes syntax analyzer class that accepts a ```BaseScanner``` type class.

# Context Free Grammar
This is the rough design of our grammar. It will change overtime.
```
song -> [directives | line ]+
directives -> OBRACE [key_value] CBRACE
key_value -> ID COLON ID
line -> [LYRIC | chord_group]*
chord_group -> OBRACKET [chord]+ CBRACKET
chord -> NOTE quality additions
quality -> QUALITY | e
additions -> ADDITONS | e
```
