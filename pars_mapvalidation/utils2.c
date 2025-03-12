/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:40:02 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 18:05:27 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_map_valid(char **map, t_game *gameinfo)
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
			{
				free_bfr_map(gameinfo);
				err_msg2("Errossr\nMap not valid\n");
			}
		}
		i++;
	}
}

void	check_ac(int ac)
{
	if (ac != 2)
	{
		write(2, "invalide arg", 12);
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
void	err_msg3(t_game *game)
{
	free_bfr_map(game);
	write(2, "Error\nU CANT PLAY\n", 19);
	exit(1);
}
