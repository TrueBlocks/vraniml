@echo off
erase tokens.h
erase Lex.cpp
erase Parse.cpp

SET BISON_SIMPLE=d:\graphics\tools\bison124\bison.simple
SET BISON_HAIRY=d:\graphics\tools\bison124\bison.hairy

\graphics\tools\bison124\bison124 -dv Parse.y >file.txt
grep -v "#line" < parse_tab.c > Parse.cpp
move parse_tab.h Tokens.h

\graphics\tools\flex247\flex247 Lex.l >>file.txt
grep -v "unistd" < lexyy.c > temp.fil
grep -v "# line" < temp.fil > Lex.cpp

erase temp.fil
erase lexyy.c
erase parse.out
erase parse_tab.c
erase file.txt
