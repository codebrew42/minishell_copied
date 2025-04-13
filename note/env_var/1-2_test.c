#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** how to print all env_var **/
int main(int argc, char *argv[], char *envp[])
{
	char	*env_var = envp[0];
	int		i = 0;
	while (env_var)
	{
		//method no.1
//		char	*key = strtok(env_var, "=");
//		char	*value = strtok(NULL, "=");
//		printf("key: %s, value: %s\n", key, value);
		//method no.2
		printf("%s\n", env_var);
		i++;
		env_var = envp[i];
	}
	return 0;
}


/** how to get PATH from env_var **/
/*
int	main(int ac, char *av[], char *envp[])
{
	char	*env_var = envp[0];
	int		i = 0;

	while (env_var)
	{
		char	*key = strtok(env_var, "=");
		char	*value = strtok(NULL, "=");
		if (strcmp(key, "PATH") == 0)
			printf("PATH: %s\n", value);
		i++;
		env_var = envp[i];
	}
}
*/