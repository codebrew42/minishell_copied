
# Minishell To‐Do List

check with [O],[X] or [ ]

## Day 1
- [ ] **Study Pre‑Project Materials**  
  - Reviewed jiyunpar’s pre‑study materials  
    (see: [Minishell Pre‑Study](https://grizzly-touch-858.notion.site/minishell-483e1e34034f42f4b2afeb2ad4b989aa))
- [ ] **Learn Readline Usage**  
  - During input, pressing Ctrl+D does nothing.  
  - When there’s no input, Ctrl+D should exit the minishell.  
  - Fixed the `rl_replace_line` issue (using the detailed path for `-lreadline` removes the “:D” output).
- [ ] **Write the Initial Makefile**  
  - Example command:  
    ```bash
    gcc main.c -lreadline -L/opt/homebrew/opt/readline/lib/ -I/opt/homebrew/opt/readline/include
    ```  
  - this bash command has issue with cursor movement.
  - how to fix it? (Also used ANSI escape sequences like `printf("\033[1A");` and `printf("\033[7C");` to move the cursor on bash.)



## Day 2
- [ ] **Implement a Linked List**
- [ ] **Integrate Readline and History**  
  - Added support for `readline` and `add_history`.
- [ ] **Create a Tree Structure**  
  - Implemented functions: `init_tree`, `make_tree_node`, `push_left`, `push_right`, and `inorder_traverse` (used during tree insertion).



## Day 3
- [ ] **Determine Tree Precedence (Heredoc Handled Separately)**  
  - Precedence order:
    1. `||` and `&&`
    2. `<`, `>`, `>>`, `|`
    3. Commands within parentheses, then command (CMD)
- [ ] **Plan Tree Construction**  
  - Decided to use an expression parser tree approach  
    (see: [Expression Parser Tree](https://ehpub.co.kr/9-3-%ec%88%98%ec%8b%9d-%ed%8c%8c%ec%84%9c-%ed%8a%b8%eb%a6%acnumeric-parser-tree/)).  
  - **Algorithm:**  
    1. If the root’s precedence is greater than or equal to the current operator, attach the current operator as the left child of the root and update the root.  
    2. If the root’s precedence is lower:
       - If the current token is an operator, attach the current operator to the right of the root (after reassigning the root’s right child).  
       - Otherwise, attach it to the rightmost part of the tree.



## Day 4
- [ ] **Outline Overall Project Structure**
  1. **Read Input**
  2. **Analyze Input:**  
     a. Check matching parentheses and quotes.  
     b. Tokenize and expand (handle environment variables and wildcard expansion).  
     c. Perform syntax checking (e.g. ensure no redirection symbols follow a pipe without an argument).  
     d. Parse.
  3. **Execute:** Traverse the reversed tree.
- [ ] **Set Up Testing Infrastructure**  
  - Created a test directory, updated the Makefile, and implemented a unit-test assert function.



## Day 5
- [ ] **Start Tokenization**
  - [ ] Defined a token structure (with value, priority, type).  
  - [ ] Implemented Bash‑like token recognition (processing the input line by line).  
  - [ ] Coded the token recognition functions.  
  - [ ] Added logic and tests for checking parentheses and quotes.



## Day 6
- **Integrate Tokenization with Execution**
  - Fixed the process waiting logic:  
    - Previously, only the last process was waited on; now, all child processes are waited for.
  - **SIGPIPE Handling:**  
    - For example, in `yes | head -2`, ensured that SIGPIPE terminates `yes` by having the parent close extra pipe readers.
  - *Note:* Tested with commands like `$ yes | head -n` (works) and `$ sleep 5 | sleep 1` (needs further adjustment).



## Day 7
- **Continue Tokenization Focusing on Execution**
  - Adjusted the new process waiting logic.
  - Resolved SIGPIPE issues by properly closing pipe file descriptors in the parent process.



## Day 8
- [ ] **Complete Basic Tokenization**
  - Created a function to generate tokens and store them in a list.
  - Implemented reading of quoted strings so that strings like `"||"` are distinguished from the `||` operator.
- *Note:* Resolved issues with shared development environments.



## Day 9
- [ ] **Advance Tokenization Further**
  - [ ] Implemented `is_bracket`.
  - [ ] Implemented `read_bracket_content`.
  - [ ] Implemented `is_dollar`.
  - [ ] **Implement Expansion:**  
    - Expand environment variables (using `getenv`, along with `opendir`/`readdir` for wildcards).
- **Remaining Tasks:**
  1. Complete parsing (approximately 50% done).
  2. Convert tokens into a list.
  3. Insert the list into the parsing tree.
  4. Connect pipes and implement command execution (e.g. `echo` and built-in commands).
  5. Handle signal processing (exit status, Ctrl+D, Ctrl+C, Ctrl+\).



## Day 10
- [ ] **Refine Syntax Error Handling & Tokenization Cases**
- [ ] **Design the Tree Structure for Tokens**
  - Example: In `$echo hello hello hello | ls`, the shell expansion yields multiple “fields” stored in a list and later joined before execution.



## Day 11
- [ ] **Build the Tree from Tokenized Fields**
  - Constructed fields and inserted them into the tree following the defined rules.
- [ ] **Syntax Error Handling:**  
  - Traversed the tree to check for operator nodes missing a child, and flagged these as syntax errors (with tests).



## Day 12
- [ ] **Implement Expansion**
  - Handled environment variables (decided on how to store and pass them).  
  - [ ] Implemented wildcard expansion using `opendir`, `readdir`, and `closedir`.
  - [ ] Still need to implement full `getenv` functionality.
- [ ] **Implement Redirection**
- [ ] **Syntax Error Checks for Duplicate Operators:**  
  - E.g., `<<< infile echo | grep` or repeated redirection symbols.
- [ ] **Quote Removal:**  
  - E.g., in commands like `ls "> abcde" outfile ">"` for proper word splitting.
- [ ] **Begin Execution Logic Implementation**
- [ ] **Handle Expansion of `?`:**  
  - Ensure that `$?` expands to the exit status.



## Day 13–14
- [ ] **Complete Expansion Implementation**
  - Used `getenv` and finalized the expansion logic.
- [ ] **Finish Parsing**
- [ ] **Fix Memory Leaks**
- [ ] **Refactor Functions Over 25 Lines**
- [ ] **Ensure Proper Use of `closedir`**
- [ ] **Update Test Setup:**  
  - Running `make` should swap libft if needed.
- [ ] **Handle `$?` Expansion Correctly**



## Day 15
- [ ] **Check Redirection Errors**
- [ ] **Further Refine Execution Logic**



## Day 16
- [ ] **Develop Execution Logic**
  - [ ] Explained why a tree structure is used.
  - [ ] Considered handling of `||`, `&&`, and parentheses  
    (e.g. `command1 && command2` should run command2 only if command1 succeeds; complex examples provided).
  - [ ] Evaluated subshell handling.
- [ ] **Redirection in Child Processes:**  
  - Redirection is set up in the child process (not the parent).
- [ ] **Prepare Refined Fields:**  
  - Removed quotes and redirection operators, then applied expansion and quote removal.



## Day 17
- [ ] **Begin Full Execution Code Implementation**
  - Created refined fields (for subshells, removed parentheses; child processes handle redirection before calling `execve`).
  - Constructed a two‑dimensional array from the refined list for execution.
  - Considered exit status handling (for `&&` and `||`, the previous process’s exit result determines subsequent execution).
- [ ] **Implement Signal Handling:**  
  - (Handle Ctrl+C, Ctrl+D, etc.)
- [ ] **Implement Built‑in Commands**



## Day 18
- [ ] **Finish Execution Code**
  - [ ] Implement full redirection handling.
  - [ ] Process subshell arguments.
  - [ ] Ensure the minishell executes commands correctly.
- [ ] **Additional:**  
  - Validate syntax errors for unmatched `||` or `&&`.



## Day 19
- [ ] **Continue Execution Code Development**
  - [ ] Implemented redirection handling.
  - [ ] Processed subshell arguments.
  - [ ] Ensure the minishell executes commands correctly.
- [ ] **Additional:**  
  - Check for syntax errors with unmatched `||` or `&&`.



## Day 20
- [ ] **Further Develop Execution Code**
  - [ ] Completed execution logic including `&&` and `||`.
  - [ ] Implemented connection for previous pipe input (`prev_pipe_in`).
  - [ ] Added the first command to `command_argv`.
  - [ ] Added logic to find the executable’s path (`execve`).
  - [ ] Handled redirection.
  - [ ] Processed subshell arguments.
  - [ ] Still need to implement execution for built‑in commands.
  - [ ] Confirmed that the minishell launches and executes.
- [ ] **Additional:**  
  - Check for syntax errors with unmatched `||` or `&&`.



## Day 21
- [ ] **Finalize Execution Code**
  - [ ] Completed execution logic for `&&` and `||`.
  - [ ] Implemented the decision path for built‑in commands (built‑in execution logic currently exists as a branch).
  - [ ] **Implement Built‑ins:**  
    - [ ] echo, cd, pwd, export, unset, env, exit.
  - [ ] Verified redirection execution.
  - [ ] Confirmed proper exit status updates.
  - [ ] Developed heredoc logic:
    - Handled cases like `<< 'limit'` (no expansion when quoted).
  - [ ] Outlined subshell execution logic.
  - [ ] Implemented `$?`.
  - [ ] Handle system call failures (e.g. for `open`).
  - [ ] Implemented heredoc.
  - [ ] Verify subshell execution.
  - [ ] Improve pipe performance.
  - [ ] Refactor functions over 25 lines.
  - [ ] **Implement Comprehensive Signal Handling:**
    - Ctrl+C: Display a new prompt on a new line.
    - Ctrl+D: Exit the shell.
    - Ctrl+\: Do nothing.
  - [ ] **Clean Up Makefile:**
    - Ensure that running `make` in the minishell folder compiles libft.
    - Ensure `make fclean` removes libft.
    - Update the readline directory path (always set to the home directory).
  - [ ] Fix memory leaks and code style (norm).

- [ ] **Additional:**
  - Check syntax errors for unmatched `||` or `&&`.  
  - Adjust exit status for syntax errors.



## Day 22
- [ ] **Verify Subshell Execution**
- [ ] **Implemented `$?` Correctly**
- [ ] **Resolved Pipe Performance Issues**
- [ ] **Refactor Functions Exceeding 25 Lines**
- [ ] **Implement Comprehensive Signal Handling:**
  - [ ] Ctrl+C: New prompt on new line.
  - [ ] Ctrl+D: Exit the shell.
  - [ ] Ctrl+\: Do nothing.
  - [ ] Set signal handlers before calling `readline` so they re‑enable correctly.
  - [ ] In forked processes, block SIGINT in the parent and use default handling in the child.
  - [ ] For heredoc:
    - [ ] Implement signal handling (check if a child was terminated by a signal using WIFSIGNALED).
  - [ ] Compare behavior (e.g. for commands like `cat || ls` in Bash).
  - [ ] Ensure that if a child dies from SIGINT (exit status 130), the parent properly detects it (using waitpid for `|`, `||`, `&&` nodes).
    - [ ] Address issues in commands like `cat << limiter` (avoid segfaults).
  - *Note:* Child processes inherit the parent’s signal handlers.
- [ ] **Clean Up Makefile** (as before).
- [ ] Fix memory leaks and code style (norm).
- [ ] **Additional Implementation:**
  - [ ] Already implemented syntax error for unmatched `||` and `&&`.
  - [ ] Adjust exit status for syntax errors.
  - [ ] Implement built‑in commands:
    - [ ] echo, cd, pwd, export, unset, env, exit.



## Day 23
- [ ] **Fix File Descriptor Leaks**  
  - Use `lsof` to detect and fix minishell FD leaks (Minsukan task).
- [ ] **Resolve Issues with Piped Commands**  
  - E.g., `cd path | ls` is currently failing.
- [ ] **Handle Parentheses in Pipelines**  
  - E.g., `() | echo` should be fixed.
- [ ] **Handle Empty Parentheses**  
  - `()` should be treated as a syntax error (or handled appropriately).
- [ ] **Address Complex Expressions**  
  - E.g., `(ls || ls (ls | ls))` (Minsukan task).
- [ ] **Improve Built‑in `exit`:**  
  - Ensure it accepts arguments.
- [ ] **Refactor Functions Over 25 Lines**
- [ ] **Implement Signal Handling:**  
  - Ctrl+C: New prompt.
  - Set signal handlers before `readline` so they re‑enable.
  - In forked processes, block SIGINT in the parent and allow default in the child.
  - Ensure that if a child terminates with SIGINT (exit status 130), the parent properly handles it.
  - Handle heredoc signal termination to avoid segfaults.
- [ ] **Immediately Unlink Heredoc Files**  
  - When a child terminates due to SIGINT, unlink heredoc files immediately.
- [ ] **Clean Up Makefile** (as specified above).
- [ ] Fix memory leaks and norm issues.
- [ ] **Additional Implementation:**
  - [ ] Adjust exit status on syntax errors.
  - [ ] Implement built‑ins:
    - [ ] echo (with -n option), cd, env, unset, export (distinguish between env and shell variables – weekend assignment for Ji‑yun).

- *Note on Signals:*  
  Use `WIFSIGNALED(status)` to detect termination by a signal. Watch for race conditions between child termination and the parent’s `waitpid`.



## Day 24
- [ ] **Additional Implementation:**
  - [ ] Ensure that on syntax errors, the exit status is set correctly.
  - [ ] **Implement Built‑in Commands:**
    - [ ] exit:  
      - Accept an argument (per Minsukan).  
      - After exit, ensure that if a previous exit (e.g. exit 1) occurred, `$?` reflects that value.  
      - Validate that only one argument is allowed and check for overflows/invalid input.
    - [ ] pwd.
    - [ ] cd.
    - [ ] echo (handle the `-n` option).
    - [ ] env.
    - [ ] export (distinguish between environment and shell variables; assign this as Ji‑yun’s weekend task).
    - [ ] unset.
- [ ] **Fix Issues with Piped Commands:**  
  - E.g., `cd path | ls` is failing (Minsukan task).
- [ ] **Handle Parentheses in Commands:**  
  - E.g., `() | echo` should follow proper syntax.
- [ ] **Handle Complex Expressions:**  
  - E.g., `(ls || ls (ls | ls))` (Minsukan task).
- [ ] **Fix FD Leaks Using lsof** (Minsukan task).
- [ ] **Refactor Functions Over 25 Lines**
- [ ] **Clean Up Makefile:**
  - Ensure that compiling in the minishell folder also compiles libft.
  - Ensure `make fclean` removes libft.
  - Update the readline directory path (always set to home).
- [ ] Fix memory leaks and norm issues.



## Day 25
- [ ] **Test Subshell Execution:**  
  - `echo 1 && (echo 2 && echo 3)` – subshell did not execute at all.
- [ ] **Heredoc with Pipes:**  
  - `echo 1 | cat << end > out | cat > out2` – heredoc should not work correctly with a pipe.
- [ ] **Run `echo $PATH`**
- [ ] **Fixed the Exit Status Bug** (related to `!is_alnum`).
- [ ] **Further Heredoc Enhancements:**
  - [ ] Update `heredoc_list` to track the current node index.
  - [ ] Verify file naming based on index (using `access` to check existence).
  - [ ] Align heredoc node execution with the corresponding exec_list node.  
    *Example: `ls << lim | sleep 5 | ls << lim2`*
- [ ] **Tested Built‑in Exit with Pipe:**  
  - `echo 1 | exit 123` works correctly (no extra exit output).
- [ ] **Wildcard Expansion Observations:**
  - `ls *` seems to execute only one file.  
    - In `refine_field`, tokens without quotes and containing spaces are treated as wildcard expansion.
    - *Reminder:* When implementing export, include the variable with quotes.
- [ ] **Tested Exit Error:**  
  - `minishell > exit 123 123` produces “exit: Too many arguments”.
- [ ] **Investigate Issue:**  
  - `echo $?` suddenly fails (reason unknown).
- [ ] **Additional:**
  - [ ] Ensure export output is sorted.
  - [ ] Implement unset.
  - [ ] Fix FD leaks using lsof (Minsukan task).
  - [ ] Refactor functions over 25 lines.
  - [ ] Clean Up Makefile (compile libft, update readline path, verify CFLAGS, add heredoc support).
  - [ ] Fix memory leaks and norm issues.



## Day 26
- [ ] **Fixed Execution Order Issue for `(echo $PATH)`**
- [ ] **Run `echo $PATH` Successfully**
- [ ] **Further Heredoc Tasks:**
  - [ ] Handle cases like `<< abc | << abc`.
  - [ ] For commands like `cat << lim << lim2 | sleep 5 | (cat << lim3 << lim4)`:
    - [ ] Update `heredoc_list` with the current node index.
    - [ ] Validate file naming (check file existence using `access`).
    - [ ] Align heredoc node execution with the corresponding exec_list node.
    - *Example: `ls << lim | sleep 5 | ls << lim2`*
- [ ] **Tested:**  
  - `echo 1 | exit 123` – works as expected.
- [ ] **Wildcard Expansion:**  
  - `ls *` executes a single file; tokens without quotes and with spaces trigger wildcard expansion.
- [ ] **Tested:**  
  - `minishell > exit 123 123` prints “exit: Too many arguments”.  
  - [ ] However, `echo $?` suddenly fails (issue remains unresolved).
- [ ] **Additional:**
  - [ ] Ensure export output is sorted.
  - [ ] Implement unset.
  - [ ] Fix FD leaks using lsof (Minsukan).
  - [ ] Refactor functions over 25 lines.
  - [ ] Clean Up Makefile (compile libft in minishell folder, ensure `make fclean` removes libft, update readline path).
  - [ ] Fix memory leaks and norm issues.
  - [ ] Enforce undefined behavior for filenames with spaces/special characters  
    (e.g., `touch "ab c"` leads to errors with `ls ab c`).



## Day 27
- **Heredoc Logic (Assuming Creation in a Hidden Directory; Filenames Do Not Conflict)**
  - [ ] In the parent process, iterate through exec_list nodes; if a `<<` is found, create the corresponding heredoc file.
    - [ ] For non‑subshells: iterate over all tokens in the field to count occurrences of `<<`.
    - [ ] For subshells: search the string for `<<`, ignoring those inside quotes.
      - [ ] Create as many files as counted using a naming rule (e.g., `path/1.heredoc`, `path/2.heredoc`; the path is defined in the Makefile).
  - [ ] **Heredoc Discovery:**
    - [ ] Use `opendir`.
    - [ ] Use `readdir` (skip dot directories; note that readdir may return files in random order—sorting might be needed, e.g., 0.heredoc, 1.heredoc, 2.heredoc).
    - [ ] Return the first found file, open it, set up redirection, and delete the file immediately.
  - [ ] **Signal Handling in the Parent:**  
    - Process signals appropriately when received.
- [ ] **Tested Complex Heredoc Commands:**  
  - `cat << lim1 | ls | (cat << lim2) | (cat << lim3)`  
  - `<< abc | << abc`  
  - `cat << lim << lim2 | sleep 5 | (cat << lim3 << lim4)`  
  - For `ls << lim | sleep 5 | ls << lim2`:
    - [ ] Updated heredoc_list with the current node index.
    - [ ] Validated file naming using `access`.
    - [ ] Aligned heredoc node execution with the corresponding exec_list node.
- [ ] **Additional:**
  - [ ] Ensure export output is sorted.
  - [ ] Implement unset.
  - [ ] Fix FD leaks using lsof (Minsukan).
  - [ ] Refactor functions over 25 lines.
  - [ ] Clean Up Makefile (compile libft, remove libft on `make fclean`, update readline path).
  - [ ] Fix memory leaks and norm issues.
  - [ ] Enforce undefined behavior for filenames with spaces/special characters.



## Day 28
- [ ] **Executed `(echo $PATH)` Correctly** (added the missing step).
- [ ] **Ran `echo $PATH` Successfully**
- [ ] **Further Heredoc Enhancements:**
  - [ ] Handle cases like `<< abc | << abc`.
  - [ ] For commands like `cat << lim << lim2 | sleep 5 | (cat << lim3 << lim4)`:
    - [ ] Update heredoc_list with current node index.
    - [ ] Validate file naming based on file existence.
    - [ ] Align heredoc node execution with the corresponding exec_list node.
    - *Example: `ls << lim | sleep 5 | ls << lim2`*
- [ ] **Tested:**  
  - `echo 1 | exit 123` works as expected.
- [ ] **Wildcard Expansion:**  
  - Observed that `ls *` behaves as if executing one file.  
    - In `refine_field`, if there are spaces and no quotes, it’s treated as a wildcard.
    - *Reminder:* When implementing export, add environment variables with quotes.
- [ ] **Tested:**  
  - `minishell > exit 123 123` outputs “exit: Too many arguments”.  
  - [ ] However, `echo $?` suddenly fails (issue unresolved).
- [ ] **Additional:**
  - [ ] Ensure export output is sorted.
  - [ ] Implement unset.
  - [ ] Fix FD leaks using lsof (Minsukan).
  - [ ] Refactor functions over 25 lines.
  - [ ] Clean Up Makefile (compile libft in minishell folder, ensure `make fclean` removes libft, update readline path).
  - [ ] Fix memory leaks and norm issues.
  - [ ] Enforce undefined behavior for filenames with spaces/special characters.



## Day 29
- [ ] **Handle Built‑in Commands:**
  - [ ] Implemented `cd` (handling PWD, OLDPWD, and absolute paths).
  - [ ] Implemented `export` and `env` (refactored to avoid unnecessary malloc calls).
  - [ ] Implemented `clear`:
    - Adjusted env_list value format (e.g., `h="hello"` becomes `h=hello`).
  - [ ] In subshells:
    - If redirection is present, treat it as a syntax error.
  - [ ] In execution:
    - Fixed memory leak issues.
- **Leak Handling:**  
  - Freed memory in functions (refine_field, wildcard_split, etc.).
- [ ] **Additional Tasks:**
  - [ ] Split project into separate folders and files.
  - [ ] Implement system call return error handling.
  - [ ] Refactor functions over 25 lines.
  - [ ] Fix FD leaks using lsof (Minsukan).
  - [ ] Ensure compliance with norm.
  - [ ] Clean Up Makefile:
    - Compile libft when running `make`.
    - Ensure `make fclean` removes libft.
    - Update the readline directory (always set to home).
    - Verify CFLAGS.



## Day 30
- [ ] **Organize Project Structure**
  - Split the project into appropriate folders and files.
- [ ] **Implement System Call Error Handling**
- [ ] **Refactor Functions Over 25 Lines**  
  (compared to previous versions)
- [ ] **Fix FD Leaks Using lsof** (Minsukan task)
- [ ] **Ensure Code Style Compliance (Norm)**
- [ ] **Clean Up Makefile:**
  - [ ] Ensure that running `make` in the minishell folder also compiles libft.
  - [ ] Ensure `make fclean` removes libft.
  - [ ] Update the readline directory path (always set to home).
  - [ ] Verify CFLAGS.



## Day 31
- [ ] **Decide on `ls()` Error Handling**  
  - Whether to show a syntax error or “command not found” for `ls()`; decision: keep it as is (per Cheseo’s suggestion).
- [ ] **Fix Subshell Spacing Issue:**  
  - For example, `(cat) | (cat) | (cat)` – when interrupted, extra spaces (three times) are printed.
- [ ] **Handle Built‑in Exit Status**
- [ ] **Address Unhandled System Calls:**
  - [–] What if Signal fails?
  - [–] Handling of `open` with variable arguments.
  - [–] `waitpid` issues.
  - [ ] Fixed `close`.
  - [ ] For `opendir`, `readdir`, `closedir` – handled internally (not considered system calls here).
- [ ] **Implemented System Call Return Error Handling**
- [ ] **Additional Tasks:**
  - [ ] Fix FD leaks using lsof (Minsukan).
  - [ ] Clean Up Makefile:
    - [ ] Ensure libft compiles when running `make` in the minishell folder.
    - [ ] Ensure `make fclean` removes libft.
    - [ ] Update readline directory (always set to home).
    - [ ] Verify CFLAGS.
    - [ ] Add Makefile support for heredoc.
  - [ ] Organize header files.



## Day 32
- [ ] **Modularize Code:**  
  - Separated `main`, subshell, and parser into distinct modules.
- [ ] **Separate Execution Logic**
- [ ] **Code Style (Norm) Compliance:**  
  - Applied norm checks to `execute`, `refine_field`, `tokenize`, and `main`.



## Day 33
- [ ] **Tokenization Splitting**
- [ ] **Code Style (Norm) Compliance**
- [ ] **Fix FD Leaks Using lsof** (Minsukan)
- [ ] **Clean Up Makefile:**
  - [ ] Ensure that running `make` in the minishell folder compiles libft.
  - [ ] Ensure `make fclean` removes libft.
  - [ ] Update the readline directory path (always set to home).
  - [ ] Verify CFLAGS.
  - [ ] List source files.
  - [ ] List bonus files.
  - [ ] Add Makefile support for heredoc.
- [ ] **Organize Header Files**



## Additional Tasks (Suggested)
- [ ] **Implement Auto‑Completion** for commands and filenames.
- [ ] **Enhance Error Messages** for clearer user feedback.
- [ ] **Expand Unit Tests** to cover more edge cases.
- [ ] **Improve Memory Management** and verify with tools like Valgrind.
- [ ] **Document Code Thoroughly** for easier future maintenance.
- [ ] **Consider Cross‑Platform Compatibility** Enhancements.


