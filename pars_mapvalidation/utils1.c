/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:38:19 by mbouras           #+#    #+#             */
/*   Updated: 2025/04/25 16:01:37 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_texture_color(char *line, t_game *game)
{
	int		i;
	char	**str_split;

	i = 0;
	game->fd = 0;
	str_split = ft_split(line, ' ');
	if (!str_split[1] || str_split[2])
		free_help2(game, str_split);
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
		free_help2(game, str_split);
	free (str_split);
}

void	free_simple(t_game *game)
{
	free(game->str);
	free(game);
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
		free_simple(game);
		write(2, "cannot oppen map! \n", 17);
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
