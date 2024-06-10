


# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;
	size_t	newlen;

	j = 0;
	newlen = 0;
	if (start >= strlen(s))
		return (strdup(""));
	if (start + len > strlen(s))
		newlen = strlen(s) - start;
	else
		newlen = len;
	str = (char *)malloc(sizeof(char) * (newlen + 1));
	if (!str || !s)
		return (NULL);
	while (start < strlen(s) && j < len)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}



int main ()
{
	char s[40] = "echo 'helle $USER' > infile.txt | wc -l";
	char *line = ft_substr(s, 0, 34);
	printf("line: %s\n", line);
}