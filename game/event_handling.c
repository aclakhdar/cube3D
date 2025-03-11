/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:39:31 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 21:28:24 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_collision(t_window *window, double old_x, double old_y, \
	t_collision *colision)
{
	int	map_x;
	int	map_y;

	colision->delta_x = colision->new_x - old_x;
	colision->delta_y = colision->new_y - old_y;
	colision->dist = sqrt(colision->delta_x * colision->delta_x + \
		colision->delta_y * colision->delta_y);
	if (colision->dist == 0)
		return (0);
	colision->dir_x = colision->delta_x / colision->dist;
	colision->dir_y = colision->delta_y / colision->dist;
	colision->check_x = colision->new_x + colision->dir_x * 20.0;
	colision->check_y = colision->new_y + colision->dir_y * 20.0;
	map_x = (int)(colision->check_x / COL_S);
	map_y = (int)(colision->check_y / COL_S);
	if (map_x < 0 || map_x >= window->image->nb_cols || \
		map_y < 0 || map_y >= window->image->nb_rows)
		return (1);
	if (window->image->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	rotate_left(t_window *window)
{
	window->player.dir -= ROT_SPEED;
	if (window->player.dir < 0)
		window->player.dir += 360;
	return (0);
}

int	rotate_right(t_window *window)
{
	window->player.dir += ROT_SPEED;
	if (window->player.dir >= 360)
		window->player.dir -= 360;
	return (0);
}

int	update_player(t_window *window)
{
	double	old_x;
	double	old_y;

	if (!window || !window->image)
		return (1);
	old_x = window->player.x;
	old_y = window->player.y;
	if (window->mov.up)
		move_up(window, old_x, old_y);
	if (window->mov.down)
		move_down(window, old_x, old_y);
	if (window->mov.left)
		move_left(window, old_x, old_y);
	if (window->mov.right)
		move_right(window, old_x, old_y);
	if (window->mov.r_left)
		rotate_left(window);
	if (window->mov.r_right)
		rotate_right(window);
	draw_scene(window->image, window);
	return (0);
}

int	key_release(int keycode, t_window *window)
{
	if (keycode == UP)
		window->mov.up = 0;
	if (keycode == DOWN)
		window->mov.down = 0;
	if (keycode == LEFT)
		window->mov.left = 0;
	if (keycode == RIGHT)
		window->mov.right = 0;
	if (keycode == R_ARROW)
		window->mov.r_right = 0;
	if (keycode == L_ARROW)
		window->mov.r_left = 0;
	return (0);
}
