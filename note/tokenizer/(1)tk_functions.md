# 1.  `strtok` 
`strtok` (**string tokenizer**) is used to **split a string into tokens** based on a given delimiter (`=` in this examples below).  
## example
```c
int	main(int ac, char *av[], char *envp[])
{
	char	*env_var = envp[0];
	int		i = 0;

	while (env_var)
	{
		char	*key = strtok(env_var, "=");
		char	*value = strtok(NULL, "=");
		printf("key: %s, value: %s\n", key, value);
		i++;
		env_var = envp[i];
	}
}
```

### **1️⃣ First `strtok(env_var, "=")` Call**
- Finds the **first `=`** in `env_var`.  
- **Replaces it with `\0`**, splitting the string into two parts:
  ```
  "PATH\0/usr/bin:/bin:/usr/sbin"
  ```
- **Returns the first token**, which is `"PATH"`.  
- After this call, strtok returns `"PATH"` 
- later on, at the bottom of the while loop, `env_var` will be modified to `"/usr/bin:/bin:/usr/sbin"`(before `=`).

---  

### **2️⃣ Second `strtok(NULL, "=")` Call**
- **Continues from the saved position**, which is **right after the first `\0`**.  
- Returns **everything until the next `=`** (if present) or until `\0` at the end of the string.
  ```
  "/usr/bin:/bin:/usr/sbin"
  ```
- If no more `=` is found, **it returns everything left** as one single token.

👉 **it simply returns everything after the first `\0` ("value").**
- 🔍 why? Second Call: strtok(NULL, "=")

	- it starts from the character after the \0, since it treats **\0** as a **stopping point, not a token**.
	- it does not return \0 because \0 marks the end of a string.
	- strtok only returns non-empty tokens.

---

### **⚠️ Issue with This Approach**

#### (1) multiple '=' case
If the value **contains another `=`**, it **will be split into multiple tokens** instead of keeping the full value.
```c
char env_var[] = "MY_VAR=hello=world";
```
- **First call** → `"MY_VAR"`
- **Second call** → `"hello"`  
- **Third call** → `"world"` (WRONG! The value should be `"hello=world"`)

#### (2) Modifying `envp[i]` directly
- **Modifying `envp[i]` directly** is risky because `envp` is usually read-only.
- A better approach is to **copy `env_var` into a separate buffer** before using `strtok`.

#### **Safer Alternative**
```c
char *var_copy = strdup(env_var);  // Duplicate to avoid modifying envp
char *key = strtok(env_copy, "=");
char *value = strtok(NULL, "=");
```
<br>

# 2. strchr(env_var, '=')
To **properly extract key-value pairs**, use `strchr(env_var, '=')` instead of `strtok`. 🚀

```c
#include <stdio.h>
#include <string.h>

int main(int ac, char *av[], char *envp[]) {
	int i = 0;
	
	while (envp[i]) {
		char *env_var = envp[i];
		char *equal_sign = strchr(env_var, '='); // Find first '=' in the string

		if (equal_sign) {
			size_t key_length = equal_sign - env_var; // Length of key
			char key[key_length + 1];  // Allocate buffer for key
			strncpy(key, env_var, key_length);
			key[key_length] = '\0';
			char *value = equal_sign + 1; // Value starts after '='
			printf("key: %s\n\nvalue: %s\n\n", key, value);
		}
		i++;
	}
	return 0;
}
```

---


