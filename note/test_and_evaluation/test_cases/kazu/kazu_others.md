# test cases / kazu others

## env var

```shell
$PATH
"$PATH"
'$PATH'
```
---

## && ||
```bash
cat xxx || ls
cat xxx && ls
ls || cat xxx
ls && cat xxx
```

### note

-  `||` and `&&` will give the exit code of last process which have ran.


```bash
cat xxx || ls #exit code of ls = 0

cat xxx && ls #exit code of cat = 1

ls || cat xxx #exit code of ls = 0

ls && cat xxx #exit code of cat = 1
```