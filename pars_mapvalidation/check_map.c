#include "cube.h"

void	check_map_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == ' ' || map[i][j] == '1'
					|| map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E' || map[i][j] == 'W')
				j++;
			else
				err_msg2("Error\nMap not valid\n");
		}
		i++;
	}
}

void	check_player_valid(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		err_msg2("Error\nPlayer not valid\n");
}

void	check_vide(char **map, t_game *game)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	game->map_alloc = NULL;
	while (map && map[i])
	{	
		if (ft_strlen(map[i]) > count)
			count = ft_strlen(map[i]);
		i++;
	}
	game->map_alloc = malloc((sizeof (char *)) * (i + 1));
	i = 0;
	while (map && map[i])
	{	
		game->map_alloc[i] = malloc(count + 1);
		i++;
	}
	game->map_alloc[i] = NULL;
	check_vide_norm(map, game, count);
}

void	check_vide_norm(char **map, t_game *game, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				game->map_alloc[i][j] = '+';
			else
				game->map_alloc[i][j] = map[i][j];
			j++;
		}
		while (j < (int)count)
		{
			game->map_alloc[i][j] = '+';
			j++;
		}
		game->map_alloc[i][j] = '\0';
		i++;
	}
}

void	err_in_map(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'E' || map[i][j] == 'W')
	{
		if ((i < 1 || map[i - 1][j] == '+' ) || (j < 1 || map[i][j - 1] == '+' )
			|| (map[i + 1] && map[i + 1][j] == '+') || map[i][j + 1] == '+')
			err_msg2("Error\nU cccan't\n");
	}
}
void	check_game(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			err_in_map(map, i, j);
			j++;
		}
		if (ft_strchr("0EWNS", map[i][j - 1]))
			err_msg2("Error\n cccccan't\n");
		i++;
	}
	j = 0;
	while (map[i - 1][j])
	{
		if (map[i - 1][j] != '1' && map[i - 1][j] != '+')
			err_msg2("Error\nUu ccccan't\n");
		j++;
	}
}