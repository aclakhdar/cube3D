#include "cube.h"

void	check_newline(t_game *game)
{
	int	i;

	i = 0;
	while (game->str[i] != '\0')
	{
		if (game->str[i] == '\n' && game->str[i + 1] == '1')
		{
			i++;
			while (game->str[i])
			{
				if (game->str[i] == '\n' && game->str[i + 1] == '\n')
				{
					write(2,"error empty line",16);
					exit(1);
				}
				i++;
			}
			return ;
		}
		i++;
	}
}

int	check_map_name(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i])
	{
		if (map_name[i] == '.')
		{
			if (map_name[i + 1] == 'c' && map_name[i + 2] == 'u'
				&& map_name[i + 3] == 'b' && map_name[i + 4] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	check_ac(int ac)
{
	if (ac != 2)
	{
		write(2,"invalide arg",12);
		exit(1);
	}
}
void	err_msg(void)
{
	write(2, "Error\nU CANT PLAY\n", 19);
	exit(1);
}
void	err_msg2(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
void	check_texture_color(char *line, t_game *game)
{
	int		i;
	char	**str_split;

	i = 0;
	game->fd = 0;
	str_split = ft_split(line, ' ');
	if (str_split[2])
		err_msg();
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		check_no(line, game, game->fd, str_split);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		check_we(line, game, game->fd, str_split);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		check_ea(line, game, game->fd, str_split);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		check_so(line, game, game->fd, str_split);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		check_f(game, str_split);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		check_c(game, str_split);
	else
		err_msg();
	free (str_split);
}
void	read_map(char *map_name, t_game *game)
{
	char	*line;
	int		fd;

	game->str = ft_strdup("");
	game->no = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->so = NULL;
	game->c = NULL;
	game->f = NULL;
	line = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		write(2,"cannot oppen map!",17);
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		game->str = ft_strjoin(game->str, line);
		line = get_next_line(fd);
	}
	close(fd);
}
void	alloc_map(t_game *game, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	data->max = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
			j++;
		if (j > data->max)
			data->max = j;
		i++;
	}
	data->map = malloc((i + 1) * sizeof(char *));
	k = 0;
	while (k < i)
	{
		data->map[k] = malloc((data->max + 1) * sizeof(char));
		k++;
	}
}

void	map_size(t_game *game, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			data->map[i][j] = game->map[i][j];
			j++;
		}
		while (j < data->max)
		{
			data->map[i][j] = ' ';
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
	data->map[i] = NULL;
	data->nb_rows = i;
	data->nb_cols = data->max;
}
void	free_all(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map_alloc[i])
	{
		free(game->map_alloc[i]);
		i++;
	}
	free(game->map_alloc);
	j = 0;
	while (game->array[j])
	{
		free(game->array[j]);
		j++;
	}
	free(game->str);
	free(game->array);
	free(game->c);
	free(game->f);
	free(game);
}
void	get_map(t_game *game, t_data *data)
{
	data->no = game->no;
	data->so = game->so;
	data->we = game->we;
	data->ea = game->ea;
	data->r_c = game->r_c;
	data->b_c = game->b_c;
	data->g_c = game->g_c;
	data->r_f = game->r_f;
	data->b_f = game->b_f;
	data->g_f = game->g_f;
}
void	map_check(t_game *gameInfo, t_data *data)
{
	check_map_valid(gameInfo->map);
	check_player_valid(gameInfo->map);
	check_vide(gameInfo->map, gameInfo);
	check_game(gameInfo->map_alloc);
	alloc_map(gameInfo, data);
	map_size(gameInfo, data);
	get_map(gameInfo, data);
}
void	parsing(int ac, char **av, t_data *data)
{
	int	i;
	int	j;
	t_game *gameInfo;

	i = -1;
	j = 6;
	check_ac(ac);
	if (check_map_name(av[1]) == 0)
	{
		write(2,"invalide map name",17);
		exit(1);
	}
	gameInfo = malloc(sizeof(t_game));
	read_map(av[1],gameInfo);
	check_newline(gameInfo);
	gameInfo->array = ft_split(gameInfo->str, '\n');
	while (gameInfo->array[++i] && j)
	{
		check_texture_color(gameInfo->array[i], gameInfo);
		j--;
	}
	if (gameInfo->no == NULL || gameInfo->we == NULL
		|| gameInfo->ea == NULL || gameInfo->so == NULL
		|| gameInfo->c == NULL || gameInfo->f == NULL)
		err_msg();
	gameInfo->map = gameInfo->array + 6;
	map_check(gameInfo, data);
	free_all(gameInfo);
}
