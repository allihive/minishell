#include <stdio.h>

char *point_end(char *line)
{
    // while (*line)
    // {
    //      while (*line && *line != '|' && *line != '\"' && *line != '\'')
    //         line++;
    //     if (*line == '\"' || *line == '\'')
    //     {
    //         line++;
    //         while(*line && *line != '|' && *line != '\"' && *line != '\'')
    //             line++;
    //         return(line);
    //     }
    //     else
    //         return (line);
    // }
    // return(line);


    	
    while (*line)
	{
		while (*line && *line != '\''
			&& *line != '\"' && *line != '|')
			line++;
		if (*line == '\"' || *line =='\'')
		{
			line++;
			while (*line &&*line != '|' && *line != '\'' && *line != '\"')
				line++;
			line++;
		}
		else
			return (line);
	}
	return (line);
}


int main ()
{
    
    char *s = "echo 'hallpy jkl'| 'echo'42";
     printf ("s: %s\n", s);
    printf ("s: %s\n", point_end(s));
}