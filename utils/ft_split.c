
#include "../cube.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != (char)c)
			i++;
		else
		{
			return ((char *)s + i);
		}
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}

static int	ft_nmrwords(const char *s, char c)
{
	int	a;
	int	i;

	i = 0;
	a = 0;
	if (s[i] != c)
		a = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			a++;
		i++;
	}
	return (a);
}

static char	**ft_null(char **p)
{
	p = (char **)malloc (1 * sizeof (char *));
	if (!p)
		return (NULL);
	p[0] = NULL;
	return (p);
}

char	**ft_split(const char *s, char c)
{
	char	**p;
	int		start;
	int		i;
	int		j;

	p = NULL;
	if (s[0] == '\0')
		return (ft_null(p));
	p = ((char **)malloc ((ft_nmrwords(s, c) + 1) * sizeof (char *)));
	if (!p)
		return (ft_null(p));
	i = 0;
	j = 0;
	while (i < ft_nmrwords(s, c))
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		p[i++] = ft_substr((char *)s, start, j - start);
	}
	p[i] = NULL;
	return (p);
}
