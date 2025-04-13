#include <stdio.h>
#include <string.h>

int main(int ac, char *av[], char *envp[])
{
	int i = 0;
		
	while (envp[i]) {
		char *env_var = envp[i];
		char *equal_sign = strchr(env_var, '=');

		if (equal_sign) {
			size_t key_length = equal_sign - env_var;
			char key[key_length + 1];
			strncpy(key, env_var, key_length);
			key[key_length] = '\0';
			char *value = equal_sign + 1;
			printf("key: %s\nvalue: %s\n\n", key, value);
		}
		i++;
	}
	return 0;
}