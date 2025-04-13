#!/bin/bash

# Set the output filename to always be code_compressed.txt in current directory
OUTPUT_FILE="code_compressed.txt"

# Hardcoded file list

# FILES=(
# 	"../src/signal/signal.c"
# 	"../src/signal/signal_util.c"
#     "../src/main.c"
# 	"../src/executor/executor.c"
# 	"../src/heredoc/heredoc.c"
# 	"../src/heredoc/heredoc_util.c"
#     "../include/minishell.h"
#     "../include/err.h"
#     "../include/sig_handler.h"
# 	"../include/executor.h"
# 	"../include/heredoc.h"
#     "../Makefile"
# )

FILES=(
	"../src/parser/parser.c"
	"../src/parser/util_cmd_with_redir.c"
	"../src/parser/util_save_to_ast.c"
	"../src/parser/util_type_check.c"
	"../src/parser/validate_linked_op.c"
	"../src/parser/validate_single_op.c"
	"../src/tokenizer/handle_operator.c"
	"../src/tokenizer/handle_word.c"
	"../src/tokenizer/tokenizer.c"
	"../src/tokenizer/valid_tk.c"
	"..src/expander/handle_qot_envvar.c"
	"../src/expander/ev_expander_utils.c"
	"../src/expander/util_check_qot.c"
	"../src/expander/envvar_expander.c"
    "../src/main.c"
	"../src/executor/executor.c"
    "../include/minishell.h"
    "../include/parser.h"
	"../include/tokenizer.h"
	"../include/executor.h"
    "../Makefile"
)

# FILES=(

#     "src/tokenizer/handle_operator.c"
#     "src/tokenizer/handle_word.c"
#     "src/tokenizer/tokenizer.c"
# 	"src/tokenizer/valid_tk.c"
# 	"src/parser/parser.c"
# 	"src/parser/util_cmd_with_redir.c"
# 	"src/parser/util_save_to_ast.c"
# 	"src/parser/util_type_check.c"
# 	"src/parser/validate_linked_op.c"
# 	"src/parser/validate_single_op.c"
# 	"src/expander/handle_qot_envvar.c"
# 	"src/expander/ev_expander_utils.c"
# 	"src/expander/util_check_qot.c"
# 	"src/expander/envvar_expander.c"
# 	"src/signal/signal.c"
#     "src/main.c"
# 	"src/err/err_handler.c"
#     "src/init/init.c"
#     "src/ms_free/free_ms.c"
# 	"src/ms_free/free_ms_utils.c"
# 	"src/executor/executor.c"
# 	"src/executor/exec_utils.c"
# 	"src/executor/exec_utils2.c"
# 	"src/executor/exec_builtin.c"
# 	"src/executor/exec_cmdproc.c"
# 	"src/executor/exec_stream.c"
#     "include/minishell.h"
#     "include/tokenizer.h"
#     "include/init.h"
#     "include/err.h"
#     "include/sig_handler.h"
#     "Makefile"
# )

# Check if any files exist
if [ ${#FILES[@]} -eq 0 ]; then
    echo "No files specified in the script."
    exit 1
fi

# Process the first file (using > to create/overwrite the output file)
FIRST_FILE="${FILES[0]}"
FIRST_FILENAME=$(basename "$FIRST_FILE")
echo "$FIRST_FILENAME" > "$OUTPUT_FILE"
cat "$FIRST_FILE" >> "$OUTPUT_FILE"

# Process the remaining files (using >> to append)
for ((i=1; i<${#FILES[@]}; i++)); do
    FILE="${FILES[$i]}"
    FILENAME=$(basename "$FILE")
    echo "$FILENAME" >> "$OUTPUT_FILE"
    cat "$FILE" >> "$OUTPUT_FILE"
done

echo "All files have been compiled into $OUTPUT_FILE"