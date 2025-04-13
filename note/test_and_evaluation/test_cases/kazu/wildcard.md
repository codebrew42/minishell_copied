# test cases / Wildcard

---

```bash
# with and without files
echo '*.c'
echo "*.c"
echo '*.py'
echo "*.py"

echo *.c
echo *test*
echo *test*.sh
echo t*st
echo *.*
echo *".c"

ls *.*

```
---
## note

### wildcard in quotaton will not be expanded.

```bash
# with and without files
echo '*.c'
echo "*.c"

# result of both will be:
*.c
```

Wildcard without quotaton will be expanded:

```bash
echo *.c

# result will be all filenamess with .c in current directory
test.c test2.c test3.c
```

These means:
```bash
>> echo *".c"
test1.c test2.c
```