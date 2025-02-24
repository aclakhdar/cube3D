#include "../cube.h"


void	rgb_stuff_norm(char **str_split, t_game *game)
{
	game->r_c = atoi(str_split[0]);
	free(str_split[0]);
	game->g_c = atoi(str_split[1]);
	free(str_split[1]);
	game->b_c = atoi(str_split[2]);
	free(str_split[2]);
	free (str_split);
	if (game->r_c < 0 || game->r_c > 255 || game->g_c < 0 || game->g_c > 255
		|| game->b_c < 0 || game->b_c > 255)
		err_msg2("Error\nCeiling color not valid\n");
}

void	rgb_stuff(char *line, t_game *game, int index)
{
	char	**str_split;

	str_split = ft_split(line, ',');
	if (index == 1)
	{
		game->r_f = atoi(str_split[0]);
		free(str_split[0]);
		game->g_f = atoi(str_split[1]);
		free(str_split[1]);
		game->b_f = atoi(str_split[2]);
		free(str_split[2]);
		free (str_split);
		if (game->r_f < 0 || game->r_f > 255 || game->g_f < 0 || game->g_f > 255
			|| game->b_f < 0 || game->b_f > 255)
			err_msg2("Error\nFloor color not valid\n");
	}
	else if (index == 2)
		rgb_stuff_norm(str_split, game);
	else
		free (str_split);
}


int	check_texture(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '.')
		{
			if (line[i + 1] == 'x' && line[i + 2] == 'p' && line[i + 3] == 'm'
				&& (line[i + 4] == '\0' || line[i + 4] == ' '))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_color(char *line, t_game *game, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[0] == ',')
			err_msg();
		if (line[i] == ' ')
			i++;
		if (line[i] == ',')
			count++;
		if ((line[i] != ',' && (line[i] < '0' || line[i] > '9'))
			|| (line[i] == ',' && line[i + 1] == ','))
			return (0);
		i++;
	}
	if (count != 2 || line[i - 1] == ',')
		return (0);
	rgb_stuff(line, game, index);
	return (1);
}

void	check_no(char *line, t_game *game, int fd, char **str_split)
{
	if (check_texture(line) == 0)
		err_msg2("Error\nNO not valid\n");
	game->no = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
	fd = open(game->no, O_RDONLY);
	if (fd == -1)
		err_msg2("FD not a valid texture\n");
}

void	check_we(char *line, t_game *game, int fd, char **str_split)
{
	if (check_texture(line) == 0)
		err_msg2("Error\nNO not valid\n");
	game->we = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
	fd = open(game->we, O_RDONLY);
	if (fd == -1)
		err_msg2("FD not a valid texture\n");
}

void	check_ea(char *line, t_game *game, int fd, char **str_split)
{
	if (check_texture(line) == 0)
		err_msg2("Error\nEA not valid\n");
	game->ea = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
	fd = open(game->ea, O_RDONLY);
	if (fd == -1)
		err_msg2("FD not a valid texture\n");
}

void	check_so(char *line, t_game *game, int fd, char **str_split)
{
	if (check_texture(line) == 0)
		err_msg2("Error\nSO not valid\n");
	game->so = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
	fd = open(game->so, O_RDONLY);
	if (fd == -1)
		err_msg2("FD not a valid texture\n");
}

void	check_f(t_game *game, char **str_split)
{
	if (check_color(str_split[1], game, 1) == 0)
		err_msg2("Error\nF not valid\n");
	game->f = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
}

void	check_c(t_game *game, char **str_split)
{
	if (check_color(str_split[1], game, 2) == 0)
		err_msg2("Error\nC not valid\n");
	game->c = ft_strdup(str_split[1]);
	free(str_split[0]);
	free(str_split[1]);
}