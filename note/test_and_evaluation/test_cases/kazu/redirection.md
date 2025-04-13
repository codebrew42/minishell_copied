# test cases / redirection

input: infile

output: outfile

## <>
```shell
# simple cases
echo hello > outfile
< infile cat
cat infile > outfile
< infile cat | grep f > outfile

#with more space
echo hello                     > outfile
echo hello >                    outfile

# more redirection
ls > outfile > outfile2
ls >> outfile >> outfile2
echo hello >> world >> ! > outfile

# more files
<file1 cat <file2 <file3
# checking if inside of the files are changed
cat file1
cat file2
cat file3

< file1 > file2 cat >> file3


#with more pipe
< infile cat | grep f | wc -l > outfile

# no command
< infile "" | grep f > outfile
<infile cat | "" > outfile
< file1 cat | "" | wc -l > outfile
< infile cat | grep f | "" > outfile

# no file
< "" cat | grep f > outfile
< "" cat | grep f | wc -l > outfile
< infile cat | grep f > ""
< infile cat | grep f | wc -l > ""
< infile cat | grep f | wc -l > ""

#not existing command
< infile notexist | grep f > outfile
< infile cat | notexist > outfile

# all empty
< "" "" | "" > ""
< "" "" | "" | "" > ""
```

## <<>> append

---
