/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:33:05 by mbouras           #+#    #+#             */
/*   Updated: 2025/04/25 16:01:13 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	free(game->array);
	free(game->str);
	free(game->c);
	free(game->f);
	free(game);
}

void	free_exit(t_game *game)
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
	free(game->array);
	free(game->str);
	free(game->so);
	free(game->we);
	free(game->ea);
	free(game->no);
	free(game->c);
	free(game->f);
	free(game);
}

void	free_bfr_map(t_game *game)
{
	int	j;

	j = 0;
	while (game->array[j])
	{
		free(game->array[j]);
		j++;
	}
	free(game->array);
	free(game->str);
	free(game->so);
	free(game->we);
	free(game->ea);
	free(game->no);
	free(game->c);
	free(game->f);
	free(game);
}

void	free_helper(t_game *game)
{
	free_exit(game);
	err_msg2("Error\nUu ccccan't\n");
}

void	free_help2(t_game *game, char **str_split)
{
	free_bfr_map(game);
	free_map(str_split);
	err_msg();
}
