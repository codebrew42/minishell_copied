```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *env_var = getenv("API_KEY");
	if (env_var == NULL)
	{
		printf("API_KEY is not set\n");
		return 1;
	}
	printf("API_KEY is %s\n", env_var);
	return 0;
}
```

```bash
export API_KEY=1234567890
echo $API_KEY  # 1234567890

./a.out #does nothing, why?
```

# Why ./a.out Does Nothing?

In the given example, the environment variable API_KEY is set, but ./a.out does not recognize it. This happens because:

API_KEY=123 sets the variable only for the current shell session.

Running ./a.out does not inherit API_KEY unless it is explicitly exported.

To properly pass the variable...
```bash
export API_KEY=123
API_KEY=123 ./a.out
```

Without export, API_KEY is only a shell variable and not an environment variable.

Programs like ./a.out only access exported environment variables.

Use env to check if API_KEY is in the environment:
```bash
env | grep API_KEY
```

# what does unset remove?
```
unset API_KEY
```
1.The shell’s local variables
2.The environment variables

it removes both