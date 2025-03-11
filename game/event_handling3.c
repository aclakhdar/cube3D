/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:26:41 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 21:28:38 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	move_player(t_collision *colision, double old_x, \
	double old_y, t_window *window)
{
	if (!check_collision(window, old_x, old_y, colision))
	{
		window->player.x = colision->new_x;
		window->player.y = colision->new_y;
	}
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
