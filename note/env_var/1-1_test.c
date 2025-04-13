#include <stdio.h>
#include <stdlib.h>

/** to check if the env_var is exist **/
int main(int argc, char *argv[])
{
	char	*env_var = getenv("API_KEY");
	if (!env_var)
	{
		printf("no api key\n");
		return (1);
	}
	printf("api key is %s\n", env_var);
	return (0);
}