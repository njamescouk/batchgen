@echo off

call ..\bin\doLexYacc.bat

markupgrammar -s -f ..\source\batchgen.y > batchgen.y.html
youtputmarkup -g y.output > batchgen.y.dot
dot -Tjpeg -O batchgen.y.dot

pp readme.md.pp > readme.md
pandoc -c main.css -T batchgen --toc -t html5 -f markdown readme.md > readme.html

sed -n "/Introduction/,/batchgen is a run of the mill/p" readme.md | sed -n /(this/d;$!p > blurb.md
pandoc -c main.css -t html5 -f markdown blurb.md > blurb.html

del y.output

pause
