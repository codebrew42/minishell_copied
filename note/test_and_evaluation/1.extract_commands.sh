#!/bin/bash

# Extract commands from the test cases
#ver1
#grep '^- ' 1.test_cases_commands.md > 1.only_commands.txt
#grep '^- ' 1.test_cases_commands.md | sed 's/- //g; s/`//g' > 1.only_commands.txt

awk '/^- / {print} /# eof/ {exit}' 1.test_cases_commands.md | sed 's/- //g; s/`//g' > 1.only_commands.txt
echo "Extracted commands from 1.test_cases_commands.md to 1.only_commands.txt"


<<COMMENT
Explanation:
awk '/^- / {print} /# eof/ {exit}' 1.test_cases_commands.md:
awk processes each line of the file.
/- / {print}: Prints lines starting with - .
/# eof/ {exit}: Stops processing when a line containing # eof is encountered.
| sed 's/- //g; s///g': The output from awk is piped to sed, which removes - and from the lines.
> 1.only_commands.txt: Redirects the final output to 1.only_commands.txt.
This command sequence will extract lines starting with - , stop when # eof is encountered, remove the - and characters, and save the cleaned lines to 1.only_commands.txt.
COMMENT