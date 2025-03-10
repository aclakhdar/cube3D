
#include "cube.h"

int	index_n(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	return (i);
}

char	*ft_function(char *buffer)
{
	char	*line;
	int		i;

	line = malloc(index_n(buffer) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_nextline(char *buf)
{
	char	*nline;
	int		i;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		nline = ft_substr(buf, i + 1, ft_strlen(buf));
		free(buf);
		nline[ft_strlen(nline)] = '\0';
	}
	else
	{
		nline = NULL;
		free(buf);
	}
	return (nline);
}

void	ft_norm(char **line, char **buffer)
{
	*line = ft_function(*buffer);
	*buffer = ft_nextline(*buffer);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	char		*buff;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	while (ft_check(stock) == -1)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1 || r == 0)
		{
			free(buff);
			break ;
		}
		buff[r] = '\0';
		stock = ft_strjoin(stock, buff);
	}
	ft_norm(&line, &stock);
	return (line);
}
