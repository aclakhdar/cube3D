/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:26:41 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/13 20:36:54 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	move_player(t_collision *colision, \
		double old_x, double old_y, t_window *window)
{
	t_collision	temp_col;

	temp_col = *colision;
	temp_col.new_y = old_y;
	if (!check_collision(window, old_x, old_y, &temp_col))
		window->player.x = temp_col.new_x;
	temp_col = *colision;
	temp_col.new_x = old_x;
	if (!check_collision(window, old_x, old_y, &temp_col))
		window->player.y = temp_col.new_y;
	return (0);
}

int	move_up(t_window *window, double old_x, double old_y)
{
	t_collision	*colision;

	colision = malloc(sizeof(t_collision));
	if (!colision)
		return (1);
	colision->new_x = window->player.x + \
		cos(window->player.dir * PI / 180) * MOV_SPEED;
	colision->new_y = window->player.y + \
		sin(window->player.dir * PI / 180) * MOV_SPEED;
	move_player(colision, old_x, old_y, window);
	free(colision);
	return (0);
}

int	move_down(t_window *window, double old_x, double old_y)
{
	t_collision	*colision;

	colision = malloc(sizeof(t_collision));
	if (!colision)
		return (1);
	colision->new_x = window->player.x - \
		cos(window->player.dir * PI / 180) * MOV_SPEED;
	colision->new_y = window->player.y - \
		sin(window->player.dir * PI / 180) * MOV_SPEED;
	move_player(colision, old_x, old_y, window);
	free(colision);
	return (0);
}

int	move_left(t_window *window, double old_x, double old_y)
{
	t_collision	*colision;

	colision = malloc(sizeof(t_collision));
	if (!colision)
		return (1);
	colision->new_x = window->player.x + \
		cos((window->player.dir - 90) * PI / 180) * MOV_SPEED;
	colision->new_y = window->player.y + \
		sin((window->player.dir - 90) * PI / 180) * MOV_SPEED;
	move_player(colision, old_x, old_y, window);
	free(colision);
	return (0);
}

int	move_right(t_window *window, double old_x, double old_y)
{
	t_collision	*colision;

	colision = malloc(sizeof(t_collision));
	if (!colision)
		return (1);
	colision->new_x = window->player.x + \
		cos((window->player.dir + 90) * PI / 180) * MOV_SPEED;
	colision->new_y = window->player.y + \
		sin((window->player.dir + 90) * PI / 180) * MOV_SPEED;
	move_player(colision, old_x, old_y, window);
	free(colision);
	return (0);
}
