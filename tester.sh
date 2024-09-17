#!/bin/bash


<<eof <<eof <<eof << eof > file1
<<eof <<eof <<eof << eof > file1 | ls
<<eof <<eof <<eof << eof > file1 | <<eof <<eof <<eof << eof > file1
<<eof <<eof <<eof << eof > file1 | cat 
<<eof <<eof <<eof << eof > file1 | <<eof <<eof <<eof << eof > file1 | cat >> file2
<<eof <<eof <<eof << eof > file1 | < cat >file2
rm file1 file2
cat <<eof <<eof <<eof << eof > file1 | <<eof <<eof <<eof << eof > file1 | cat >> file2

< file1 echo > file1 > file 2
all buittin with input file to check what happens .

grep this << eof this should grep the inputfile
if inputfile and cat do not use the input redir but rather read from the heredoc .. order matters
and then decided which input it should use < or << 

cat << eof >file.txt  << eof | cat

cat >file.txt << eof  << eif | cat
cat << eof >> file | cat << eof