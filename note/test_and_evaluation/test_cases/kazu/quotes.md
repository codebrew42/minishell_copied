# test cases / quotes

- `unclosed quotes` is not_required in the assignment but handle crash

-> which bihavior? printing error message and showing prompt?

```bash
echo ""
echo ''
echo "hello 'world' !"
echo 'hello "world" !'
echo 'hello 'world' !'
echo "hello "world" !"

echo "$PATH"
echo '$PATH'

# with and without files
echo '*.c'
echo "*.c"
echo '*.py'
echo "*.py"

echo *.c

```
## notes

### quotes keep different quotes                                                            
- single in double
- double in single

```bash
>> echo "hello 'world' !"
hello 'world' !
>> echo 'hello "world" !'
hello "world" !
```

but

```bash
>> echo 'hello 'world' !'
hello world !
>> echo "hello "world" !" 
hello world !
```

### environmental variables will be expanded in double quotes, but not in single quotes

```bash
>> echo "$PATH"
/home/local/bin:usr/localsbin:usr/...
>> echo '$PATH'
$PATH
```

### quotes don't expand wildcard

```bash
>> echo '*.c'
*.c
>> echo "*.c"
*.c
>> echo *.c
test1.c test2c
```