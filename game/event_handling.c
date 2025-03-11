/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:39:31 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 19:28:12 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	move_player(t_window *window, double angle)
{
	window->player.x += cos(angle * PI / 180) * MOV_SPEED;
	window->player.y += sin(angle * PI / 180) * MOV_SPEED;
}

static void	rotate_player(t_window *window, double angle)
{
	window->player.dir += angle;
	if (window->player.dir < 0)
		window->player.dir += 360;
	if (window->player.dir >= 360)
		window->player.dir -= 360;
}

int	update_player(t_window *window)
{
	if (window->mov.up)
		move_player(window, window->player.dir);
	if (window->mov.down)
		move_player(window, window->player.dir + 180);
	if (window->mov.left)
		move_player(window, window->player.dir - 90);
	if (window->mov.right)
		move_player(window, window->player.dir + 90);
	if (window->mov.r_left)
		rotate_player(window, -ROT_SPEED);
	if (window->mov.r_right)
		rotate_player(window, ROT_SPEED);
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
