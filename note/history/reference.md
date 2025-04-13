https://git.hexanyn.fr/42/minishell/-/blob/master/srcs/history.c?ref_type=heads

The provided code implements the command history feature in a minishell project, similar to shells like Bash. Here's a breakdown of its purpose and components:

### **Why History is Needed in a Shell**
- **User Convenience**: Allows users to quickly recall and re-execute previous commands without retyping.
- **Persistence**: Saves command history between shell sessions by storing it in a file.
- **Navigation**: Users can cycle through past commands using the up/down arrow keys.

---

### **Key Functions Explained**

1. **`add_history(char *line)`**
   - **Purpose**: Appends a command to the history file and updates the in-memory list.
   - **Steps**:
     1. Constructs the history file path (`~/.minishell_history`).
     2. Opens the file in append mode (creates it if missing).
     3. Writes the command to the file and adds it to the front of the linked list (`g_mini->history`).
     4. Resets `history_pos` (current navigation position) to `-1` (no active history navigation).

2. **`get_history(void)`**
   - **Purpose**: Reads the history file at shell startup to populate the in-memory history list.
   - **Steps**:
     1. Reads the history file line-by-line.
     2. Adds each line (command) to the front of the linked list, ensuring the most recent commands are first.

3. **`set_history(char c)`**
   - **Purpose**: Navigates through the history when the user presses up/down arrows.
   - **Behavior**:
     - **Up Arrow (ASCII 65)**:
       - Moves to older commands (increments `history_pos`).
       - Updates the current input line with the selected history entry.
     - **Down Arrow (ASCII 66)**:
       - Moves to newer commands (decrements `history_pos`).
       - Resets to the current input line when reaching the end of history.
   - **Terminal Interaction**: Clears the current line and displays the history entry.

---

### **In-Memory History Structure**
- **Linked List**: Commands are stored in reverse chronological order (newest first) via `ft_lstadd_front`.
- **Navigation**: `history_pos` tracks the current position in the history list:
  - `-1`: No history navigation (showing the current input line).
  - `0`: Newest command, `1`: Second newest, etc.

---

### **File Persistence**
- **Location**: `~/.minishell_history` (depends on the `HOME` environment variable).
- **Appending**: Each new command is added to the end of the file.
- **Loading at Startup**: The file is read to rebuild the history list, ensuring commands persist across shell sessions.

---

### **Why This Code is Essential**
1. **Efficiency**: Quickly access past commands without disk I/O during navigation.
2. **User Experience**: Mimics standard shell behavior, making the minishell more intuitive.
3. **Data Integrity**: Commands are saved immediately to prevent loss on shell crashes.

---

### **Flow Example**
1. **User enters `ls -l`**:
   - `add_history` writes it to the file and adds it to the front of the list.
2. **User presses UP**:
   - `set_history` retrieves the most recent command (`ls -l`) and displays it.
3. **User presses DOWN**:
   - Returns to the current input line (if any) or newer commands.

This implementation ensures the minishell handles history robustly, balancing in-memory efficiency with persistent storage.