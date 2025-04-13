// about env expander
void	function()
{
	char	*line;

	line = ft_strdup("hello $USER"); // allocated

	line = ev_expander(data, line);
	// return: expanded line
	// old line have freed in the function
	printf("%s\n", line);
	// output:
	// hello ********
}


//about wildcard expander
void	function()
{
	char	*line;
	char	**expanded;

	expanded = NULL;
	line = ft_strdup("test*.c");
	expanded = wc_expander(data, line); //line will NOT be freed in the function
	// return: expanded string array char **
	// if expanded == NULL, it means there is no filename for this line with wildcard
		// in this case, the original line will be used as argument
	// otherwise
		// args of ast will be modified

// example:
	// args in ast: {"cat", "file*", NULL}
	// expanded "file *" = {"file", "file2", NULL}
	
	// then args should be modified like this:
	// args = {"cat", "file", "file2", NULL}

// example2:
	// args in ast: {"cat", "file*", NULL}
	// expanded = NULL
	// args will not change
	
}
