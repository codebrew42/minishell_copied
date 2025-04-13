# minishel behavior list

list of the behavior of minishell which are not same as bash

---

### unclosed quotation

    echo "aaa

result:

    echo 'aaa

result:

---

### special charactor which minishell doesn't handle

`;`, `\`

    echo hello ; echo world

result:

    hello ; echo world

---

### special env var

`\$@`, `\$#` and so on



---

## Redirections

### `2>` and `2>&1`

---

