
#include "cube.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_check(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *s)
{
	int		len;
	char	*p;
	int		i;

	i = 0;
	len = ft_strlen(s);
	p = malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!s1)
		ft_strdup("");
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	j = -1;
	while (s1[++j])
		str[j] = s1[j];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	free(s1);
	free(s2);
	return (str);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*x;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	x = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (x == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		x[i] = s[start];
		i++;
		start++;
	}
	x[i] = '\0';
	return (x);
}
