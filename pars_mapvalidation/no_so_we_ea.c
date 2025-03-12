/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_so_we_ea.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:18:11 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 00:46:14 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	 game->so= ft_strdup(str_split[1]);
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
