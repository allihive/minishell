char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*str;
	int	j;
	int	newlen;

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
		return (0);
	while (start < strlen(s) && j < len)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}



int main()
{
  char *s = "echo '42'<file.txt| cat";
  char *temp =  s+18;
  printf("s:%s\n", s);
  
  printf("s:%s\n", ft_substr(s, 0, (temp - s )));
 }