/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:22:38 by aclakhda          #+#    #+#             */
/*   Updated: 2024/12/25 14:24:52 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	update_player(t_window *window) //updating player position and redrawing the sceen
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	double elapsed_time = (current_time.tv_sec - window->last_time.tv_sec) + (current_time.tv_usec - window->last_time.tv_usec) / 1000000.0;
	window->last_time = current_time;
	// printf("FPS: %f\n", 1 / elapsed_time);

	if (window->mov.up)
	{
		if (map[(int)((window->player.y - WALL_COLLISION) / 64)][(int)(window->player.x / 64)] != '1')
			window->player.y -= MOV_SPEED;
	}
	if (window->mov.down)
	{
		if (map[(int)((window->player.y + WALL_COLLISION) / 64)][(int)(window->player.x / 64)] != '1')
			window->player.y += MOV_SPEED;
	}
	if (window->mov.left)
	{
		if (map[(int)(window->player.y / 64)][(int)((window->player.x - WALL_COLLISION) / 64)] != '1')
			window->player.x -= MOV_SPEED;
	}
	if (window->mov.right)
	{
		if (map[(int)(window->player.y / 64)][(int)((window->player.x + WALL_COLLISION) / 64)] != '1')
			window->player.x += MOV_SPEED;
	}
	if (window->mov.r_left) //fham hadi mzyan
	{
		window->player.dir -= ROT_SPEED;
		if (window->player.dir < 0)
			window->player.dir += 360;
	}
	if (window->mov.r_right)
	{
		if (window->player.dir >= 360)
			window->player.dir = 0;
		window->player.dir += ROT_SPEED;
	}
	draw_scene(&window->img, window);
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

int	key_press(int keycode, t_window *window)
{
	if (keycode == R_ARROW)
	{
		window->mov.r_right = 1;
		window->mov.moved = 1;
	}
	if (keycode == L_ARROW)
	{
		window->mov.moved = 1;
		window->mov.r_left = 1;
	}
	if (keycode == UP)
	{
		window->mov.up = 1;
		window->mov.moved = 1;
	}
	if (keycode == DOWN)
	{
		window->mov.down = 1;
		window->mov.moved = 1;
	}
	if (keycode == LEFT)
	{
		window->mov.left = 1;
		window->mov.moved = 1;
	}
	if (keycode == RIGHT)
	{
		window->mov.right = 1;
		window->mov.moved = 1;
	}
	if (keycode == ESC)//free here
	{
		mlx_destroy_image(window->mlx, window->img.img);
		mlx_destroy_window(window->mlx, window->win);
		exit(0);
	}
	// printf("keycode: %d\n", keycode);
	return (0);
}
