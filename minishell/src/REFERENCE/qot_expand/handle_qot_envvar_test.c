//#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	nested_with_double_quotes(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '\'')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	nested_with_single_quotes(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == '"')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	has_nested_quotes(char *str)
{
	return (nested_with_double_quotes(str) || nested_with_single_quotes(str));
}

static int find_closing_quote(char *str, int start, char quote_type)
{
	int i;
	
	i = start + 1;
	while (str[i] && str[i] != quote_type)
		i++;
	
	if (str[i] == quote_type)
		return (i);
	return (-1);
}

// Checks if a variable at position i should be expanded
int should_expand_var_at(char *str, int i)
{
	int j = 0;
	int active_single_quote = 0;
	
	while (j < i)
	{
		// Single quotes are only relevant at the outermost level
		// Once inside ACTUAL single quotes (not those inside double quotes), variables don't expand
		if (str[j] == '\'' && (j == 0 || str[j-1] != '\\'))
		{
			if (active_single_quote)
				active_single_quote = 0;
			else
			{
				// Check if this single quote is inside double quotes
				int in_dquote = 0;
				for (int k = 0; k < j; k++)
				{
					if (str[k] == '"' && (k == 0 || str[k-1] != '\\'))
						in_dquote = !in_dquote;
				}
				
				if (!in_dquote)
					active_single_quote = 1;
			}
		}
		j++;
	}
	
	return !active_single_quote;
}

// Returns 1 if any variables in the string should be expanded
int should_expand_vars(char *str)
{
	int i = 0;
	
	if (!str)
		return (0);
		
	while (str[i])
	{
		if (str[i] == '$' && str[i+1] && 
			(str[i+1] == '?' || str[i+1] == '_' || 
			 (str[i+1] >= 'A' && str[i+1] <= 'Z') || 
			 (str[i+1] >= 'a' && str[i+1] <= 'z') ||
			 (str[i+1] >= '0' && str[i+1] <= '9') ||
			 str[i+1] == '('))  // For command substitution
		{
			if (should_expand_var_at(str, i))
				return (1);
		}
		i++;
	}
	
	return (0);
}

// Check if outer quotes should be removed
int should_remove_quotes(char *str, char quote_type)
{
    int first = -1, last = -1;
    
    // Find first and last quotes
    for (int i = 0; str[i]; i++) {
        if (str[i] == quote_type && (i == 0 || str[i-1] != '\\')) {
            if (first == -1)
                first = i;
            last = i;
        }
    }
    
    // If first and last characters are quotes of the given type,
    // they should be removed during parsing
    return (first == 0 && last == strlen(str) - 1);
}

// Handles command substitution
char *process_command_substitution(char *cmd)
{
    if (strncmp(cmd, "$(echo ", 7) == 0) {
        // Extract what's inside the echo command
        char *content = cmd + 7;
        int len = strlen(content);
        
        // Remove trailing )
        if (content[len-1] == ')')
            content[len-1] = '\0';
            
        // If it's $PATH, return the path
        if (strcmp(content, "$PATH") == 0)
            return strdup("/usr/lib/gcc:/home/user/bin:/usr/local/bin:/usr/bin");
            
        return strdup(content);
    }
    return strdup("$(command-output)");
}

