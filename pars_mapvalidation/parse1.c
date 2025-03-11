/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:40:23 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 21:36:09 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
					write(2, "error empty line", 16);
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
	int		i;
	int		j;
	t_game	*gameinfo;

	i = -1;
	j = 6;
	check_ac(ac);
	if (check_map_name(av[1]) == 0)
		err_msg2("invalide map name");
	gameinfo = malloc(sizeof(t_game));
	read_map(av[1], gameinfo);
	check_newline(gameinfo);
	gameinfo->array = ft_split(gameinfo->str, '\n');
	while (gameinfo->array[++i] && j)
	{
		check_texture_color(gameinfo->array[i], gameinfo);
		j--;
	}
	if (gameinfo->no == NULL || gameinfo->we == NULL
		|| gameinfo->ea == NULL || gameinfo->so == NULL
		|| gameinfo->c == NULL || gameinfo->f == NULL)
		err_msg();
	gameinfo->map = gameinfo->array + 6;
	map_check(gameinfo, data);
	free_all(gameinfo);
}
