@echo off
set xparams=-nonet --param glossterm.auto.link 1 --param header.rule 1 --param footer.rule 1 --param html.stylesheet.type text/css --stringparam html.stylesheet "http://www.njames.co.uk/styles/main.css" --param section.autolabel 1 
set xtrans=C:\cygwin\usr\share\docbook-xsl\xhtml\docbook.xsl

set pparams=-nonet --param glossterm.auto.link 1 --stringparam  paper.type  A4 --param header.rule 1 --param footer.rule 1
set ptrans=c:\cygwin\usr\share\docbook-xsl\fo\docbook.xsl

set docStem=batchgen_readme
rem chunker.output.doctype-public chunker.output.doctype-system 

xsltproc %xparams% --output %docStem%.html %xtrans% %docStem%.docbook.xml

set basefile=%docStem%.docbook
xsltproc %pparams% --output %basefile%.fo %ptrans% %basefile%.xml
call C:\bin\fop-0.20.5\fop %basefile%.fo %docStem%.pdf

del *.fo

pause
