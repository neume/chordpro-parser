# Chordpro Parser
An attempt to rewrite chordproko gem in C++. It should be portable to any device that can run or compile this project.

This program outputs XML or YML files.

## Ruby Gem
A wrapper ruby gem will follow after a working prototype or release candidate is published and soon will be utilized in an existing
`chordproko` gem.

## Setup
There's nothing in it yet. Run this command to try it out.
```sh
make build-and-run
```
## The program
### Lexical Analyzer
The input of this anaylzer is a the raw .chordpro file. It will just (for now) out put on your screen a breakdown of tokens of the said file. Example

Input:
```
{title: Back to me}
[E]Can you feel me
[C#m]See me falling a[F#m-B]way(see me falling away)
```
Output:
```
[Dir  ]:   {title: Back to me}
[Chord]:   [E]
[Lyric]:   Can you feel me
[Chord]:   [C#m]
[Lyric]:   See me falling a
[Chord]:   [F#m-B]
[Lyric]:   way(see me falling away)
```
### Our goal
This program should produce a yml file similar to this.
``` yml
song:
  directive:
    title: Back to me
  line:
    chord:
      E
    lyric:
      Can you feel me
    chord:
      note:
        C#
      quality:
        m
      add:
        7
  line:
    chord:
      C#m
    lyric:
      See me falling a
    chord:
      F#m
    chord:
      B
    lyric:
      way(see me falling away)
```
This generated YML is then consumed by Chordpro formatters to layout a readable song sheet. _(We will design a formatter someday with ruby, java, c++ and others)_
## TODOs
+ Lexical Analyzer
  - Classify
  - On demand execution
+ Syntax Analyzer
+ Intermediate Code Generation or maybe not.
+ Tests
