/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:56:57 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 20:44:29 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	free_simple(t_game *game)
{
	free(game->str);
	free(game);
}

void	handle_map_error(t_game *game, char *message)
{
	free_exit(game);
	err_msg2(message);
}