// Simulates bash's handling of the input for demonstration
char *simulate_bash_expansion(char *str)
{
	char *result = strdup(str);
	char *path = "/usr/lib/gcc:/home/user/bin:/usr/local/bin:/usr/bin"; // Shortened for readability
	char *user = "jiepark"; // Example username
	char *home = "/home/jiepark"; // Example home directory
	char *var_start;
	char *expanded;
	int in_active_single_quotes = 0;
	int i = 0;
	
	// Simple simulation
	while (result[i])
	{
		// Track actual single quotes (those not inside double quotes)
		if (result[i] == '\'' && (i == 0 || result[i-1] != '\\'))
		{
			// Check if this quote is inside double quotes
			int in_dquote = 0;
			for (int k = 0; k < i; k++)
			{
				if (result[k] == '"' && (k == 0 || result[k-1] != '\\'))
					in_dquote = !in_dquote;
			}
			
			if (!in_dquote)
				in_active_single_quotes = !in_active_single_quotes;
		}
		
		// Process variables when not in active single quotes
		if (result[i] == '$' && !in_active_single_quotes)
		{
			var_start = &result[i];
			
			// Handle $PATH
			if (strncmp(var_start+1, "PATH", 4) == 0 && 
			    (!var_start[5] || var_start[5] == ' ' || var_start[5] == '"' || 
			     var_start[5] == '\'' || var_start[5] == ':' || var_start[5] == ')'))
			{
				// Cut string at variable
				*var_start = '\0';
				
				// Create new expanded string
				expanded = malloc(strlen(result) + strlen(path) + strlen(var_start+5) + 1);
				strcpy(expanded, result);
				strcat(expanded, path);
				strcat(expanded, var_start+5);
				
				// Replace old string
				free(result);
				result = expanded;
				
				// Resume from end of inserted path
				i = strlen(result) - strlen(var_start+5);
				continue;
			}
			// Handle $USER
			else if (strncmp(var_start+1, "USER", 4) == 0 && 
			         (!var_start[5] || var_start[5] == ' ' || var_start[5] == '"' || 
			          var_start[5] == '\'' || var_start[5] == ':' || var_start[5] == ')'))
			{
				// Cut string at variable
				*var_start = '\0';
				
				// Create new expanded string
				expanded = malloc(strlen(result) + strlen(user) + strlen(var_start+5) + 1);
				strcpy(expanded, result);
				strcat(expanded, user);
				strcat(expanded, var_start+5);
				
				// Replace old string
				free(result);
				result = expanded;
				
				// Resume from end of inserted username
				i = strlen(result) - strlen(var_start+5);
				continue;
			}
			// Handle $HOME
			else if (strncmp(var_start+1, "HOME", 4) == 0 && 
			         (!var_start[5] || var_start[5] == ' ' || var_start[5] == '"' || 
			          var_start[5] == '\'' || var_start[5] == ':' || var_start[5] == ')'))
			{
				// Cut string at variable
				*var_start = '\0';
				
				// Create new expanded string
				expanded = malloc(strlen(result) + strlen(home) + strlen(var_start+5) + 1);
				strcpy(expanded, result);
				strcat(expanded, home);
				strcat(expanded, var_start+5);
				
				// Replace old string
				free(result);
				result = expanded;
				
				// Resume from end of inserted home dir
				i = strlen(result) - strlen(var_start+5);
				continue;
			}
			// Handle $?
			else if (var_start[1] == '?' && 
			         (!var_start[2] || var_start[2] == ' ' || var_start[2] == '"' || 
			          var_start[2] == '\'' || var_start[2] == ':' || var_start[2] == ')'))
			{
				// Cut string at variable
				*var_start = '\0';
				
				// Create new expanded string
				expanded = malloc(strlen(result) + 2 + strlen(var_start+2) + 1);
				strcpy(expanded, result);
				strcat(expanded, "0"); // Assume exit status 0
				strcat(expanded, var_start+2);
				
				// Replace old string
				free(result);
				result = expanded;
				
				// Resume from end of inserted exit status
				i = strlen(result) - strlen(var_start+2);
				continue;
			}
			// Handle command substitution $(...)
			else if (var_start[1] == '(' && strchr(var_start, ')'))
			{
				char *closing = strchr(var_start, ')');
				*closing = '\0'; // Temporarily terminate at closing parenthesis
				char *cmd_output = process_command_substitution(var_start);
				*var_start = '\0'; // Cut at command start
				
				// Create new expanded string
				expanded = malloc(strlen(result) + strlen(cmd_output) + strlen(closing+1) + 1);
				strcpy(expanded, result);
				strcat(expanded, cmd_output);
				strcat(expanded, closing+1);
				
				// Replace old string
				free(cmd_output);
				free(result);
				result = expanded;
				
				// Resume from end of inserted command output
				i = strlen(result) - strlen(closing+1);
				continue;
			}
		}
		i++;
	}
	
	return result;
}

