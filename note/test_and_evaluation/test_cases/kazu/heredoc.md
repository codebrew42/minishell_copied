# test cases / heredoc

---

```shell
cat <<LIM
cat << LIM
cat <<                 LIM
cat << LI\M
cat << ""
cat << LIM | grep a > file
cat << LIM | grep a >> file
cat << LIM | rev
cat << $hello
cat << LIM1 << LIM2

# syntax error
cat <<
```

---
## notes

- LIMITER = "" is "\n"

- if input is environmental variable, it will expand

```bash
cat << LIM
$a 
$path
$PATH
LIM

#result


/home/usr/bin:/usr/bin:/usr...
```
`$a` and `$path` is not there, so `cat` shows only `\n`.

`$PATH` exsists, so `cat` will expand