int main(void)
{
    // These test cases represent individual AST node arguments
    char *test_cases[] = {
        // Simple cases
        "word",                      // Case 1: Simple word
        "\"quoted\"",                // Case 2: Double quoted arg
        "'quoted'",                  // Case 3: Single quoted arg
        
        // Environment variable cases
        "$PATH",                     // Case 4    "\"$USER'hey'\"",          // Var followed by quoted text
        "\"$USER'$USERhey'\"",     // Var followed by quoted text with var
        "\"$?\"",                  // Exit status variable
        "hey \"word 'word' \" word 'word' \" word\"" // Complex case with multiple quotes: Unquoted variable - expands
        "'$PATH'",                   // Case 5: Variable in single quotes - no expansion
        "\"$PATH\"",                 // Case 6: Variable in double quotes - expands
        "prefix$PATH",               // Case 7: Variable with prefix - expands
        "$PATHsuffix",               // Case 8: Variable with suffix - expands
        
        // Nested quote cases
        "\"word with 'nested'\"",    // Case 9: Single quotes inside double quotes
        "'word with \"nested\"'",    // Case 10: Double quotes inside single quotes
        "\"'test'\"",                // Case 11: Single quoted inside double
        "\"word '$PATH' word\"",     // Case 12: Variable inside single inside double - EXPANDS but keeps quotes
        "'word \"$PATH\" word'",     // Case 13: Variable in double quotes inside single - no expansion
        "\"$PATH'text'\"",           // Case 14: Variable followed by single quotes
        "'$PATH\"text\"'",           // Case 15: Variable followed by double quotes in single
        
        // Complex cases
        "\"$USER:$PATH\"",           // Case 16: Multiple variables in double quotes - both expand
        "$?",                        // Case 17: Exit status variable
        "$(echo $PATH)",         // Case 18: Command substitution - parentheses removed
        "\"$USER'hey'\"",          // Var followed by quoted text
        "\"$USER'$USERhey'\"",     // Var followed by quoted text with var
        "\"$?\"",                  // Exit status variable
  //      "hey \"word 'word' \" word 'word' \" word\"" // Complex case with multiple quotes
        // Additional test for adjacent quoted sections
        NULL
    };
    
    printf("===== QUOTE AND VARIABLE DETECTION TESTS =====\n\n");
    
    for (int i = 0; test_cases[i]; i++)
    {
        printf("Case %2d: %s\n", i + 1, test_cases[i]);
        
        // Count quotes and special chars for debugging
        int single_quotes = 0, double_quotes = 0, dollar_signs = 0, parentheses = 0;
        for (int j = 0; test_cases[i][j]; j++) {
            if (test_cases[i][j] == '\'') single_quotes++;
            if (test_cases[i][j] == '"') double_quotes++;
            if (test_cases[i][j] == '$') dollar_signs++;
            if (test_cases[i][j] == '(' || test_cases[i][j] == ')') parentheses++;
        }
        
        printf("  Quote count: %d single, %d double, %d $ signs, %d parentheses\n", 
               single_quotes, double_quotes, dollar_signs, parentheses);
        
        printf("  Has nested quotes:           %s\n", 
               has_nested_quotes(test_cases[i]) ? "YES" : "NO");
        printf("  Single quotes inside double: %s\n", 
               nested_with_double_quotes(test_cases[i]) ? "YES" : "NO");
        printf("  Double quotes inside single: %s\n", 
               nested_with_single_quotes(test_cases[i]) ? "YES" : "NO");
        printf("  Should expand variables:     %s\n",
               should_expand_vars(test_cases[i]) ? "YES" : "NO");
        printf("  Should remove double quotes: %s\n",
               should_remove_quotes(test_cases[i], '"') ? "YES" : "NO");
        printf("  Should remove single quotes: %s\n",
               should_remove_quotes(test_cases[i], '\'') ? "YES" : "NO");
               
        // Show bash expansion for all cases with variables
        if ((strstr(test_cases[i], "$") != NULL) || 
            (strstr(test_cases[i], "$(") != NULL)) {
            char *expanded = simulate_bash_expansion(test_cases[i]);
            printf("  Bash would expand to:      %s\n", expanded);
            free(expanded);
        }
        
        printf("\n");
    }
    
    printf("==============================\n");
    
    return (0);
}